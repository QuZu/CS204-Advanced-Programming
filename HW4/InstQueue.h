#ifndef INSTQUEUE_H
#define INSTQUEUE_H
using namespace std;
//I utilized int queue codes in the lecture and adapted them to my program with some changes.
struct Instructor
{
	string Ins_name;
	int Ins_id;
	string service_name;
	Instructor::Instructor()
	{
		Ins_name="";
		Ins_id=-1;
		service_name="";
	}
	Instructor::Instructor(string service,string name,int id)
	{
		Ins_name=name;
		Ins_id=id;
		service_name=service;
	}

};

class InstQueue
{
private:
	struct Instructor *queueArray;
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	InstQueue(int);  //constructor, parameter is capacity
	~InstQueue(); //destructor
	// Member functions.
	void enqueue(Instructor); 
	void dequeue(Instructor &);
  	bool isEmpty() const; 
  	bool isFull() const;
  	void clear();  //removes all elements
};
#endif