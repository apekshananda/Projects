//Capacitor.h class declaration for capacitor
#ifndef CAPACITOR_H
#define CAPACITOR_H
#include "Component.h"

class Capacitor :public Component {// derived from component class
private:
	double Capacitance;
	double voltage[2];// to keep track of voltages across two points of capacitor
public:
	Capacitor(double capacitance, float red, float green, float blue, std::string componentName); // takes capacitance , Name, and RGB colors as parameters
	std::string GetName() const override;                                               // returns the name of component
	double GetVoltage(double _current, double timestep) override;                  // calculates the voltage in capacitance and returns it.   
	void Update() override;                             //  update the voltage in Capacitor as  relies on previous voltage 
	void Display() override;           // prints the capacitance and voltage in Capacitor component
};
#endif
