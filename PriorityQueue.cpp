#include <iostream>
#include <cstring>
#include <stdexcept>

using namespace std;

class road_network
{
private:
    // Road representation with dynamic memory management
    class road
    {
    public:
        char *start;
        char *end;
        int priority;

        road(const char *s, const char *e, int p) : priority(p)
        {
            start = new char[strlen(s) + 1];
            end = new char[strlen(e) + 1];
            strcpy(start, s);
            strcpy(end, e);
        }
        road() {}
        ~road()
        {
            delete[] start;
            delete[] end;
        }

        // Copy constructor
        road(const road &other) : priority(other.priority)
        {
            start = new char[strlen(other.start) + 1];
            end = new char[strlen(other.end) + 1];
            strcpy(start, other.start);
            strcpy(end, other.end);
        }

        // Assignment operator
        road &operator=(const road &other)
        {
            if (this != &other)
            {
                delete[] start;
                delete[] end;

                priority = other.priority;
                start = new char[strlen(other.start) + 1];
                end = new char[strlen(other.end) + 1];
                strcpy(start, other.start);
                strcpy(end, other.end);
            }
            return *this;
        }
    };

    // Dynamic Priority Queue with heap implementation
    class priority_queue
    {
    private:
        road *heap;
        int capacity;
        int size;

        void resize()
        {
            int new_capacity = capacity == 0 ? 1 : capacity * 2;
            road *new_heap = new road[new_capacity];

            for (int i = 0; i < size; ++i)
            {
                new_heap[i] = heap[i];
            }

            delete[] heap;
            heap = new_heap;
            capacity = new_capacity;
        }

        void swap(road &a, road &b)
        {
            road temp = a;
            a = b;
            b = temp;
        }

        void heapify_up(int index)
        {
            while (index > 0)
            {
                int parent = (index - 1) / 2;
                if (heap[index].priority > heap[parent].priority)
                {
                    swap(heap[index], heap[parent]);
                    index = parent;
                }
                else
                {
                    break;
                }
            }
        }

        void heapify_down(int index)
        {
            while (true)
            {
                int left = 2 * index + 1;
                int right = 2 * index + 2;
                int largest = index;

                if (left < size && heap[left].priority > heap[largest].priority)
                    largest = left;
                if (right < size && heap[right].priority > heap[largest].priority)
                    largest = right;

                if (largest != index)
                {
                    swap(heap[index], heap[largest]);
                    index = largest;
                }
                else
                {
                    break;
                }
            }
        }

    public:
        priority_queue() : heap(nullptr), capacity(0), size(0) {}

        ~priority_queue()
        {
            delete[] heap;
        }

        void push(const char *start, const char *end, int priority)
        {
            if (size == capacity)
            {
                resize();
            }

            heap[size] = road(start, end, priority);
            heapify_up(size);
            size++;
        }

        road pop()
        {
            if (size == 0)
            {
                throw runtime_error("Priority queue is empty");
            }

            road top = heap[0];
            heap[0] = heap[size - 1];
            size--;

            if (size > 0)
            {
                heapify_down(0);
            }

            return top;
        }

        bool is_empty() const
        {
            return size == 0;
        }

        void print() const
        {
            for (int i = 0; i < size; ++i)
            {
                cout << "Road: " << heap[i].start << " -> " << heap[i].end
                     << ", Priority: " << heap[i].priority << "\n";
            }
        }
    };
};
