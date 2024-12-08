// Functions Loading Data into Data Structures
#include "Graph.cpp"
#include "fstream"
using namespace std;
LinkedList<Intersection> loadIntersections()
{
    LinkedList<Intersection> l;
    for (int i = 'A'; i <= 'Z'; i++)
    {
        l.append(Intersection(i));
    }
    return l;
}
LinkedList<Road> readRoad(string filename = "road_network.csv")
{
    ifstream file(filename);
    string line;
    LinkedList<Road> l;
    getline(file, line);
    while (getline(file, line))
    {
        char inter_from = line[0];
        char inter_to = line[2];
        int cost = stoi(line.substr(4));
        l.append(Road(inter_from, inter_to, cost));
    }
    return l;
}
LinkedList<Vehicle> readEVehicle(string filename = "emergency_vehicles.csv")
{
    ifstream file(filename);
    string line, sub = "blank";
    LinkedList<Vehicle> l;
    getline(file, line);
    while (getline(file, line))
    {
        string id, priority;
        char inter_from, inter_to;
        int count = -1;
        for (int i = 0; i < line.length() + 1; i++)
        {
            if (line[i] == ',' || line[i] == '\n' || line[i] == '\r')
            {
                count++;
                sub = line.substr(0, i);
                line = line.substr(i + 1);
                i = -1;
            }
            if (i != -1 && line[i] == '\000')
            {
                sub = line.substr(0, i);
                count++;
            }
            if (sub == "")
            {
                return l;
            }
            switch (count)
            {
            case 0: // string read
                id = sub;
                break;
            case 1: // 1st inter
                inter_from = sub[0];
                break;
            case 2: // 2nd inter
                inter_to = sub[0];
                break;
            case 3: // 2nd inter
                priority = sub;
                break;
            default:
                break;
            }
        }
        l.append(Vehicle(id, inter_from, inter_to, priority));
    }
    return l;
}
LinkedList<Vehicle> readVehicle(string filename = "vehicles.csv")
{
    ifstream file(filename);
    string line, sub;
    LinkedList<Vehicle> l;
    getline(file, line);
    while (getline(file, line))
    {
        string id;
        char inter_from, inter_to;
        int count = -1;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',' || line[i] == '\n' || line[i] == '\r' || line[i] == '\000')
            {
                count++;
                sub = line.substr(0, i);
                line = line.substr(i + 1);
                i = 0;
            }
            switch (count)
            {
            case 0: // string read
                id = sub;
                break;
            case 1: // 1st inter
                inter_from = sub[0];
                break;
            case 2: // 2nd inter
                inter_to = sub[0];
                break;
            default:
                break;
            }
        }
        l.append(Vehicle(id, inter_from, inter_to));
    }
    return l;
}

// int main()
// {
//     LinkedList<Vehicle> vl = readVehicle();
//     cout << "Vehicles: \n";
//     for (int i = 0; i < vl.size; i++)
//     {
//         cout << vl[i].id << " " << vl[i].source << " " << vl[i].destination << " " << vl[i].priority << endl;
//     }
//     LinkedList<Vehicle> evl = readEVehicle();
//     for (int i = 0; i < evl.size; i++)
//     {
//         cout << evl[i].id << " " << evl[i].source << " " << evl[i].destination << " " << evl[i].priority << endl;
//     }
//     LinkedList<Road> rl = readRoad();
//     for (int i = 0; i < rl.size; i++)
//     {
//         cout << rl[i].from << " " << rl[i].to << " " << rl[i].travel_time << endl;
//     }
// }