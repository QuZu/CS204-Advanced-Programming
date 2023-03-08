#include <iostream>
#include "StudentQueue.h"
#include <string>
using namespace std;

//I utilized int queue codes in the lecture and adapted them to my program with some changes.

StudentQueue::StudentQueue() // Constructor.It generates an empty dynamic queue   
{
	front = NULL;
	rear = NULL;   
}

//Function enqueue inserts the student struct at the rear of the queue.
void StudentQueue::enqueue(Student node)  
{       
	if (isEmpty())   //if the queue is empty
	{	//make student node the first element
		front = new Student(node.id,node.student_name,node.func_name,node.next); // creating a new student node
		rear = front;
	}
	else  //if the queue is not empty
	{	//add student node after rear
		rear->next = new Student(node.id,node.student_name,node.func_name,node.next);// creating a new student node
		rear = rear->next; // shifting rear of queue
	} 
}

// Function dequeue removes the student struct at the front of the queue, and copies it into node
void StudentQueue::dequeue(Student &node)
{
	Student *temp;
	if (isEmpty())
	{
		cout << "Attempting to dequeue on empty queue, exiting program...\n";
		exit(1);
	}
	else //if the queue is not empty
	{	//return front's node, advance front and delete old front
		node = *front;
		temp = front;
		front = front->next;
		delete temp;      
	}
}

// Function isEmpty returns true if the student queue is empty, and false otherwise.             *
bool StudentQueue::isEmpty() const
{
	if (front == NULL)
		return true;
	else 
		return false;
}

// Function clear dequeues all the elements in the student queue.                             *
void StudentQueue::clear()
{
	Student node;   // Dummy variable for dequeue

	while(!isEmpty())
		dequeue(node); //delete all elements
	#ifdef _DEBUG
		cout << " Student queue cleared\n";
	#endif
}
StudentQueue::~StudentQueue()
{
	Student node;   // Dummy variable for dequeue
	while(!isEmpty())
		dequeue(node); //delete all elements
	/*#ifdef _DEBUG
		cout << " Destructor for Student queue called \n";
	#endif*/
}