// Road, Vehicle, etc structes
#include <string>
#define HIGH 0
#define MEDIUM 1
#define LOW 2
using namespace std;

//Typedefining Intersection as it has single member or no method
typedef char Intersection;
struct Road
{
    Intersection from;
    Intersection to;
    int travel_time;
    string status;
    bool is_closed;
    Road()
    {
        this->from = 'a';
        this->to = 'a';
        travel_time = 0;
        status = "Clear";
        is_closed = false;
    }
    Road(char from, char to, int weight, string status)
    {
        this->from = from;
        this->to = to;
        travel_time = weight;
        this->status = status;
        if (status == "Clear")
        {
            is_closed = false;
        }
        else
        {
            is_closed = true;
        }
    }
    Road(char from, char to, int weight)
    {
        this->from = from;
        this->to = to;
        travel_time = weight;
        status = "Clear";
        is_closed = false;
    }
    void changeStatus(string new_status)
    {
        status = new_status;
        if (status == "Clear")
        {
            is_closed = false;
        }
        else
        {
            is_closed = true;
        }
    }
};
// to change Road status use changeStatus method

struct Vehicle
{
    string id;
    char source;
    char destination;
    int priority;
    Vehicle(string id=0, char s='a', char d='a')
    {
        this->id = id;
        source = s;
        destination = d;
        priority = LOW;
    }
    Vehicle(string id, char s, char d, int priority)
    {
        this->id = id;
        source = s;
        destination = d;
        this->priority = priority;
    }
    Vehicle(string id, char s, char d, string priority)
    {
        this->id = id;
        source = s;
        destination = d;
        if (priority == "High")
        {
            this->priority = HIGH;
        }
        else if (priority == "Medium")
        {
            this->priority = MEDIUM;
        }
        else
        {
            this->priority = LOW;
        }
    }
};