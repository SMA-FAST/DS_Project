#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class road_network
{
private:
    // Road structure with single-character names
    struct road
    {
        char s;  // start intersection
        char e;  // end intersection
        int d;   // distance
        bool c;  // is congested
        bool m;  // is under maintenance
    };

    // Dynamic array management for roads
    class road_manager
    {
    private:
        road* roads;
        int capacity;
        int count;

        void resize()
        {
            int new_capacity = capacity == 0 ? 1 : capacity * 2;
            road* new_roads = new road[new_capacity];
            
            for (int i = 0; i < count; ++i)
            {
                new_roads[i] = roads[i];
            }
            
            delete[] roads;
            roads = new_roads;
            capacity = new_capacity;
        }

    public:
        road_manager() : roads(nullptr), capacity(0), count(0) {}

        ~road_manager()
        {
            delete[] roads;
        }

        void add(char start, char end, int distance, bool congested, bool maintenance)
        {
            if (count == capacity)
            {
                resize();
            }
            
            roads[count] = {start, end, distance, congested, maintenance};
            count++;
        }

        road* get_roads()
        {
            return roads;
        }

        int get_count() const
        {
            return count;
        }

        // Find roads connecting specific intersections
        void find_connections(char start, char end)
        {
            cout << "Connections for route " << start << " -> " << end << ":\n";
            for (int i = 0; i < count; ++i)
            {
                if ((roads[i].s == start && roads[i].e == end) || 
                    (roads[i].s == end && roads[i].e == start))
                {
                    cout << "Road: " << roads[i].s << " - " << roads[i].e 
                         << ", Distance: " << roads[i].d 
                         << ", Congested: " << (roads[i].c ? "Yes" : "No")
                         << ", Maintenance: " << (roads[i].m ? "Yes" : "No") << "\n";
                }
            }
        }
    };

    // Dynamic intersection tracking
    class intersection_manager
    {
    private:
        char* intersections;
        int capacity;
        int count;

        void resize()
        {
            int new_capacity = capacity == 0 ? 1 : capacity * 2;
            char* new_intersections = new char[new_capacity];
            
            for (int i = 0; i < count; ++i)
            {
                new_intersections[i] = intersections[i];
            }
            
            delete[] intersections;
            intersections = new_intersections;
            capacity = new_capacity;
        }

    public:
        intersection_manager() : intersections(nullptr), capacity(0), count(0) {}

        ~intersection_manager()
        {
            delete[] intersections;
        }

        void add(char intersection)
        {
            // Prevent duplicates
            for (int i = 0; i < count; ++i)
            {
                if (intersections[i] == intersection)
                {
                    return;
                }
            }

            if (count == capacity)
            {
                resize();
            }
            
            intersections[count] = intersection;
            count++;
        }

        void print_intersections()
        {
            cout << "Intersections: ";
            for (int i = 0; i < count; ++i)
            {
                cout << intersections[i] << " ";
            }
            cout << "\n";
        }

        int get_count() const
        {
            return count;
        }
    };

    road_manager roads;
    intersection_manager intersections;

public:
    // Add road with automatic intersection tracking
    void add_road(char start, char end, int distance, bool congested = false, bool maintenance = false)
    {
        // Add intersections
        intersections.add(start);
        intersections.add(end);

        // Add road
        roads.add(start, end, distance, congested, maintenance);
    }

    // Analyze network details
    void analyze_network()
    {
        cout << "Network Analysis:\n";
        
        // Print intersections
        intersections.print_intersections();
        
        // Print road details
        cout << "Total Roads: " << roads.get_count() << "\n";
        
        road* road_list = roads.get_roads();
        for (int i = 0; i < roads.get_count(); ++i)
        {
            cout << "Road: " << road_list[i].s << " -> " << road_list[i].e 
                 << ", Distance: " << road_list[i].d 
                 << ", Congested: " << (road_list[i].c ? "Yes" : "No")
                 << ", Maintenance: " << (road_list[i].m ? "Yes" : "No") << "\n";
        }
    }

    // Find road connections
    void find_road_connections(char start, char end)
    {
        roads.find_connections(start, end);
    }
};

// int main()
// {
//     road_network network;

//     // Add roads
//     network.add_road('A', 'B', 50, true, false);
//     network.add_road('B', 'C', 70, false, true);
//     network.add_road('A', 'C', 120, false, false);
//     network.add_road('C', 'D', 30, true, true);

//     // Analyze network
//     network.analyze_network();

//     // Find specific road connections
//     network.find_road_connections('A', 'B');
//     network.find_road_connections('B', 'C');

//     return 0;
// }