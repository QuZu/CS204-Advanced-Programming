#ifndef COMMONSTACK_H
#define COMMONSTACK_H

using namespace std;
//I utilized int stack codes in the lecture and adapted them to my program with some changes.
struct StackNode
{
	string f_name_defined;
	StackNode *next;
};

class CommonStack
{
private:
	StackNode *top;

public:
	CommonStack(void); //constructor
	~CommonStack(void); //destructor
	// Member functions.
	void push(string);
	void pop(string &);
	bool isEmpty(void);
};
#endif // !COMMONSTACH_H
