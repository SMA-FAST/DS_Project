#include <iostream>
#include <cstring>
#define MAX_SIZE 100

using namespace std;

// Structure to represent a road
struct Road {
    char intersection1[20];
    char intersection2[20];
    int travelTime; // Travel time in seconds
    bool isClosed;  // True if the road is closed
};

// Min-Heap for Roads
class MinHeap {
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
            if (heap[index].travelTime < heap[parent].travelTime) {
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
            int smallest = index;

            if (left < size && heap[left].travelTime < heap[smallest].travelTime)
                smallest = left;
            if (right < size && heap[right].travelTime < heap[smallest].travelTime)
                smallest = right;

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    MinHeap() : size(0) {}

    // Insert a new road into the heap
    void push(const char* intersection1, const char* intersection2, int travelTime, bool isClosed) {
        if (size >= MAX_SIZE) {
            cout << "Heap is full.\n";
            return;
        }
        strcpy(heap[size].intersection1, intersection1);
        strcpy(heap[size].intersection2, intersection2);
        heap[size].travelTime = travelTime;
        heap[size].isClosed = isClosed;
        heapifyUp(size);
        size++;
    }

    // Remove and return the road with the smallest travel time
    Road pop() {
        if (size == 0) {
            cout << "Heap is empty.\n";
            Road temp;
strcpy(temp.intersection1, "");
strcpy(temp.intersection2, "");
temp.travelTime = -1;
temp.isClosed = false;
return temp;

        }
        Road top = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        return top;
    }

    // Check if the heap is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Print the heap (for debugging)
    void print() const {
        for (int i = 0; i < size; i++) {
            cout << "Road: " << heap[i].intersection1 << " -> " << heap[i].intersection2
                 << ", Travel Time: " << heap[i].travelTime
                 << ", Closed: " << (heap[i].isClosed ? "Yes" : "No") << "\n";
        }
    }
};

// Parse road closures and populate the heap
void populateHeap(MinHeap& heap, const char roadClosureData[][3][20], int roadCount,
                  const char travelTimeData[][3][20], int travelCount) {
    for (int i = 0; i < travelCount; i++) {
        const char* intersection1 = travelTimeData[i][0];
        const char* intersection2 = travelTimeData[i][1];
        int travelTime = atoi(travelTimeData[i][2]);

        // Check if the road is closed
        bool isClosed = false;
        for (int j = 0; j < roadCount; j++) {
            if ((strcmp(intersection1, roadClosureData[j][0]) == 0 &&
                 strcmp(intersection2, roadClosureData[j][1]) == 0) ||
                (strcmp(intersection2, roadClosureData[j][0]) == 0 &&
                 strcmp(intersection1, roadClosureData[j][1]) == 0)) {
                isClosed = true;
                break;
            }
        }

        heap.push(intersection1, intersection2, travelTime, isClosed);
    }
}

int main() {
    MinHeap heap;

    // Sample road closures data
    const char roadClosureData[2][3][20] = {
        {"A", "B", "Blocked"},
        {"C", "D", "Blocked"}
    };

    // Sample travel time data
    const char travelTimeData[3][3][20] = {
        {"A", "B", "50"},
        {"C", "D", "70"},
        {"E", "F", "30"}
    };

    // Populate the heap
    populateHeap(heap, roadClosureData, 2, travelTimeData, 3);

    // Process the heap
    cout << "Initial Heap:\n";
    heap.print();

    cout << "\nProcessing Roads:\n";
    while (!heap.isEmpty()) {
        Road top = heap.pop();
        if (!top.isClosed) {
            cout << "Road: " << top.intersection1 << " -> " << top.intersection2
                 << ", Travel Time: " << top.travelTime << "\n";
        } else {
            cout << "Road: " << top.intersection1 << " -> " << top.intersection2 << " is closed.\n";
        }
    }

    return 0;
}
