#include <iostream>
#include <random>
using namespace std;
template <class HashObject>
struct HashNode
{
	int key = -1;
	HashObject data;
};
template <class HashObject>
class Hash
{
	int size;
	char probe;
	HashNode<HashObject> **table;

public:
	Hash(int size, char p)
	{
		this->size = size;
		probe = p;
		table = new HashNode<HashObject> *[size];
		for (int i = 0; i < size; i++)
			table[i] = nullptr;
	}
	~Hash()
	{
		for (int i = 0; i < size; i++)
		{
			if (table[i] != nullptr)
				delete table[i];
		}

		delete[] table;
	}
	int hashFunction(HashObject value)
	{
		return value % size;
	}
	int probing(int key)
	{
		int index = key;
		int count = 0;
		switch (probe)
		{
		case 'l':
		case 'L':
		{
			while (count++ < size)
			{

				if (table[index] == nullptr)
					return index;
				index = (key + count) % size;
			}
			break;
		}
		case 'q':
		case 'Q':
		{
			while (count++ < size)
			{
				if (table[index] == nullptr)
					return index;
				index = (key + (count * count)) % size;
			}
			break;
		}
		case 'r':
		case 'R':
		{
			while (count++ < 2 * size)
			{
				if (table[index] == nullptr)
					return index;
				index = (key + rand()) % size;
			}
			break;
		}
		}
		return -1;
	}
	int probing(int key, HashObject value)
	{
		int index = key;
		int count = 0;
		switch (probe)
		{
		case 'l':
		case 'L':
		{
			while (count++ < size)
			{
				if (table[index] != nullptr && table[index]->data == value)
					return index;
				index = (key + count) % size;
			}
			break;
		}
		case 'q':
		case 'Q':
		{
			while (count++ < 2 * size)
			{
				if (table[index] != nullptr && table[index]->data == value)
					return index;
				index = (key + (count * count)) % size;
			}
			break;
		}
		case 'r':
		case 'R':
		{
			while (count++ < 2 * size)
			{
				if (table[index] != nullptr && table[index]->data == value)
					return index;
					index = (key + rand()) % size;
			}
			break;
		}
		}
		return -1;
	}
	bool insert(HashObject data)
	{
		int index = probing(hashFunction(data));
		if (index == -1)
		{
			return false;
		}
		HashNode<HashObject> *node = new HashNode<HashObject>;
		node->key = index;
		node->data = data;
		table[index] = node;
		return true;
	}
	bool search(HashObject data)
	{
		int index = probing(hashFunction(data),data);
		if (index == -1)
		{
			cout << "Value: " << data << ", Does Not Exist.\n";
			return false;
		}
		cout << "Value: " << data << ", Does Exist.\n";
		return true;
	}
	void display()
	{
		cout << "{";
		for (int i = 0; i < size; i++)
		{
			if (table[i] != nullptr)
				cout << table[i]->data << ", ";
		}
		cout << "\b\b}";
	}
};
// int main()
// {
// 	int size;
// 	char p;
// 	cout << "Enter size of HashTable: ";
// 	cin >> size;
// 	cout << "Enter Probing Method(L/l: Linear Probing,Q/q :Quadratic Probing,R/r: Random Probing): ";
// 	cin >> p;
// 	Hash<int> h(size, p);
// 	// for (int i = size; i > 0; i--)
// 	// {
// 	// 	h.insert(i);
// 	// }
// 	h.insert(10);
// 	h.insert(30);
// 	h.insert(11);
// 	h.insert(21);
// 	h.insert(20);
// 	h.insert(44);
// 	int s;
// 	cout << "Enter value to search: ";
// 	cin >> s;
// 	h.search(s);
// 	h.display();

// 	return 0;
// }
