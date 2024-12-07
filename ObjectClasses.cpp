// Road, Vehicle, etc structes
#include <string>
using namespace std;
struct Road
{
    char from;
    char to;
    int travel_time;
    string status;
    bool is_closed;
    Road(char from, char to,int weight, string status)
    {
        this->from=from;
        this->to=to;
        travel_time=weight;
        this->status=status;
        if(status=="Clear")
        {
            is_closed=false;
        }
        else
        {
            is_closed=true;
        }
    }
};
// Since there is no additional information in intersection we can just pass char to template of vertex to store the name
struct Intersection
{
    char name;
};
struct Vehicle
{
    string id;
    string priority;
};