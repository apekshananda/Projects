//Capacitor.cpp
#include"Capacitor.h"

Capacitor::Capacitor(double capacitance, float red, float green, float blue, std::string componentName) {
	name = componentName; // takes the componentName and store it in  variable of parent class ( component)
	Capacitance = capacitance; // takes the capacitance and store it in local variable
	Red = red;
	Green = green; // take rgb color and store them in variable of component class 
	Blue = blue;
	voltage[0] = 0.0;
	voltage[1] = 0.0;
}

std::string Capacitor::GetName() const  {
	return name; // return the name of component
}

double Capacitor::GetVoltage(double _current, double timestep)  {
	// Calculate the voltage
	voltage[1] = voltage[0] + (_current * timestep / Capacitance);
	return voltage[1];
}

void Capacitor::Update()  {
	voltage[0] = voltage[1]; // Update the previous voltage
}

void Capacitor::Display()  {
	// Implement display logic for the Capacitor
	std::cout << "This component has a Capacitance of " << Capacitance << "F with a voltage drop of " << voltage[1] << "V." << std::endl;

}