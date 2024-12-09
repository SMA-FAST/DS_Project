#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "FileHandeling.cpp" // Handles data loading       // Manages the graph structure

using namespace std;

int displayMenu()
{
    cout << "\nSmart Traffic Management System Simulator" << endl;
    cout << "1. Display City Traffic Network" << endl;
    cout << "2. Simulate Traffic Signal" << endl;
    cout << "3. Emergency Vehicle Routing" << endl;
    cout << "4. Check Congestion Status" << endl;
    cout << "5. Show Blocked Roads" << endl;
    cout << "6. Block a Road" << endl;
    cout << "7. Unblock a Road" << endl;
    cout << "8. Exit Simulation" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

void displayCityNetwork(Graph &graph)
{
    cout << "\nCity Traffic Network:" << endl;
    graph.printGraph();
}

void simulateTrafficSignal(Graph &graph)
{
    cout << "\nSimulating Traffic Signals:" << endl;
    // Example simulation for roads
    for (int i = 0; i < graph.connecting_edges.size; i++)
    {
        for (int j = 0; j < graph.connecting_edges[i].size; j++)
        {
            if (graph.connecting_edges[i][j].weight < 10)
            {
                cout << "Intersection " << graph.vertices[i].data
                     << " ->" << graph.connecting_edges[i][j].data.to
                     << "Traffic Light Status: RED" << endl;
            }
            else
            {
                cout << "Intersection " << graph.vertices[i].data
                     << " ->" << graph.connecting_edges[i][j].data.to
                     << "Traffic Light Status: GREEN" << endl;
            }
        }
    }
}

void checkCongestionStatus(Graph &graph)
{
    cout << "\nCongestion Status:" << endl;
    for (int i = 0; i < graph.connecting_edges.size; i++)
    {
        for (int j = 0; j < graph.connecting_edges[i].size; j++)
        {
            if (graph.connecting_edges[i][j].weight < 10)
            {
                cout << "Road " << graph.connecting_edges[i][j].data.from << "->" << graph.connecting_edges[i][j].data.to << ": No Congestion" << endl;
            }
            else if (graph.connecting_edges[i][j].weight < 20)
            {
                cout << "Road " << graph.connecting_edges[i][j].data.from << "->" << graph.connecting_edges[i][j].data.to << ": Minor Congestion" << endl;
            }
            else
            {
                cout << "Road " << graph.connecting_edges[i][j].data.from << "->" << graph.connecting_edges[i][j].data.to << ": Major Congestion" << endl;
            }
        }
    }
}

void showBlockedRoads(Graph &graph)
{
    cout << "\nBlocked Roads:" << endl;
    for (int j = 0; j < graph.blocked_roads.size; j++)
    {
        cout << "Road " << graph.blocked_roads[j].data.from
             << " -> " << graph.blocked_roads[j].data.to << " is Blocked." << endl;
    }
}

void emergencyVehicleRouting(Graph &graph, LinkedList<Vehicle> &evs)
{
    cout << "\nEmergency Vehicle Routing Simulation:" << endl;
    for (int i = 0; i < evs.size; i++)
    {
        cout << "Routing " << evs[i].id << ": " << endl;
        graph.findShortestPath(graph.findVertexID(evs[i].source), graph.findVertexID(evs[i].destination));
    }
}

void blockRoad(Graph &graph, char from, char to)
{
    cout << "\nBlocking Road " << from << " -> " << to << ":" << endl;
    if (graph.blockRoad(from, to))
        cout << "Road Blocked Successfully." << endl;
    else
        cout << "Road already blocked or road does not exist." << endl;
}

void unblockRoad(Graph &graph, char from, char to)
{
    cout << "\nUnblocking Road " << from << " -> " << to << ":" << endl;
    if (graph.unblockRoad(from, to))
        cout << "Road Unblocked Successfully." << endl;
    else
        cout << "Road already unblocked or road does not exist." << endl;
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
        choice = displayMenu();
        system("clear");
        cin.clear();
        cin.ignore();
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
            emergencyVehicleRouting(graph, eVehicles);
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
            cout << "Exiting Simulation. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
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