//version 2.2
#include <iostream>
using namespace std;

template <class ListObject>

struct ListNode
{
    ListObject data;
    ListNode<ListObject> *next = nullptr;
    ListNode(ListObject data) : data(data), next(nullptr) {}
    ListNode(){}
};

template <class ListObject>
class LinkedList
{
public:
    ListNode<ListObject> *head = nullptr;
    ListNode<ListObject> *tail = nullptr;
    int size = 0;

    LinkedList()
    {
    }
    LinkedList(ListObject entry)
    {
        insertAtFirst(entry);
    }
    bool insertAtFirst(ListObject entry)
    {
        if (head != nullptr)
        {
            ListNode<ListObject> *newNode = new ListNode<ListObject>;
            newNode->data = entry;
            newNode->next = head;
            head = newNode;
            size++;
            return true;
        }
        head = new ListNode<ListObject>(entry);
        tail = head;
        size++;
        return true;
    }
    bool append(ListObject entry)
    {
        if (head == nullptr)
        {
            return insertAtFirst(entry);
        }
        tail->next = new ListNode<ListObject>(entry);
        tail = tail->next;
        tail->data = entry;
        size++;
        return true;
    }

    bool insert(int position, ListObject entry)
    {
        if (position == 0) // head
        {
            return insertAtFirst(entry);
        }
        else if (position == (size)) // tail
        {
            return append(entry);
        }
        // position x
        int currentPosition = 1;
        ListNode<ListObject> *currentListNode = head;
        while (currentListNode->next && currentPosition < position)
        {
            currentListNode = currentListNode->next;
            currentPosition += 1;
        }
        if (currentPosition == position)
        {
            ListNode<ListObject> *newNode = new ListNode<ListObject>;
            newNode->data = entry;
            newNode->next = currentListNode->next;
            currentListNode->next = newNode;
            size++;
            return true;
        }
        return false; // position not in list node range
    }

    bool replace(ListObject value, ListObject entry)
    {
        ListNode<ListObject> *currentListNode = head;
        while (currentListNode->next && currentListNode->data != value)
        {
            currentListNode = currentListNode->next;
        }
        if (currentListNode->data == value && currentListNode != nullptr)
        {
            ListNode<ListObject> *newNode = new ListNode<ListObject>;
            newNode->data = entry;
            newNode->next = currentListNode->next;
            currentListNode->next = newNode;
            size++;
            return true;
        }
        return false; // value not found
    }
    bool removeAtFirst()
    {
        ListNode<ListObject> *deletionListNode = head;
        if (deletionListNode != nullptr)
        {
            if (head == tail)
            {
                head = tail = nullptr;
                delete deletionListNode;
                size--;
                return true;
            }
            else
            {
                head = head->next;
                delete deletionListNode;
                size--;
                return true;
            }
        }
        return false; // list is empty
    }
    bool removeAtLast()
    {
        ListNode<ListObject> *currentListNode = head;
        ListNode<ListObject> *previousListNode = nullptr;
        while (currentListNode && currentListNode->next)
        {
            previousListNode = currentListNode;
            currentListNode = currentListNode->next;
        }
        if (currentListNode != nullptr && previousListNode != nullptr)
        {

            delete currentListNode;
            previousListNode->next = nullptr;
            tail = previousListNode;
            size--;
            return true;
        }
        else if (currentListNode != nullptr) // only one node in the list
        {
            head = tail = nullptr;
            size--;
        }
        return false; // List is empty
    }
    bool removeAtValue(ListObject value)
    {
        if (head == nullptr)
        {
            return false;
        }
        if (head->data == value)
        {
            removeAtFirst();
        }
        ListNode<ListObject> *currentListNode = head;
        ListNode<ListObject> *previousListNode = nullptr;

        while (currentListNode->next != nullptr && currentListNode->data != value)
        {
            previousListNode = currentListNode;
            currentListNode = currentListNode->next;
        }
        if (currentListNode->data == value && currentListNode->next == nullptr)
        {
            // value at tail and tail!=head
            previousListNode->next = nullptr;
            tail = previousListNode;
            size--;
            delete currentListNode;
            return true;
        }
        if (currentListNode->data == value) // value between head and tail
        {
            previousListNode->next = currentListNode->next;
            size--;
            delete currentListNode;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool removeAtPosition(int position)
    {
        if (position == 0) // head
        {
            return removeAtFirst();
        }
        else if (position == (size - 1)) // tail
        {
            return removeAtLast();
        }
        // position between head and tail
        int currentPosition = 1;
        ListNode<ListObject> *previousListNode = head;
        while (previousListNode->next && currentPosition < position)
        {
            previousListNode = previousListNode->next;
            currentPosition += 1;
        }
        if (currentPosition == position)
        {
            ListNode<ListObject> *deletionListNode = previousListNode->next;
            previousListNode->next = deletionListNode->next;
            delete deletionListNode;
            size--;
            return true;
        }
        return false; // position not in list node range
    }
    ListObject& operator[](int position)
    {
        if (position == 0) // head
        {
            return head->data;
        }
        else if (position == (size - 1)) // tail
        {
            return tail->data;
        }
        // position between head and tail
        int currentPosition = 0;
        ListNode<ListObject> *currentListNode = head;
        while (currentListNode->next && currentPosition < position)
        {
            currentListNode = currentListNode->next;
            currentPosition += 1;
        }
        if (currentPosition == position)
        {
            return currentListNode->data;
        }
        cout << "List index out of bound, exiting";
        exit(0); // position not in list node range
    }
    void reverse() 
    {
    ListNode<ListObject> *curr = head, *prev = nullptr, *next;
    while (curr != nullptr) 
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}
    void empty()
    {
        while (head)
        {
            removeAtFirst();
        }
    }
    LinkedList operator=(LinkedList &rhs)
    {
        empty();
        ListNode<ListObject> *current = rhs.head;
        while (current != nullptr)
        {
            this->append(current->data);
            current = current->next;
        }
        return *this;
    }
    LinkedList(LinkedList &list_to_copy)
    {
        ListNode<ListObject> *current = list_to_copy.head;
        while (current != nullptr)
        {
            this->append(current->data);
            current = current->next;
        }
    }
    ~LinkedList()
    {
        empty();
    }
    void display()
    {
        cout << "{";
        ListNode<ListObject> *currentListNode = head;
        while (currentListNode)
        {
            cout << currentListNode->data << ", ";
            currentListNode = currentListNode->next;
        }
        if (currentListNode == head)
            cout << "}" << endl;
        else
            cout << "\b\b}" << endl;
    }
};

/*
int main()
{
    LinkedList<int> l;
    cout << "Empty: ";
    l.display();
    cout << "Size: " << l.size << endl;

    for (int i = 0; i < 20; i += 1)
    {
        l.insert(i, 10 * i);
    }
    cout << "LinkedList: ";
    l.display();
    cout << "Size: " << l.size << endl;
    l.append(11);
    cout << "Appended 11: ";
    l.display();
    cout << "Size: " << l.size << endl;
    l.removeAtValue(0);
    cout << "Remove Value 0: ";
    l.display();
    cout << "Size: " << l.size << endl;
    l.insertAtFirst(1);
    cout << "Inset Value 1 at first: ";
    l.display();
    cout << "Size: " << l.size << endl;
    l.removeAtFirst();
    cout << "Remove first: ";
    l.display();
    cout << "Size: " << l.size << endl;
    if (!l.removeAtValue(9))
        cout << "Failed: ";
    cout << "Remove Value 9: ";
    l.display();
    cout << "Size: " << l.size << endl;
    l.removeAtValue(50);
    cout << "Remove Value 50: ";
    l.display();
    cout << "Size: " << l.size << endl;
    l.removeAtLast();
    cout << "Remove Last: ";
    l.display();
    cout << "Size: " << l.size << endl;
    l.removeAtValue(190);
    cout << "Remove Value 190: ";
    l.display();
    cout << "Size: " << l.size << endl;
    LinkedList l2(l);
    cout << "l2: ";
    l2.display();
    cout << "Size: " << l2.size << endl;
    LinkedList<int>l3;
    l3=l2;
    cout << "l3: ";
    l3.display();
    cout << "Size: " << l3.size << endl;
    l.empty();
    cout << "Empty: ";
    l.display();
    cout << "Size: " << l.size << endl;
    l2=l;
    cout << "l2: ";
    l2.display();
    cout << "Size: " << l2.size << endl;
    cout<<l3[3];
    return 0;
}
*/
