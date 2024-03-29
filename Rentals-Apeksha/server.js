
const express = require("express")
const app = express()
const path = require("path")
app.use('/rent',express.static("assets"))
app.use(express.static("assets"))
// write the code to create a web server
// - automatically assign a PORT Number that your server will run on
// - get the default port from the person's computer (porcess.env.PORT), and if you cannot
// find a default port, then use port 8080
const HTTP_PORT = process.env.PORT || 8080

app.use(express.urlencoded({ extended: true }))

// handlebars import and configuration
const exphbs = require("express-handlebars");
app.engine(".hbs", exphbs.engine({
    extname: ".hbs",
    helpers: {
        json: (context) => { return JSON.stringify(context) }
    }
}));
app.set("view engine", ".hbs");
const items = [
    { id: "aaaa", name: "Friend's TV Show Crap Bag", Availability: true },
    { id: "bbbb", name: "Sunglasses SOJO", Availability: true },
    { id: "cccc", name: "Polaroid Camera", Availability: true },
    { id: "dddd", name: "Arcade Bong", Availability: true },
    { id: "eeee", name: "Tent with 4 people capacity", Availability: true },
    { id: "ffff", name: "Friends title track record", Availability: true },
]

app.post("/rent/:rental", (req, res) => {
    console.log(`[DEBUG] Request received at /rent POST endpoint`)
    const itemfromform = req.params.rental
    let idx = -1
    for (let i = 0; i < items.length; i++) {
        if (items[i].id === itemfromform) {
            idx = i
            break
        }
    }

    items[idx].Availability = false
    res.render("home-page", {layout:false, item:items})
})
app.post("/return", (req, res) => {
    console.log(`[DEBUG] Request received at /return endpoint`)
    let rented=false
    for (let i = 0; i < items.length; i++) {
        if(items[i].Availability ===false)
        {
            rented=true
            items[i].Availability = true;
        }
        
    }
    if(rented===false)
    {
        res.render("error-page", { layout: false, print:"You do not have any rented items " })
    }
    else{
        res.render("home-page", { layout: false, item: items })
    }
    
})
app.post("/update", (req, res) => {
    console.log(`[DEBUG] Request received at /update POST endpoint`)
    const update_items = req.body.updates
    let newitems = []
    if (update_items === "Available items") {
        for (let i = 0; i < items.length; i++) {
            if (items[i].Availability === true) {
                newitems.push(items[i])
            }
        }
    }
    else if (update_items === "Your Rentals") {
        for (let i = 0; i < items.length; i++) {
            if (items[i].Availability === false) {
                newitems.push(items[i])
            }
        }
    }
    if(newitems.length===0){
        res.render("error-page", { layout: false, print:"No Results found " })
    }
    else{
        res.render("home-page", { layout: false, item: newitems })
    }
    
})
app.post("/search", (req, res) => {
    console.log(`[DEBUG] Request received at /search POST endpoint`)
    const search_items = req.body.itemname
    let newitems = []
    let f=false
    for (let i = 0; i < items.length; i++) {
        if (items[i].name.includes(search_items)) {
            newitems.push(items[i])
            f=true
            break
        }
    }
    if(f===false){
        res.render("error-page", { layout: false, print:"Item not found" })
    }
    else{
        res.render("home-page", { layout: false, item: newitems })
    }
})
app.get("/", (req, res) => {
    
    res.render("home-page", { layout: false, item: items })
})

// --------------------------------
// function
// - this is the function that executes when the web server starts

const onHttpStart = () => {
   console.log("The web server has started...")
   console.log(`Server is listening on port ${HTTP_PORT}`)
   console.log("Press CTRL+C to stop the server.")
 }
 
 app.listen(HTTP_PORT, onHttpStart)
 
 
 