#include <iostream>
using namespace std;

template <class StackObject>
struct StackNode
{
    StackObject data;
    StackNode<StackObject> *next = nullptr;
};

template <class StackObject>
class Stack
{
    StackNode<StackObject> *top;
public:
    Stack()
    {
        top = nullptr;
    }
    Stack(StackObject entry)
    {
        top = new StackNode<StackObject>;
        top->data = entry;
    }
    bool isEmpty()
    {
        return top == nullptr;
    }
    bool push(StackObject entry)
    {
        if (entry == StackObject())
        {
            return false;
        }
        if (this->isEmpty())
        {
            top = new StackNode<StackObject>;
            top->data = (entry);
            top->next = nullptr;
            return true;
        }
        else
        {
            StackNode<StackObject> *newNode = new StackNode<StackObject>;
            newNode->data = (entry);
            newNode->next = top;
            top = newNode;
            return true;
        }
        return true;
    }

    StackObject pop()
    {
        StackNode<StackObject> *deletionNode = top;
        if (this->isEmpty())
        {
            return StackObject();
        }
        StackObject temp = top->data;
        top = top->next;
        delete deletionNode;
        return temp;
    }

    StackObject peek()
    {
        if (this->isEmpty())
        {
            return StackObject();
        }
        return top->data;
    }
    int length()
    {
        int count = 0;
        StackNode<StackObject> *currentNode = top;
        while (currentNode != nullptr)
        {
            count++;
            currentNode = currentNode->next;
        }
        return count;
    }
    void display()
    {
        cout << "{";
        StackNode<StackObject> *currentNode = top;
        while (currentNode)
        {
            cout << currentNode->data << ", ";
            currentNode = currentNode->next;
        }
        if (currentNode == top)
            cout << "}" << endl;
        else
            cout << "\b\b}" << endl;
    }
    void clear()
    {
        while (!this->isEmpty())
        {
            pop();
        }
    }
    Stack(Stack &stack)
    {
        this->top = new StackNode<StackObject>;
        this->top->data = stack.top->data;
        StackNode<StackObject> *current = stack.top;
        StackNode<StackObject> *new_node = this->top;
        while (current->next != nullptr)
        {
            new_node->next = new StackNode<StackObject>;
            new_node = new_node->next;
            current=current->next;
            new_node->data = current->data;
        }
    }
    Stack<StackObject>& operator=(Stack<StackObject> &stack)
    {
        this->clear();
        this->top = new StackNode<StackObject>;
        this->top->data = stack.top->data;
        StackNode<StackObject> *current = stack.top;
        StackNode<StackObject> *new_node = this->top;
        while (current->next != nullptr)
        {
            new_node->next = new StackNode<StackObject>;
            new_node = new_node->next;
            current=current->next;
            new_node->data = current->data;
        }
        return *this;
    }
    ~Stack()
    {
        clear();
    }
};
