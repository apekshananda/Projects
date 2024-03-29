// Inductor.h - class declaration for an inductor
#ifndef INDUCTOR_H
#define INDUCTOR_H
#include "Component.h"

class Inductor : public Component { // derived from component class
private:
	double Inductance;
	double current[2];//to keep track of current current[0], current[1]
	double voltage = 0.0;

public:
	Inductor(double inductance, float red, float green, float blue, std::string componentName); // takes Inductance , Name, and RGB colors as parameters
	std::string GetName() const override;                                               // returns the name of component
	double GetVoltage(double _current, double timestep) override;                  // calculates the voltage in Inductance and returns it.   
	void Update() override;                             //  update the current in Inductor as  relies on previous current 
	void Display() override;           // prints the Inductance and voltage in Inductor component
};
#endif
