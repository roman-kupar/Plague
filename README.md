# Plague Simulation Program
## Overview
This program is a 2D simulation that models the spread of an infectious disease in a population limited by some area. The simulation is represented by moving points on a grid, with blue points representing healthy individuals and red points representing infected individuals. The program shows exponential disease spread rate.
## Features
2D Grid Simulation: The program creates a 2D grid where each human is represented as point (blue or red).

Health Status Visualization: Healthy individuals are represented as blue points, while infected individuals are represented as red points. Also there is a chance for a heavy illness, which impacts on slowing point and changing its color. When a movement speed comes to zero, the point disappears, representing human death.

Infection Dynamics: Individuals move randomly on the grid, and there is a chance for healthy individuals to become infected when it intersects infected point.

Infection Parameters: In future, you'd be able to configure parameters such as infection probability, movement speed, and more to customize the simulation.

Statistics and Visualization: The program provides statistics on the infection spread, including the number of infected, healthy and dead individuals over time. 
