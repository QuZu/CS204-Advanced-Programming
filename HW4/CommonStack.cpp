#include <iostream>
#include "CommonStack.h"
using namespace std;

//I utilized int stack codes in the lecture and adapted them to my program with some changes.

// Constructor to generate an empty stack.
CommonStack::CommonStack()
{
	top = NULL; 
}


// Member function push pushes the string that has function name and defined variable onto the stack.   
void CommonStack::push(string function_name_defined)
{
	StackNode *newNode;

	// Allocate a new node and store function name and defined variable
	newNode = new StackNode;
	newNode->f_name_defined=function_name_defined;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

// Member function pop, pops the value at the top of the stack off, and copies it into the variable passed as an f_defined                            *

void CommonStack::pop(string &f_defined)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "The stack is empty.\n";
	}
	else	// pop value off top of stack
	{
		f_defined = top->f_name_defined; // getting value of the top of stack and return the f_defined
		temp = top->next;
		delete top; // deleting the top of stack
		top = temp;
	}
}

// Member funciton isEmpty returns true if the stack is empty, or false otherwise.                     *
bool CommonStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}
//destructor for common stack
CommonStack::~CommonStack()
{ 
	string temp;
	while (!isEmpty())
	{
		pop(temp);
	}
	/*#ifdef _DEBUG
		cout << " Destructor for Common Stack called \n";
	#endif*/
}

