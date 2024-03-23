// server code
//javascript to import express


const express = require("express");

//use the functions/classes
// provided by express
//to create a web server

const app = express();
const HTTP_PORT = process.env.PORT || 8080;

// use a static resources folder
app.use(express.static('assets'))

// configure express to receive form field data
app.use(express.urlencoded({ extended: true }))

// setup handlebars
const exphbs = require("express-handlebars");
app.engine(".hbs", exphbs.engine({
    extname: ".hbs",
    helpers: {
        json: (context) => { return JSON.stringify(context) }
    }
}));
app.set("view engine", ".hbs");

const session = require('express-session')
app.use(session({
    secret: "the quick brown fox jumped over the lazy dog 1234567890",  // random string, used for configuring the session
    resave: false,
    saveUninitialized: true
}))
const mongoose = require('mongoose');

mongoose.connect("mongodb+srv://dbUser:kmQoaLVnlf94rzAz@cluster0.e0xuyub.mongodb.net/?retryWrites=true&w=majority");
const Schema = mongoose.Schema
const userSchema = new Schema({ username: String, password:String, userType: String })
const User = mongoose.model("user_collection", userSchema)
const classesSchema = new Schema({ image: String, className: String, Length: Number, classStatus: Boolean })
const Class = mongoose.model("classes_collection", classesSchema)
const paymentSchema = new Schema({ username: String, className: String, pricebefore: Number, total: Number, date: Date })
const Payments = mongoose.model("payments_collection", paymentSchema)

//-------------
//endpoints
//-------------

app.get("/", async (req, res) => {
    console.log(`[DEBUG] GET request received at / endpoint`)
    console.log(req.session)
    if (req.session.userLoggedIn === undefined) {
        res.render("login_page", { layout: "my-template", status: false })
        return
    }
    else {
        if (req.session.userLoggedIn === true) {
            try {
                let price = 0
                let list = []

                const classlist = await Class.find().lean()
                if (classlist.length === 0) {
                    res.send("ERROR: There are no classes in the gym!")
                    return
                }
                for (let i = 0; i < classlist.length; i++) {
                    price = 0.65 * classlist[i].Length
                    const classdict = { id: classlist[i]._id, imageName: classlist[i].image, name: classlist[i].className, classLength: classlist[i].Length, Status: classlist[i].classStatus, classPrice: price }
                    list.push(classdict)
                }
                res.render("schedule_page", { layout: "my-template", status: true, classes: list })
            } catch (err) {
                console.log(err)
            }
            return
        }
    }

})

//Create an endpoint to receive form data 


app.post("/login", async (req, res) => {
    console.log(`[DEBUG] POST request received at /login endpoint`)
    const emailFromUI = req.body.emailAddress
    const passwordFromUI = req.body.password
    const passwordInInt = parseInt(passwordFromUI)
    console.log(`LOGIN Email: ${emailFromUI}, Password: ${passwordFromUI}`)

    try {
        const userFromDB = await User.findOne({ username: emailFromUI })
        if (userFromDB === null) {
            res.send(`LOGIN ERROR: This user does not exist: ${emailFromUI}`)
            return
        }
        else {
            if (userFromDB.password === passwordFromUI) {
                req.session.userLoggedIn = true
                req.session.userType = userFromDB.userType
                req.session.username = userFromDB.username
                res.redirect("/")
                return
            }
            else {
                res.send(`LOGIN ERROR: Invalid password`)
                return
            }

        }
    } catch (err) {
        console.log(err)
    }
})

app.post("/create", async (req, res) => {
    const emailFromUI = req.body.emailAddress
    const passwordFromUI = req.body.password
    const userTypeFromUI = "user"
    console.log(`SIGNUP: Email: ${emailFromUI}, Password: ${passwordFromUI}, User Type: ${userTypeFromUI}`)

    try {
        const userFromDB = await User.findOne({username:emailFromUI})
        if (userFromDB === null) {
 
            const userToAdd = User({username:emailFromUI, password:passwordFromUI, userType:userTypeFromUI})
            await userToAdd.save()

            req.session.hasLoggedInUser = true
            req.session.userType = userToAdd.userType
            req.session.username = userToAdd.username
            res.send(`Logged In`)
 
 
        }
        else {
            // 3. if yes, then show an error
            res.send(`ERROR: There is already a user account for ${emailFromUI}`)
            return
        }
    }
    catch (err) {
        console.log(err)
    }
})

app.post("/book/:idtoBook", async (req, res) => {
    console.log(`[DEBUG] Request received at /book POST endpoint`)
    const idtobook = req.params.idtoBook
    const Username = req.session.username
    try {
        console.log(idtobook)
        const classFromDB = await Class.findOne({ _id: idtobook })
        if (classFromDB === null) {
            res.send(`LOGIN ERROR: This does not exist`)
            return
        }
        else {
            classFromDB.classStatus = false
            await classFromDB.save()
            let price = 0.65 * classFromDB.Length
            let Total = (0.13 * price) + price
            console.log(req.session.username)
            const payment = Payments({ username: Username, className: classFromDB.className, pricebefore: price, total: Total, date: Date() })
            await payment.save()
            res.send(`Booking successfull, view the cart page to see all the bookings`)

        }
    }
    catch (err) {
        console.log(err)
    }
})
app.post("/not-book", (req, res) => {
    res.send("User have to login ")
})
app.get("/admin", async (req, res) => {
    console.log(`[DEBUG] POST request received at /admin endpoint`)

    if (req.session.userLoggedIn === undefined) {
        res.send("ERROR: you have to log in")
        return
    }
    else {

        if (req.session.userType === "admin") {
            if (req.session.userLoggedIn === true) {
                const paymentsfromDB = await Payments.find().lean()
                res.render("admin_page", { layout: "my-template", status: true, paylist: paymentsfromDB })
                return
            }
        }
        else {
            res.send("ERROR: You must be an admin user.")
            return
        }
    }
})
app.get("/classes", async (req, res) => {
    console.log(`[DEBUG] POST request received at /classes endpoint`)
    try {
        let price = 0
        let list = []

        const classlist = await Class.find().lean()
        if (classlist.length === 0) {
            res.send("ERROR: There are no classes in the gym!")
            return
        }
        for (let i = 0; i < classlist.length; i++) {
            price = 0.65 * classlist[i].Length
            const classdict = { id: classlist[i]._id, imageName: classlist[i].image, name: classlist[i].className, classLength: classlist[i].Length, Status: classlist[i].classStatus, classPrice: price }
            list.push(classdict)
        }
        console.log(list)
        console.log(classlist)
        console.log(req.session)
        if (req.session.userLoggedIn === undefined) {

            res.render("schedule_page", { layout: "my-template", status: false, classes: list })
        }
        else {
            if (req.session.userLoggedIn === true) {
                res.render("schedule_page", { layout: "my-template", status: true, classes: list })
            }
        }

    } catch (err) {
        console.log(err)
    }

})
app.get("/cart", async (req, res) => {
    console.log(`[DEBUG] POST request received at /cart endpoint`)
    if (req.session.userLoggedIn === undefined) {
        res.send("ERROR: you have to log in")
        return
    }
    else {
        if (req.session.userLoggedIn === true) {
            try {
                let price = 0
                let list = []
                const classlist = await Class.find().lean()
                if (classlist.length === 0) {
                    res.send("ERROR: There are no classes in the gym!")
                    return
                }
                for (let i = 0; i < classlist.length; i++) {
                    if (classlist[i].classStatus === false) {
                        price = 0.65 * classlist[i].Length
                        const classdict = { id: classlist[i]._id, imageName: classlist[i].image, name: classlist[i].className, classLength: classlist[i].Length, Status: classlist[i].classStatus, classPrice: price }
                        list.push(classdict)
                    }
                }
                res.render("cart", { layout: "my-template", status: true, classes: list })
            } catch (err) {
                console.log(err)
            }
        }
    }
})
app.get("/logout", (req, res) => {
    console.log(`[DEBUG] LOGOUT...`)
    req.session.destroy()
    res.redirect("/")

})

// start server
//function that executes the web server
const onHttpStart = () => {
    console.log("Express http server listening on: " + HTTP_PORT);
    console.log(`http://localhost:${HTTP_PORT}`);
}
app.listen(HTTP_PORT,onHttpStart);
