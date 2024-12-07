#include <iostream>
#include <cstring> // For string handling
#define MAX_SIZE 100 // Maximum number of roads

using namespace std;

// Structure to represent a road
struct Road {
    char intersection1[20]; // Name of first intersection
    char intersection2[20]; // Name of second intersection
    int priority;           // Priority of the road (higher = higher priority)
};

// Custom Priority Queue for Roads
class PriorityQueue {
private:
    Road heap[MAX_SIZE];
    int size;

    // Swap two elements
    void swap(Road& a, Road& b) {
        Road temp = a;
        a = b;
        b = temp;
    }

    // Heapify upwards (used after insertion)
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].priority > heap[parent].priority) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Heapify downwards (used after deletion)
    void heapifyDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && heap[left].priority > heap[largest].priority)
                largest = left;
            if (right < size && heap[right].priority > heap[largest].priority)
                largest = right;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    PriorityQueue() : size(0) {}

    // Insert a new road into the priority queue
    void push(const char* intersection1, const char* intersection2, int priority) {
        if (size >= MAX_SIZE) {
            cout << "Priority queue is full.\n";
            return;
        }
        strcpy(heap[size].intersection1, intersection1);
        strcpy(heap[size].intersection2, intersection2);
        heap[size].priority = priority;
        heapifyUp(size);
        size++;
    }

    // Remove and return the highest-priority road
    Road pop() {
        if (size == 0) {
            cout << "Priority queue is empty.\n";
            Road temp;
strcpy(temp.intersection1, "");
strcpy(temp.intersection2, "");
temp.priority = -1;
return temp;
        }
        Road top = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        return top;
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Print the priority queue (for debugging)
    void print() const {
        for (int i = 0; i < size; i++) {
            cout << "Road: " << heap[i].intersection1 << " -> " << heap[i].intersection2
                 << ", Priority: " << heap[i].priority << "\n";
        }
    }
};

// Graph Class
class Graph {
private:
    struct Edge {
        char intersection2[20];
        char status[20];
    };

    struct Vertex {
        char name[20];
        Edge edges[MAX_SIZE];
        int edgeCount;
    };

    Vertex vertices[MAX_SIZE];
    int vertexCount;

public:
    Graph() : vertexCount(0) {}

    // Add a new vertex (intersection)
    void addVertex(const char* name) {
        strcpy(vertices[vertexCount].name, name);
        vertices[vertexCount].edgeCount = 0;
        vertexCount++;
    }

    // Add an edge (road) between two intersections
    void addEdge(const char* intersection1, const char* intersection2, const char* status) {
        for (int i = 0; i < vertexCount; i++) {
            if (strcmp(vertices[i].name, intersection1) == 0) {
                strcpy(vertices[i].edges[vertices[i].edgeCount].intersection2, intersection2);
                strcpy(vertices[i].edges[vertices[i].edgeCount].status, status);
                vertices[i].edgeCount++;
                return;
            }
        }
        cout << "Intersection " << intersection1 << " not found.\n";
    }

    // Push roads into the priority queue based on their status
    void populateQueue(PriorityQueue& pq) {
        for (int i = 0; i < vertexCount; i++) {
            for (int j = 0; j < vertices[i].edgeCount; j++) {
                const char* status = vertices[i].edges[j].status;
                int priority = 0;

                if (strcmp(status, "Blocked") == 0)
                    priority = 100;
                else if (strcmp(status, "Under Repair") == 0)
                    priority = 50;
                else if (strcmp(status, "Clear") == 0)
                    priority = 10;

                pq.push(vertices[i].name, vertices[i].edges[j].intersection2, priority);
            }
        }
    }
};

int main() {
    Graph graph;
    PriorityQueue pq;

    // Add intersections
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");

    // Add roads
    graph.addEdge("A", "B", "Blocked");
    graph.addEdge("A", "C", "Under Repair");
    graph.addEdge("B", "C", "Clear");

    // Populate the priority queue
    graph.populateQueue(pq);

    // Process roads
    while (!pq.isEmpty()) {
        Road top = pq.pop();
        cout << "Processing road: " << top.intersection1 << " -> " << top.intersection2
             << " with priority " << top.priority << "\n";
    }

    return 0;
}
