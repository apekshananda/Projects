# Analog_Circuit_Simulator
## Project Description
### Overview
This project involves the development of an Analog Circuit Simulator (ANASIM) to simulate the behavior of analog electronic circuits. The simulator supports three approaches: numerical methods, machine learning, and heuristic algorithms. Theoretical background and implementation details are provided for each approach.

### Use-Case Scenario
ANASIM is designed to simulate analog electronic circuits, incorporating numerical methods, machine learning cost functions, and heuristic algorithms. The project involves completing the design and implementation started by a former employee. A project plan, scheduling, cost estimation, and quality assurance are integral to the development process.

### Theoretical Background
Numerical Methods
The simulator employs numerical methods, including Euler's method, the midpoint method, and the Runge-Kutta method for solving ordinary differential equations. The challenge with applying these methods to analog circuits lies in their assumption of linear behavior, making them less suitable for nonlinear circuits.

Machine Learning Cost Function
The machine learning cost function approximates real data using a hypothetical equation. For nonlinear electronic circuits, the cost function is expanded to higher-order equations, akin to the Taylor Series. This approach involves applying voltages to circuits, measuring currents, determining optimal parameters, and using them to predict behavior.

Heuristic Algorithms
Heuristic algorithms are used for faster and more efficient problem-solving in non-linear circuits. For example, the diode's voltage-current relationship is described, and heuristic approaches are employed for components exhibiting non-linear behavior.

### Work Breakdown
Cost Function
The assignment centers around a cost function, predicting component currents given an applied voltage. The cost function iteratively guesses the current until the cost approaches zero. Key variables include predicted current (I1), cost of the function for the current iteration (J1), costs for the previous iteration (J0), applied voltage, and the sum of component voltages.

Circuit Components
Implementation of resistor, capacitor, and inductor components derived from the base class is required. Each component displays current in a different color, and the analog circuit class manages a list of circuit components, a static display function, a run function for simulation, the cost function, and a destructor.

Graphics
The OpenGL graphics library is recommended for visualizing the simulation results. Applied voltage and component voltages need to be plotted over time.

## Sample Run
A sample run involves applying a sinusoidal voltage for 0.6 seconds, followed by 0 volts for the remainder of the simulation. The plotted results should display the applied voltage and voltages across each circuit component.

![ANASIM](https://github.com/salonikamboj/Analog_Circuit_Simulator/assets/100891813/045fb093-cd55-4ad3-92fa-647fb47d6218)

The output file is available at RLC.dat.

## Additional Resources
1. OpenGL Documentation
2. Configuring Visual Studio for OpenGL Development
