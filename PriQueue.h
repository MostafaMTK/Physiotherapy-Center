#pragma once
#include <iostream>
using namespace std;
class Patient;
ostream& operator<<(ostream& o, Patient* p);
template < typename T>
class PriNode
{
private:
	T item;		// A data item
	int pri;	//priority of the item
	PriNode<T>* next; // Pointer to next node
public:
	PriNode(const T& r_Item, int PRI)
	{
		setItem(r_Item, PRI);
		next = nullptr;
	}
	void setItem(const T& r_Item, int PRI)
	{
		item = r_Item;
		pri = PRI;
	}
	void setNext(PriNode<T>* nextNodePtr)
	{
		next = nextNodePtr;
	}

	T getItem(int& PRI) const
	{
		PRI = pri;
		return item;
	}

	PriNode<T>* getNext() const
	{
		return next;
	}

	int getPri() const
	{
		return pri;
	}
};

template <typename T>
class PriQueue
{
protected:
	PriNode<T>* head;
	int count;
public:
	PriQueue() : head(nullptr) {}

	~PriQueue() {
		T tmp;
		int p;
		while (dequeue(tmp, p));
	}

	//insert the new node in its correct position according to its priority
	void enqueue(const T& data, int priority) {
		PriNode<T>* newNode = new PriNode<T>(data, priority);

		if (head == nullptr || priority > head->getPri()) {

			newNode->setNext(head);
			head = newNode;
			count++;
			return;
		}

		PriNode<T>* current = head;
		while (current->getNext() && priority <= current->getNext()->getPri()) {
			current = current->getNext();
		}
		newNode->setNext(current->getNext());
		current->setNext(newNode);
		count++;
	}

	bool dequeue(T& topEntry, int& pri) {
		if (isEmpty())
			return false;

		topEntry = head->getItem(pri);
		PriNode<T>* temp = head;
		head = head->getNext();
		delete temp;
		count--;
		return true;
	}

	bool peek(T& topEntry, int& pri) {
		if (isEmpty())
			return false;

		topEntry = head->getItem(pri);
		pri = head->getPri();
		return true;
	}

	bool isEmpty() const {
		return head == nullptr;
	}

	void Print()
	{
		PriNode<T>* ptr = head;
		int priority;
		if (ptr)
		{
			priority = ptr->getPri();
			cout << ptr->getItem(priority);
			ptr = ptr->getNext();
		}
		while (ptr)
		{
			cout << ", " << ptr->getItem(priority);
			ptr = ptr->getNext();
		}
	}
	//Get Count Function
	int GetCount()
	{
		return count;
	}
};