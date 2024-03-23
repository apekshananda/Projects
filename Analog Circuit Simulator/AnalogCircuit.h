//AnalogCircuit.h - header file for the analog circuit


#ifndef _ANALOGCIRCUIT_H_
#define _ANALOGCIRCUIT_H_

#include <fstream>
#include <list>
#include <Windows.h>    
#include <gl/GL.h>    
#include <gl/GLU.h>    
#include <gl/glut.h>
#include <gl/freeglut.h>
#include "Component.h"

extern int windowWidth, windowHeight;
extern double scalingFactor;

void start();

class AnalogCircuit {
	const double T = 0.000001;//timestep of 1uS
	const double timeMax = 0.1;
	const double tolerance = 0.0001;//
	const double freq = 50;//50Hz
	const double Vpeak = 10.0;//10V
	const int xoffset = 50;
	double I=0.0;
	std::list<Component*> component;//polymorphism with the STL
	std::ofstream fout;
public:
	AnalogCircuit(std::string filename);//dump output data to a file
	static void display(float R, float G, float B);//display output data on the screen
	void run(); // run the simulation
	void CostFunctionV(double& current, double V,double time); // calculate the cost and update the current
	~AnalogCircuit();
};

#endif// _ANALOGCIRCUIT_H_