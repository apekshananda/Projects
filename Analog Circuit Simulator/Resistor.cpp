//Resistor.cpp
#include"Resistor.h"

Resistor::Resistor(double resistance, float red, float green, float blue, std::string componentName) {
	Resistance = resistance;  // takes the reistance and store it in local variable
	Voltage = 0.0;          
	name = componentName;  // takes the componentName and store it in  variable of parent class ( component)
	Red = red;
	Green = green;      // take rgb color and store them in variable of component class 
	Blue = blue;
}

std::string Resistor::GetName() const  {
	return name;    // return the name of component
}

double Resistor::GetVoltage(double _current, double timestep)  {
	Voltage = _current * Resistance;   // V=IR
	return Voltage;    
}

void Resistor::Update()  {
	// nothing to update here
}

void Resistor::Display()  {
	// Implement display logic for the resistor
	std::cout << "This component has a resistance of " << Resistance << "ohms with a voltage drop of " << Voltage << "V." << std::endl;

}