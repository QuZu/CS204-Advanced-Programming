#include <iostream>
#include <string>
#include "InstQueue.h"
using namespace std;

//I utilized int queue codes in the lecture and adapted them to my program with some changes.

// Constructor - creates an empty Instructor queue with given number of elements 
InstQueue::InstQueue(int s)
{
	queueArray = new Instructor[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
}

// Function enqueue inserts the ýnstructor node at the rear of the queue.    
void InstQueue::enqueue(Instructor node)
{
	if (isFull())
    { 
		cout << "The queue is full. Instructor " << node.Ins_name << " not enqueued\n";
    }
	else
	{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new ýnstructor node.
		queueArray[rear] = node;
		// Update item count.
		numItems++;
	}
}

// Function dequeue removes the Insructor node at the front of the queue, and copies it into node.
void InstQueue::dequeue(Instructor &node)
{
	if (isEmpty())
	{
       cout << "Attempting to dequeue on empty queue, exiting program...\n";
       exit(1);
    }
	else
	{
		// Move front.
		front = (front + 1) % queueSize;
		// Retrieve the front item.
		node = queueArray[front];
		// Update item count.
		numItems--;
	}
}
// Function isEmpty returns true if the Instructor queue is empty, and false otherwise.  
bool InstQueue::isEmpty() const
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

// Function isFull returns true if the queue is full, and false otherwise.  
bool InstQueue::isFull() const
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

// Function clear resets the front and rear indices, and sets numItems to 0.     
void InstQueue::clear()
{
	front =  - 1;
	rear =  - 1;
	numItems = 0;
	#ifdef _DEBUG
		cout << "queue cleared\n";
	#endif
}
//destructor for instructor queue
InstQueue::~InstQueue ()
{
	/*#ifdef _DEBUG
	cout << " Instructor destructor called" << endl;
	#endif*/
	delete [] queueArray;
}