# Elevator Simulation Project
**If you would like to access the full project report, please click [here](Report.pdf).**  
*The report includes an in-depth explanation of the project’s purpose, methodology, and code analysis.*

## Description
The Elevator Simulation Project is a C++ program designed to simulate the operation and management of elevators with a strong focus on efficient use of data structures and object-oriented programming (OOP) principles. The primary goal is to model real-world elevator behavior in a single or multi-elevator system while optimizing performance in the terms of passenger wait time, elevator utilization, and overall system efficiency. Users can customize the simulation parameters, such as the number of floors, elevators, and passengers, to test the system's performance under various scenarios.

## Features
* Simulates a single or multi-elevator system
* Customizable simulation parameters
  * Total number of passengers to simulate
  * Number of passengers to generate per second
  * Number of floors in the building
  * Number and capacity of elevators
* An optimized elevator assignment algorithm to handle passenger requests efficiently
* Outputs a summary of simulation results

## Sample Run
```
-----------------------------------
=== ELEVATOR SIMULATION PROGRAM ===
-----------------------------------
Enter the total number of passengers to simulate (max 100000): 1000

Enter the number of passengers to generate per second (max 30): 15

Enter the number of floors in the simulation (max 150): 10

Enter the number of elevators to simulate (max 20): 4

Enter the capacity of each elevator (max 20): 15

=== SIMULATION RESULTS ===
Simulation Duration: 67s
Total Passengers Served: 1000
Average Wait Time: 3.16s
```

---

This project was developed as part of COMP-SCI 303 Data Structures at the University of Missouri - Kansas City (UMKC).

Copyright © 2024 Atlas Mallams

This repository is licensed under the [MIT License](https://opensource.org/licenses/MIT).  
For more information, please see [LICENSE](LICENSE).
