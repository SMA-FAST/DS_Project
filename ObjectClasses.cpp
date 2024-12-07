//Road, Vehicle, etc structes
#include<string>
using namespace std;
struct Road
{
    char from_intersection;
    char to_intersection;
    string status;
};
//Since there is no additional information in intersection we can just pass char to template of vertex to store the name
struct Intersection
{
    char name;
};
struct Vehicle
{
    string id;
    string priority;
};