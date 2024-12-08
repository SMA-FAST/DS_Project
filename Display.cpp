#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "FileHandeling.cpp" // Handles data loading       // Manages the graph structure

using namespace std;

int displayMenu()
{
    cout << "\nSmart Traffic Management System Simulator"<<endl;
    cout << "1. Display City Traffic Network"<<endl;
    cout << "2. Simulate Traffic Signal"<<endl;
    cout << "3. Emergency Vehicle Routing"<<endl;
    cout << "4. Check Congestion Status"<<endl;
    cout << "5. Show Blocked Roads"<<endl;
    cout << "6. Block a Road"<<endl;
    cout << "7. Unblock a Road"<<endl;
    cout << "8. Exit Simulation"<<endl;
    cout << "Enter your choice: ";
    int choice;
    cin>> choice;
    return choice;
}

void displayCityNetwork(Graph &graph)
{
    cout << "\nCity Traffic Network:"<<endl;
    graph.printGraph();
}

void simulateTrafficSignal(Graph &graph)
{
    cout << "\nSimulating Traffic Signals:"<<endl;
    // Example simulation for roads
    for (int i = 0; i < graph.vertices.size; i++)
    {
        cout << "Intersection " << graph.vertices[i].data
             << " -> Traffic Light Status: GREEN"<<endl;
    }
}

void checkCongestionStatus(Graph &graph)
{
    cout << "\nCongestion Status:"<<endl;
    for (int i = 0; i < graph.vertices.size; i++)
    {
        cout << "Intersection " << graph.vertices[i].data << ": No Congestion"<<endl;
    }
}

void showBlockedRoads(Graph &graph)
{
    cout << "\nBlocked Roads:"<<endl;
    for (int i = 0; i < graph.vertices.size; i++)
    {
        for (int j = 0; j < graph.connecting_edges[i].size; j++)
        {
            if (graph.connecting_edges[i][j].data.is_closed)
            {
                cout << "Road " << graph.connecting_edges[i][j].data.from
                     << " -> " << graph.connecting_edges[i][j].data.to << " is Blocked."<<endl;
            }
        }
    }
}

void emergencyVehicleRouting(Graph &graph)
{
    cout << "\nEmergency Vehicle Routing Simulation:"<<endl;
    // Simplified BFS routing for emergencies
    graph.BFS(0);
}

void blockRoad(Graph &graph, char from, char to)
{
    cout << "\nBlocking Road " << from << " -> " << to << ":"<<endl;
    graph.getEdge(graph.findVertexID(from), graph.findVertexID(from)).data.is_closed = true;
    cout << "Road Blocked Successfully."<<endl;
}

void unblockRoad(Graph &graph, char from, char to)
{
    cout << "\nUnblocking Road " << from << " -> " << to << ":"<<endl;
    graph.getEdge(graph.findVertexID(from), graph.findVertexID(from)).data.is_closed = false;
    cout << "Road Unblocked Successfully."<<endl;
}

int main()
{
    Graph graph;
    LinkedList<Intersection> intersections = loadIntersections();
    LinkedList<Road> roads = readRoad();
    LinkedList<Vehicle> vehicles = readVehicle();
    LinkedList<Vehicle> eVehicles = readEVehicle();

    // Add intersections to the graph
    for (int i = 0; i < intersections.size; i++)
    {
        graph.addVertex(intersections[i]);
    }

    // Add roads to the graph
    for (int i = 0; i < roads.size; i++)
    {
        graph.addEdge(roads[i]);
    }

    int choice;
    while (true)
    {
        system("clear");
        choice=displayMenu();
        system("clear");
        switch (choice)
        {
        case 1:
        {
            displayCityNetwork(graph);
            break;
        }
        case 2:
            simulateTrafficSignal(graph);
            break;
        case 3:
            emergencyVehicleRouting(graph);
            break;
        case 4:
            checkCongestionStatus(graph);
            break;
        case 5:
            showBlockedRoads(graph);
            break;
        case 6:
        {
            char from, to;
            cout << "Enter intersections (from to) to block: ";
            cin >> from >> to;
            blockRoad(graph, from, to);
            break;
        }
        case 7:
        {
            char from, to;
            cout << "Enter intersections (from to) to unblock: ";
            cin >> from >> to;
            unblockRoad(graph, from, to);
            break;
        }
        case 8:
            cout << "Exiting Simulation. Goodbye!"<<endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again."<<endl;
        }
        cout << flush;
        int choice2;
        cout << "Enter any key to return to menu:";
        cin >> choice2;
        cin.clear();
        cin.ignore();
    }
    return 0;
}