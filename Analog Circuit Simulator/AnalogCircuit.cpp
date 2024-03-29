//AnalogCircuit.cpp - function definitions for the analog circuit


#include <iomanip>//setw
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>//M_PI
#include <stdlib.h>//abs

#include "AnalogCircuit.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Resistor.h"

using namespace std;

int xpos, ypos;
int windowWidth, windowHeight;
double scalingFactor;

void start() {
	cout << "BEGIN" << endl;
	AnalogCircuit circuit("RLC.dat");
	circuit.run();
	cout << "Press any key + ENTER to end..." << endl;
	char key;
	cin >> key;
	glutLeaveMainLoop();
	cout << "DONE!" << endl;
}

void AnalogCircuit::display(float R, float G, float B) {//draw a point on the screen
	//	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R, G, B);//RGB
	glBegin(GL_POINTS);
	glVertex2f(xpos, ypos);
	glEnd();
	glFlush();
}

AnalogCircuit::AnalogCircuit(string filename) {//dump data to filename, initialize variables
	fout.open(filename); // open the file using fout
}

void AnalogCircuit::run() {

	component.push_back(new Capacitor(0.000100, 0.0, 1.0, 0.0, "C1"));//100uF, Green
	component.push_back(new Inductor(0.020, 0.0, 0.0, 1.0, "L1"));//20mH, Blue
	component.push_back(new Resistor(10, 1.0, 0.0, 0.0, "R1"));//10ohm, Red

	//Horizontal line
	glColor3f(1.0, 1.0, 1.0); // Set color to white

	// Horizontal axis (positive part)
	glBegin(GL_LINES);
	glVertex2f(0.0, scalingFactor * windowHeight / 2.0); // Starting point at the leftmost point
	glVertex2f(windowWidth, scalingFactor * windowHeight / 2.0); // Ending point at the right edge
	glEnd();

	// Draw the vertical axis
	glColor3f(1.0, 1.0, 1.0); // Set color to white

	// Vertical axis 
	glBegin(GL_LINES);
	glVertex2f( 0.0, 0.0); // Starting point at the leftmost point
	glVertex2f(  1.0, windowHeight); // Ending point from top to bottom
	glEnd();


	//Horizontal line markers
	glColor3f(1.0, 1.0, 1.0);
	int numMarkers_h = 10;
	float spacing_h = windowWidth / numMarkers_h;
	glBegin(GL_LINES);
	for (int i = 0; i < numMarkers_h; ++i) {
		float x = i * spacing_h;
		float y = scalingFactor * windowHeight / 2.0 - 5.0;
		glVertex2f(x, y); // Starting point
		glVertex2f(x, y + 10.0); // Ending point
	}
	glEnd();

	//Vertical line markers
	glColor3f(1.0, 1.0, 1.0); //(RGB)
	int numMarkers_v = 10;
	float spacing_v = windowHeight / numMarkers_v;
	glBegin(GL_LINES);
	for (int i = 0; i < numMarkers_v; ++i) {
		float y = i * spacing_v;
		float x = scalingFactor ;
		glVertex2f(x, y); // Starting point
		glVertex2f(x + 10.0, y); // Ending point
	}
	glEnd();

	//put titles in file
	fout << std::setw(12) << "time" << std::setw(12) << "Voltage" << std::setw(12) << "Current"
		<< std::setw(12) << "V_cap" << std::setw(12) << "V_ind" << std::setw(12) << "V_res" << std::endl;

	//Display each component's name and colour
	//Run the simulation for the first 0.06 seconds (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen
	for (double time = 0.0; time < 0.6 * timeMax; time += T) {
		double V = Vpeak * sin(2.0 * M_PI * freq * time);

		// determine x and y position for  votlage V.
		xpos = time * windowWidth / timeMax;
		ypos = (windowHeight * V / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0; // y position is just for thr normal voltage
		display( 1.0, 1.0, 1.0); // display graph for Voltage V against Current I using white line

		//determine the voltages across the components and plot them in green
		CostFunctionV(I, V,time);

		
	}

	//Run the simulation to the end (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen
	for (double time = 0.6 * timeMax; time < timeMax; time += T) {
		double V = 0.0;
		// determine x and y position for  votlage V which is 0 in this case.
		xpos = time * windowWidth / timeMax;
		ypos = (windowHeight * V / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0; // y position is just for the normal voltage
		display(1.0, 1.0, 1.0); // display graph for Voltage V against Current I using white line


		//determine the voltages across the components and plot them in green
		CostFunctionV(I, V,time);
		
	}

}

void AnalogCircuit::CostFunctionV(double& current, double voltage,double time) { 
	double I1 = current;
	double J1 = 0.0;
	double J0 = 0.0;
	double alpha = 1.0;

	do {
		double sumVoltage = 0.0;
		list<Component*>::iterator it;
		for (it = component.begin(); it != component.end(); ++it) {
			double Vcomponent = (*it)->GetVoltage(I1, T);
			sumVoltage += Vcomponent;
			
		}
		J1 = sumVoltage - voltage;
		//Reduce alpha if J1 and J0 are of opposite signs or are equal to each other
		if ((abs(J0 - J1) != (J0 - J1)) || J0 == J1)alpha /= 2.0;

		if (abs(J1) > tolerance) {
			if (J1 < 0) {//increase the current
				I1 += alpha;
			}
			else {
				I1 -= alpha;
			}
			J0 = J1;
		}
		if (alpha < tolerance / 1000000.0) {//reset alpha
			alpha = ((double)rand() / (RAND_MAX)) + 0.5;//between 0.5 and 1.5
		}
	} while (abs(J1) > tolerance);

	//create variables for voltages across every component
	double v_cap = 0; 
	double v_ind = 0;
	double v_res = 0;
	list<Component*>::iterator it;
	//iterate through every component to get voltage
	for (it = component.begin(); it != component.end(); ++it) {
		ypos = (windowHeight * (*it)->GetVoltage(I1, T) / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;// y position is the voltage across every component
		// if component is Capacitor
		if ((*it)->GetName() == "C1") {
			display(0.0, 1.0, 0.0); //display voltage against current in green line
			v_cap = (*it)->GetVoltage(I1, T);
		}
		//if component if Inductor
		else if ((*it)->GetName() == "L1")
		{
			display(0.0, 0.0, 1.0); //display voltage against current in blue line
			v_ind = (*it)->GetVoltage(I1, T);
		}
		//if component is resistor
		else if ((*it)->GetName() == "R1")
		{
			display(1.0, 0.0, 0.0); //display voltage against current in red line
			v_res = (*it)->GetVoltage(I1, T);
		}
		(*it)->Display(); // display components feature and voltages
		(*it)->Update();  // update the current or voltage if required by component
	}
	current = I1; // update the current
	fout << std::fixed << std::setprecision(7);
	// put the values in file
	fout << std::setw(12) << time << std::setw(12) << voltage << std::setw(12) << current
		<< std::setw(12) << v_cap << std::setw(12) << v_ind << std::setw(12) << v_res << std::endl;
	fout << endl;
}

AnalogCircuit::~AnalogCircuit() {//perform cleanup
	fout.close(); // close the file
}