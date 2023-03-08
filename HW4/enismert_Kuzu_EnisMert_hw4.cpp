#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "InstQueue.h"
#include "StudentQueue.h"
#include "CommonStack.h"
using namespace std;
/*
Author: Enis Mert Kuzu 28174
Date: November 2021
Description: It is a program created to provide a certain number of services to academic staff and students.
While the requests of the academic staff are kept in the static instructor queue, another dynamic queue keeps the request of the students.
The processing of services happens in the common dynamic stack.
*/

InstQueue instructorsQueue(5); //defining static queue with size 5 for instructors
StudentQueue studentsQueue; //defining a dynamic students queue for students
CommonStack Shared_stack; // defining common stack to perform desired functions

struct Commands_Struct // defining a commands struct to store function commands in the linked list
{
	string com_name;
	Commands_Struct *down;
	Commands_Struct::Commands_Struct() //default constructor
	{
		com_name="";
		down=NULL;
	}
	Commands_Struct::Commands_Struct(string name,Commands_Struct *ptr) //constructor with f_name and pointer
	{
		com_name=name;
		down=ptr;
	}
};
struct Function_Struct //defining a function struct to store function in the linked list
{
	string func_name;
	Function_Struct *next;
	Commands_Struct *down;
	Function_Struct::Function_Struct() // default constructor
	{
		func_name="";
		next=NULL;
		down=NULL;
	}
	//constructor with function name and pointers that points to commands and next function struct
	Function_Struct::Function_Struct(string fonk,Function_Struct *input_next,Commands_Struct *input_down)
	{
		func_name=fonk;
		next=input_next;
		down=input_down;
	}
};

Function_Struct *services_head=NULL; //creating NULL pointer for the function linked list at the beginning
void print_stack(CommonStack &stack) // defining a function to print a stack values
{
	CommonStack temp; // temporary stack
	string value;
	if (stack.isEmpty()) // if stack is empty 
	{
		cout << "The stack is empty"<<endl;
	}
	else 
	//if not empty, printing without changing the values and size in the common stack with the help of a temporary stack
	{
		while (!stack.isEmpty()) //getting values for temp stack
		{
			stack.pop(value);
			temp.push(value);
		}
		while (!temp.isEmpty()) //reassign the values to the common stack and print it in first in first out(FIFO) format
		{
			temp.pop(value);
			cout<<value<<endl;
			stack.push(value);
		}
	}
}
void print_Services(Function_Struct*&head) // defining a function to print  linked list of services
{
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"PRINTING AVAILABLE SERVICES <FUNCTIONS> TO BE CHOSEN FROM THE USERS"<<endl;
	cout<<"-------------------------------------------------------------------"<<endl<<endl<<endl;
	Function_Struct *ptr=head; // getting head of the linked list
	while (ptr !=NULL)
	{
		cout<<ptr->func_name<<":"<<endl;
		Commands_Struct *comm=ptr->down; // getting head of commands in specific function
		while (comm !=NULL)
		{
			if (comm->down==NULL)
			{
				cout<<comm->com_name<<".";
				comm=comm->down;
			}
			else
			{
				cout<<comm->com_name<<", ";
				comm=comm->down;
			}
		}
		cout<<endl<<endl;
		ptr=ptr->next;
	}
}
bool check_services(Function_Struct*&head, string function_name) //defining a function to check whether function name in linked list or not
{
	bool cond=false;
	Function_Struct *ptr=head;
	while (ptr !=NULL && ptr->func_name !=function_name) //loop until find the function name
	{
		ptr=ptr->next;
	}
	if (ptr !=NULL && ptr->func_name ==function_name) //if find the function name in linked list return true, otherwise return false 
	{
		cond=true;
	}
	return cond;
}
Function_Struct *function_finder(Function_Struct*&head,string f_name)//defining a function to get the pointer of a specific function 
{
	Function_Struct *temp=head;
	while ( temp->func_name !=f_name) //loop until find a function name
	{
		temp=temp->next;
	}
	return temp; //return the pointer of this function
}
void addInstructorRequest()
{
	string f_name;
	cout<<"Add a service <function> that the instructor wants to use:"<<endl;
	cin>>f_name;
	if (check_services(services_head,f_name)==false) //checking whether function is in linked list with check_services function
	{
		cout<<"The requested service <function> does not exit"<<endl;
		cout<<"GOING BACK TO MAIN MENU"<<endl<<endl;
	}
	else // if function is in linked list
	{
		//getting id and name of instructor
		string inst_name;
		int inst_id;
		cout<<"Give instructor's name: ";
		cin>>inst_name;
		cout<<"Give instructor's ID <an int>: ";
		cin>>inst_id;
		Instructor temp(f_name,inst_name,inst_id); //defining temporary struct for enqueue operation
		instructorsQueue.enqueue(temp); //sending queue 
		cout<<"Prof. "<<inst_name<<"'s service request of "<<f_name<<" has been put in the instructor's queue."<<endl
			<<"Waiting to be served..."<<endl<<endl;
	}
}
void addStudentRequest()
{
	string f_name;
	cout<<"Add a service <function> that the student wants to use:"<<endl;
	cin>>f_name;
	if (check_services(services_head,f_name)==false) //checking whether function is in linked list with check_services function
	{
		cout<<"The requested service <function> does not exit"<<endl;
		cout<<"GOING BACK TO MAIN MENU"<<endl<<endl;
	}
	else // if function is in linked list
	{
		//getting id and name of student
		string std_name;
		int std_id;
		cout<<"Give student's name: ";
		cin>>std_name;
		cout<<"Give student's ID <an int>: ";
		cin>>std_id;
		Student temp(std_id,std_name,f_name,NULL); ////defining temporary struct for enqueue operation
		studentsQueue.enqueue(temp); //Sending to enqueue function and regenerate as a new struct, after that add to queue dynamically.
		cout<<std_name<<"'s service request of "<<f_name<<" has been put in the student's queue."<<endl
			<<"Waiting to be served..."<<endl<<endl;
	}
}
void processARequest(string functionName)
{
	Function_Struct *ptr=function_finder(services_head,functionName); // getting function pointer that points to functionName in the linked list
	Commands_Struct *c_ptr=ptr->down; //getting head of commands of this function
	string define_command;
	int counter=0;
	while (c_ptr !=NULL)
	{
		string command=c_ptr->com_name; //getting command from ptr
		stringstream ss(command); //reading the command with stringstream 
		string subcommand;
		ss>>subcommand; //and assigning it to subcommand
		if(subcommand =="define") // if command define a varible
		{
			//process the define command
			define_command=functionName+": "+command; //creating a new string for stack
			Shared_stack.push(define_command); // pushing this string to shared stack
			counter++; //to store how many definitions there are
		}
		else if (subcommand=="call")
		{
			// process the call command
			string f_name;
			ss>>f_name; // getting f_name with stringstream
			cout<<"Calling "<<f_name<<" from "<<functionName<<endl;
			// the recursion goes here
			processARequest(f_name); //resending it to processArequest
		}
		else
		{
			//print the stack
			cout<<"PRINTING THE STACK TRACE:"<<endl;
			print_stack(Shared_stack); //printing a stack with print_stack function
		}
		c_ptr=c_ptr->down; //moving next command
	}
	while (counter !=0) //removing as many definitions as the number of definitions (counter) so that all definitions of the function are removed from the stack
	{
		// delete this function’s data from the top of the stack
		Shared_stack.pop(define_command);
		counter--;
	}

	cout<<functionName<<" is finished. Clearing the stack from it's data... "
	<<endl;
	system("pause");
	if (Shared_stack.isEmpty()) //if shared stack is empty 
	{
		cout<<"The stack is empty."<<endl;
	}
}
void processARequest()
{
	Instructor inst;
	Student std;
	if (!instructorsQueue.isEmpty()) 	//if instructors queue is not empty, process the next request
	{
		cout<<"Processing instructor queue... "<<endl;
		instructorsQueue.dequeue(inst); //dequeing first element of instructor queue
		cout<<"Processing prof. "<<inst.Ins_name<<"'s request <with ID "<<inst.Ins_id<<"> of service <function>:"<<endl;
		cout<<inst.service_name<<endl;
		processARequest(inst.service_name); //sending which service operation will be performed
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else if (!studentsQueue.isEmpty()) //if instructors queue is empty and student’s not,then process the next student request
	{
		cout<<"Instructors queue is empty.Proceeding with students queue..."<<endl;
		studentsQueue.dequeue(std);//dequeing first element of student queue
		cout<<"Processing "<<std.student_name<<"'s request <with ID "<<std.id<<"> of service <function>:"<<endl;
		cout<<std.func_name<<endl;
		cout<<"-------------------------------------------------------------------"<<endl;
		processARequest(std.func_name);//sending which service operation will be performed
		cout<<"GOING BACK TO MAIN MENU"<<endl;
	}
	else
	{
		// otherwise…
		cout<<"Both instructor's and student's queue is empty.\nNo request is processed."
			<<endl<<"GOING BACK TO MAIN MENU"<<endl;
	}
}
void delete_linkedlist(Function_Struct*&head) // defining a function to delete services linked list
{
	Function_Struct *temp_head=head;
	while (head !=NULL)
	{
		Commands_Struct* ptr=head->down;
		Commands_Struct *temp;
		while (ptr !=NULL)
		{
			temp=ptr;
			ptr=ptr->down;
			delete temp;
		}
		temp_head=head;
		head=head->next;
		delete temp_head;
	}
}


int main()
{
	string prefer,f_preference;
	string file_name,file_line;
	cout<<"If you want to open a service <function> defining file,"<<endl;
	cout<<"then press (Y/y) for 'yes', otherwise press any single key"<<endl;
	cin>>prefer;
	if (prefer=="Y" || prefer=="y") //if user want to open a file
	{
		bool cond=true;
		bool cont=true;
		do
			{
				cout<<"Enter the input file name: ";
				cin>>file_name; //getting file name
				ifstream reader_file;
				reader_file.open(file_name.c_str()); //open a file with ifstream
				if (reader_file.fail()) // if the file does not open
				{
					cond=false; //changing the cond to stop while loop
					cout << "Could not open file " << file_name << endl;
					cout<<"Program exiting..."<<endl;
					cont=false; //Changing cont so that the program does not continue
				}
				else // if the file open
				{
					//reading the file
					Function_Struct*function_ptr=NULL;
					while (getline(reader_file,file_line))
					{
					
						if (file_line[file_line.length()-1]==':') // reading function names and sending it to linked list
						{
							file_line=file_line.substr(0,file_line.length()-1);
							if (services_head==NULL) //if it is the first function so the list of services is empty.
							{
								//sending the first function to a linked list
								services_head= new Function_Struct(file_line,NULL,NULL);
								function_ptr=services_head; 
								
							}
							else //if linked list is not empty
							{
								Function_Struct*ptr=services_head;
								while (ptr->next !=NULL) //finding the last node of the linked list 
								{
									ptr=ptr->next;
								}
								//adding the new function to the end of the linked list
								Function_Struct *temp=new Function_Struct(file_line,NULL,NULL);
								ptr->next=temp;
								function_ptr=temp;
							}
						}
						else // reading function commands if file_line is not a function
						{
							file_line=file_line.substr(0,file_line.length()-1);
							if (function_ptr->down==NULL) // if adding for the first time to commands node
							{
								Commands_Struct*temp= new Commands_Struct(file_line,NULL);
								function_ptr->down=temp;
							}
							else //if any command came before or command node exist
							{
								Commands_Struct* comm= function_ptr->down;
								while (comm->down !=NULL) //finding the end of the command in linked list
								{
									comm=comm->down;
								}
								//adding the new command to the end of commands in the linked list
								Commands_Struct*temp= new Commands_Struct(file_line,NULL);
								comm->down=temp;
							}
						}
					}
					reader_file.close();
					cout<<"Do you want to open another service defining file?"<<endl;
					cout<<"Press (Y/y) for 'yes', otherwise press any single key"<<endl;
					cin>>f_preference;
					if (f_preference =="Y" || f_preference =="y")
					{
						cond=true; // if the user want to continue opening a file
					}
					else
					{
						cond=false; // if user do not want open a file,changing the condition and stop the while loop
					}
				}
			} while(cond);
			if (cont) //continuing to main menu if all files entered by the user have been read without error
			{
				print_Services(services_head); //printing the services 
				while (true) //main menu 
				{
					cout << endl;
					cout<<"**********************************************************************"<<endl
						<<"**************** 0 - EXIT PROGRAM *************"<<endl
						<<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST *************"<<endl
						<<"**************** 2 - ADD A STUDENT SERVICE REQUEST *************"<<endl
						<<"**************** 3 - SERVE (PROCESS) A REQUEST *************"<<endl
						<<"**********************************************************************"<<endl;
					cout << endl;
					int option;
					cout << "Pick an option from above (int number from 0 to 3): ";
					cin>>option;
					switch (option)
					{
						case 0:
							cout<<"PROGRAM EXITING ... "<<endl;
							system("pause");
							exit(0);
						case 1:
							addInstructorRequest();
							break;
						case 2:
							addStudentRequest();
							break;
						case 3:
							processARequest();
							break;
						default:
							cout<<"INVALID OPTION!!! Try again"<<endl;
					}//switch
				}//while (true)
			}
			//deleting operation for all dynamically allocated memory and ý used destructor for static ýnstructor queue,students queue and common stack 
		delete_linkedlist(services_head); // deleting function linked list before the finishing program	
	}		
	else //if user doesn't want to open any files
	{
		cout<<"PROGRAM EXITING ..."<<endl;
		//deleting operation for all dynamically allocated memory and ý used destructor for static ýnstructor queue,students queue and common stack 
		delete_linkedlist(services_head); // deleting function linked list before the finishing program
	}
	system("pause");
	return 0;
}
