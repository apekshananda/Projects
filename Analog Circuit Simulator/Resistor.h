// Resistor.h - class declaration for a resistor
#ifndef RESISTOR_H
#define RESISTOR_H
#include "Component.h"

class Resistor : public Component { // derived from component class
private:
	double Resistance;
	double Voltage;

public:
	Resistor(double resistance, float red, float green, float blue, std::string componentName); // takes resistance , Name, and RGB colors as parameters
	std::string GetName() const override;                                               // returns the name of component
	double GetVoltage(double _current, double timestep) override;                  // calculates the voltage in resistance and returns it.   
	void Update() override ;                             // there is nothing to update in resistor as it doe not rely on previous current or voltage
	void Display() override;           // prints the resistance and voltage in resistor component
};
#endif