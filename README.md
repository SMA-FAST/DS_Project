Smart Traffic Management System Simulator
Introduction
The Smart Traffic Management System Simulator is designed to simulate urban traffic management in real-time. This C++ project demonstrates the use of advanced data structures and algorithms to optimize traffic flow, manage congestion, and prioritize emergency vehicle routing. The system dynamically adjusts traffic signals and recalculates vehicle routes based on real-time data, providing a practical approach to modern traffic challenges.

Key Features
1.	City Traffic Network (Graph Representation)
•	Represents city roads and intersections as a directed, weighted graph.
•	Supports dynamic addition/removal of roads or intersections.
•	Visualizes the graph structure for better understanding.
2.	Vehicle Routing System
•	Implements Dijkstra's Algorithm for shortest path calculation.
•	Dynamically recalculates routes based on changing traffic conditions.
•	Tracks vehicle movement across the network.
3.	Traffic Signal Management
•	Uses priority queues to manage incoming roads based on vehicle density.
•	Dynamically adjusts green signal durations to reduce overall congestion.
•	Overrides normal traffic operations for emergency situations.
4.	Congestion Monitoring
•	Tracks vehicle density on each road using hash tables.
•	Identifies and resolves congestion using BFS/DFS algorithms.
•	Displays congestion levels for analysis.
5.	Emergency Vehicle Handling
•	Calculates optimal routes for emergency vehicles using the A* algorithm.
•	Overrides traffic signals to clear paths for emergency vehicles.
•	Restores normal flow once emergencies are resolved.
6.	Accident and Road Closure Simulation
•	Simulates disruptions by blocking roads dynamically.
•	Re-routes traffic to minimize delays.
•	Updates the traffic network to reflect the changes.
7.	Interactive Simulation Dashboard
•	Visualizes traffic flow, signal statuses, and congestion levels.
•	Allows manual control for adding/removing vehicles or blocking roads.
•	Generates logs of all system actions for analysis.

System Workflow
1.	Initialization
•	Defines the road network as a graph with weights representing travel times.
•	Loads data for vehicles, signals, and emergencies from CSV files.
2.	Traffic Simulation
•	Dynamically assigns routes to vehicles based on the current traffic state.
3.	Signal and Flow Management
•	Adjusts signal timings based on vehicle density.
•	Prioritizes heavily congested roads.
4.	Emergency Handling
•	Reroutes traffic and adjusts signals for emergency vehicles.
•	Restores normal operations after the emergency clears.
5.	Congestion Resolution
•	Identifies congestion zones and reroutes vehicles to less busy paths.
•	Continuously updates routes as traffic conditions evolve.

How to Run the Project
Prerequisites
•	A working C++ compiler (e.g., GCC, MSVC).
•	CSV files for input data:
•	road_network.csv
•	vehicles.csv
•	traffic_signals.csv
•	emergency_vehicles.csv
•	road_closures.csv
Steps to Execute
1.	Clone the repository (or download the project folder).
2.	Compile the source code using the following command:
bash
Copy code
g++ -o simulator *.cpp
3.	Run the compiled program:
bash
Copy code
./simulator

Input Files and Formats
1.	road_network.csv: Defines intersections and roads with travel times.
2.	vehicles.csv: Specifies vehicle IDs and their start and end points.
3.	traffic_signals.csv: Provides initial signal timings at intersections.
4.	emergency_vehicles.csv: Lists emergency vehicles and their priority levels.
5.	road_closures.csv: Contains data for simulating road closures or accidents.

Expected Outputs
The system generates:
•	Simulation Dashboard: Displays traffic data and signal statuses.
•	Vehicle Routing: Shows optimal paths for vehicles.
•	Congestion Levels: Highlights congestion zones.
•	Emergency Handling: Demonstrates priority routing for emergency vehicles.
Refer to the Sample Output file provided for detailed examples.
