//Road, Vehicle, etc classes
#include<string>
using namespace std;
class Road
{
    char from_intersection;
    char to_intersection;
    string status;
};
class Intersection
{
    char name;
};
class Vehicle
{
    string id;
    string priority;
};