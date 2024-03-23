//Inductor.cpp
#include"Inductor.h"

Inductor::Inductor(double inductance, float red, float green, float blue, std::string componentName) {
	name = componentName; // takes the componentName and store it in  variable of parent class ( component)
	Inductance = inductance; // takes the inductance and store it in local variable
	Red = red;
	Green = green;  // take rgb color and store them in variable of component class 
	Blue = blue;
	current[0] = 0.0;
	current[1] = 0.0;
}

std::string Inductor::GetName() const  {
	return name; // return the name of component
}

double Inductor::GetVoltage(double _current, double timestep)  {
	current[1] = _current;
	if (timestep > 0.0) {
		// Calculate the voltage using the provided equation
		voltage = (Inductance * (current[1] - current[0]) / timestep);

	}
	else {
		// Handle division by zero or very small timestep
		voltage = 0.0;
	}
	return voltage;
}

void Inductor::Update()  {
	current[0] = current[1];// Update the previous current
}

void Inductor::Display() {
	// Implement display logic for the inductor
	std::cout << "This component has a Inductance of " << Inductance << "H with a voltage drop of " << voltage << "V." << std::endl;

}