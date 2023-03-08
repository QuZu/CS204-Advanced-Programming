#ifndef STUDENTQUEUE_H
#define STUDENTQUEUE_H
using namespace std;
//I utilized int queue codes in the lecture and adapted them to my program with some changes.
struct Student
{
	int id;
	string student_name;
	string func_name;
	Student *next;
	Student::Student() //default constructor
	{
		id=-1;
		student_name="";
		func_name="";
		next=NULL;
	}
	Student::Student(int num,string name,string fun_name, Student*ptr) //constructor with variables
	{
		id = num;
		student_name=name;
		func_name=fun_name;
		next = ptr;
	}
};

class StudentQueue
{
private:
	// These track the front and rear of the queue.
	Student *front;
	Student *rear;	
public:
	// Constructor.
	StudentQueue();
	//destructor
	~StudentQueue();
	// Member functions.
	void enqueue(Student);
	void dequeue(Student &);
	bool isEmpty() const;     
	void clear();
};
#endif