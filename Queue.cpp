#include <iostream>
using namespace std;
/*
Can make additional overloaded enqueue and dequeue functions for multiple items such as
bool enqueue(QueueObject* array, intsizeOfArray);
objact* dequeue(int noOfItems)
can also be my Array Data Structure instead of built in *
*/

template <class QueueObject>
struct QueueNode
{
    QueueObject data;
    QueueNode<QueueObject> *next = nullptr;
};

template <class QueueObject>
class Queue
{
    QueueNode<QueueObject> *front = nullptr;
    QueueNode<QueueObject> *rear = nullptr;

public:
    Queue() {}
    Queue(QueueObject entry)
    {
        front = new QueueNode<QueueObject>;
        front->data = entry;
        rear = front;
    }
    bool isEmpty()
    {
        return front == nullptr;
    }
    bool enqueue(QueueObject entry)
    {
        if (entry == QueueObject())
        {
            return false;
        }
        QueueNode<QueueObject> *newQueueNode = new QueueNode<QueueObject>;
        newQueueNode->data = entry;
        if (this->isEmpty())
        {
            front = newQueueNode;
            rear = front;
        }
        else
        {
            rear->next = newQueueNode;
            rear = newQueueNode;
        }
        return true;
    }
    QueueObject dequeue()
    {
        QueueObject result;
        if (this->isEmpty())
        {
            result = QueueObject();
        }
        else if (front == rear)
        {
            result = front->data;
            delete front;
            front = nullptr;
            rear = nullptr;
        }
        else
        {
            result = front->data;
            QueueNode<QueueObject> *deletionQueueNode = front;
            front = front->next;
            delete deletionQueueNode;
        }
        return result;
    }
    QueueObject peek()
    {
        if (this->isEmpty())
            return QueueObject();
        else
            return front->data;
    }
    int length()
    {
        int count = 0;
        QueueNode<QueueObject> *currentNode = front;
        while (currentNode != nullptr)
        {
            count++;
            currentNode = currentNode->next;
        }
        return count;
    }
    void clear()
    {
        while (!this->isEmpty())
        {
            dequeue();
        }
    }
    Queue(Queue<QueueObject> &queue_to_copy)
    {
        QueueNode<QueueObject> *current = queue_to_copy.front;
        QueueNode<QueueObject> *new_node = new QueueNode<QueueObject>;
        new_node->data = current->data;
        front = new_node;
        rear = front;
        while ((current->next != nullptr))
        {
            current = current->next;
            new_node->next = new QueueNode<QueueObject>;
            new_node = new_node->next;
            new_node->data = current->data;
        }
    }
    Queue<QueueObject> &operator=(Queue<QueueObject> &queue_to_copy)
    {
        this->clear();
        QueueNode<QueueObject> *current = queue_to_copy.front;
        QueueNode<QueueObject> *new_node = new QueueNode<QueueObject>;
        new_node->data = current->data;
        front = new_node;
        rear = front;
        while ((current->next != nullptr))
        {
            current = current->next;
            new_node->next = new QueueNode<QueueObject>;
            new_node = new_node->next;
            new_node->data = current->data;
        }
        return *this;
    }

    ~Queue()
    {
        clear();
    }
};
