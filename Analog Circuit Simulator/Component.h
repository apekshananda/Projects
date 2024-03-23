//Component.h - abstract base class for electronic components


#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <iostream>

class Component {
protected:
	float Red;
	float Green;
	float Blue;
	std::string name;
public:
	virtual std::string GetName() const = 0;
	virtual void Update() = 0;
	virtual double GetVoltage(double _current, double timestep) = 0;
	virtual void Display() = 0;
};

#endif// _COMPONENT_H_