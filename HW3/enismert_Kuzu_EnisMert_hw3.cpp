#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

/*
Author: Enis Mert Kuzu 28174
Date: November 2021
Description:The aim of this code creating a 2D linked list to allocate bus line and their stops.
To allocate bus lines define a singly dynamic linked list and to allocate busstops define a doubly linked list.
After allocation,user can add busline or stops and delete them with main function.
*/
struct busStop {
	string busStopName;
	busStop *left;
	busStop *right;
	busStop::busStop()
	{
		busStopName="";
		left=NULL;
		right=NULL;
	}
	busStop::busStop(string bus_stop,busStop *l,busStop *r)
	{
		busStopName=bus_stop;
		left=l;
		right=r;
	}
};
struct busLine {
	string busLineName;
	busLine *next;
	busStop *busStops;
	busLine::busLine()
	{
		busLineName="";
		next=NULL;
		busStops=NULL;
	}
	busLine::busLine(string busline_name,busLine *n,busStop *s)
	{
		busLineName=busline_name;
		next=n;
		busStops=s;
	}
};

busLine* head = nullptr;
busLine *adding_busline(busLine *head) //defining a function to find a last busline location
{
	busLine*ptr=head;
	while (ptr->next!=NULL)
	{
		ptr=ptr->next;
	}
		return ptr; // return the location of end of the busline linked list 
}
busStop *findleft_busstops(busStop*stop_head) // defining a function to find a end of the linked list to add new node;
{
	while (stop_head->right!=NULL)
	{
		stop_head=stop_head->right;
	}
	return stop_head; // return node that points to NULL
}
busStop* finding_busstop(busStop*stop_head,string stop_name) // defining a function to find a spesific busstop location 
{
	busStop *ptr=stop_head;
	while (ptr !=NULL && ptr->busStopName != stop_name) // loop until busstop name is found
	{
		ptr=ptr->right;
	}
	return ptr; // return the location of busstop as a pointer

}
busLine* finding_prev_busline(busLine*head,string busline) //defining a function  to find busline before known busline
{
	busLine*ptr=head;
	busLine *prev=head;
	while (ptr !=NULL && ptr->busLineName !=busline)
	{
		prev=ptr; // taking the previous busline
		ptr=ptr->next; 
	}

		return prev; //return the pointer that points to next busline of known busline
}
void printMainMenu() //main menu function;
{
	cout << endl<<endl;
	cout <<"I***********************************************I"<<endl
	<<"I 0 - EXIT PROGRAM I"<<endl
	<<"I 1 - PRINT LINES I"<<endl
	<<"I 2 - ADD BUS LINE I"<<endl
	<<"I 3 - ADD BUS STOP I"<<endl
	<<"I 4 - DELETE BUS LINE I"<<endl
	<<"I 5 - DELETE BUS STOP I"<<endl
	<<"I 6 - PATH FINDER I"<<endl
	<<"I***********************************************I"<<endl
	<<">>";
	cout << endl;
}
bool consistencyCheck() {
	busLine* currBL = head; //a global variable
	while(currBL) 
	{
		busStop* currBS = currBL->busStops;
		while(currBS)
		{
			busStop* rightBS = currBS->right;
			if(rightBS && rightBS->left != currBS) 
			{
			cout << "Inconsistency for " << currBL->busLineName
			<< " " << currBS->busStopName << endl;
			return false;
			}
			currBS = currBS->right;
		}
		currBL = currBL->next;
	}
	return true;
}
void printBusLines() //printing all bus lines in the linked list
{
	cout<<endl;
	busLine *ptr=head; //taking head of linked list
	busStop *stop_ptr; //defining busstop pointer to use busstops
	while (ptr !=NULL)
	{
		cout<<ptr->busLineName<<": "; //printing busline name
		stop_ptr=ptr->busStops; //defining stop_ptr as a busstops pointer
		while (stop_ptr != NULL) // loop for until the end of the busstops
		{
			if (stop_ptr->right !=NULL) //if not at the end of busstops, write the name of busstop and  put <-> symbol 
			{
				cout<<stop_ptr->busStopName<<" <-> ";
			}
			else // if stop_ptr reaches the end of linked list,just print the name of the bus stop
			{
				cout<<stop_ptr->busStopName;
			}
			stop_ptr=stop_ptr->right; // to move next stop
		}
		cout<<endl;
		ptr=ptr->next; // to move next busline
	}
}
bool busline_check(string busline_name,busLine*& busline_pointer) //bus line checking for whether bus line exist or not
{
	busLine *ptr=head;
	while (ptr !=NULL && ptr->busLineName != busline_name) // loop for until end of the busline linked list to find busline_name
	{
		ptr=ptr->next;
	}
	if (ptr==NULL) //if ptr has reached its end, bus line could not be found.
	{
		return false;
	}
	else // if ptr is not NULL , there is a busline for this busline_name
	{
		busline_pointer=ptr; // return the location of this busline as a reference
		return true; 
	}
}
bool busstop_check(busStop *bus_stop_head,string bus_stop_name) // checking for whether bus line exist with this busstop or not in the double linked list
{
	busStop *stop=bus_stop_head; // defining the head of  bus stops of the specific bus line
	while (stop !=NULL && stop->busStopName != bus_stop_name) // loop for until end of the busstops double linked list to find busstop
	{
		stop=stop->right;
	}
	if (stop==NULL) //if stop has reached its end, busstop could not be found.
	{
		return false;
	}
	else //if ptr is not NULL , there is a busstop for this bus_stop_name
	{
		return true;
	}
}
void print_bus_line(busStop* pointer_stops) //printing one bus line getting with busstops pointer
{
	while (pointer_stops !=NULL) // loop for until the end of the busstops
	{
		if (pointer_stops->right==NULL) //if spointer_stops reaches the end of linked list,just print the name of the bus stop
		{
			cout<<pointer_stops->busStopName;
		}
		else //if not at the end of busstops, write the name of busstop and  put <-> symbol
		{
			cout<<pointer_stops->busStopName<<" <-> ";
		}
		pointer_stops=pointer_stops->right; //moving next busstop
	}
	cout<<endl;
}
bool head_busstop_check(busLine*head,string busstop) //busstop checking for whether bus line exist or not in the 2D linked list(entire linked list)
{
	busLine*temp=head; //getting head of busline linked list
	bool cond=true;
	while (temp !=NULL && cond) 
	{
		busStop *stops_ptr=temp->busStops; // getting head of busstops double linked list
		while (stops_ptr !=NULL && stops_ptr->busStopName !=busstop) //move right until find matching bus stop
		{
			stops_ptr=stops_ptr->right;
		}
		if (stops_ptr !=NULL && stops_ptr->busStopName==busstop) //if busstop match, changing cond to stop first while loop
		{
			cond=false;
		}
		temp=temp->next; //moving next node of busline
	}
	return cond; //if cond equals to false, there is a busstop
}

void addBusLine() //adding a busline to 2D linked list
{
	string busline,busstop;
	busLine*busline_pointer;
	cout<<"Enter the name of the new bus line (0 for exit to main menu)."<<endl;
	cin>>busline;
	while(busline !="0" && busline_check(busline,busline_pointer))//if busline_check return true, there is a bus line
	{
		cout<<"Bus line already exists: enter a new one (0 for exit to main menu)."<<endl;
		cin>>busline; // getting new busline 
	}
	if (busline != "0") // if bus lines are not equal to 0, continuing adding
	{
		busLine *temp=new busLine(busline,head,NULL); //dynamically create a new bus line and add the bus line to the beginning of the linked list
		cout<<"Enter the name of the next bus stop (enter 0 to complete)"<<endl;
		cin>>busstop; //getting busstops for this busline
		if (busstop=="0") // if user not write a busline,showing appropriate message
		{
			cout<<"You are not allowed to add an empty bus line"<<endl;
		}
		else
		{
			while (busstop != "0") //loop for go back to the main menu when bus stop equal to 0 
			{
				if(busstop_check(temp->busStops,busstop)) //checking bus stop existence in the linked list with busstop_check function
				{
				cout<<"Bus stop already exists in the line"<<endl;
				cout<<"Enter the name of the next bus stop (enter 0 to complete)"<<endl;
				cin>>busstop;
				}
				else // if not exist
				{
					busStop *stop_ptr; //defining stop_ptr to allocate busstop location
					if (temp->busStops==NULL) //if the bus stops are empty on the bus line, placing it as the first stop
					{
						stop_ptr=new busStop(busstop,NULL,NULL); //dynamically add the first stop
						temp->busStops=stop_ptr; // updating the head of busstops
					}
					else // if there is a busstop in the busline 
					{
						//adding the new stop to the right
						busStop *previous=findleft_busstops(temp->busStops); //finding the last busstop
						stop_ptr=new busStop(busstop,previous,NULL);//dynamically add the first sto
						previous->right=stop_ptr;//updating the last busstop to point the new busstop
					}
					cout<<"Enter the name of the next bus stop (enter 0 to complete)"<<endl;
					cin>>busstop;
				}
			}
			cout<<"The bus line information is shown below"<<endl;
			cout<<busline<<": ";
			busStop *temp_ptr=temp->busStops; //defining temp value to print all stops
			print_bus_line(temp_ptr); // printing all bus stops of this bus line with print_bus_line function
			cout<<endl;
			cout<<"Are you sure? Enter (y/Y) for yes (n/N) for no?"<<endl; //asking if the user wants to add
			char select;
			cin>>select;
			if (select =='y' || select=='Y') // if wants to add
			{
				temp->next=head; //connecting the temp to rest of the list
				head=temp; // updating head of busline linked list
				printBusLines();
			}
			else // delete all user-given nodes if they don't want to add
			{
				busStop *temp_bus_stops_head=temp->busStops;
				while (temp_bus_stops_head != NULL)
				{
					busStop *next_stop=temp_bus_stops_head->right;
					delete temp_bus_stops_head; // first delete bus stops
					temp_bus_stops_head=next_stop;  
				}
				head=temp->next; //update the head and delete the temp
				delete temp; 
			}
		}
	}
}
void addBusStop() //adding a bussttop for given busline
{
	string busline,busstop;
	busLine*busline_pointer; //defining a pointer to allocate the bus line
	cout<<"Enter the name of the bus line to insert a new bus stop (0 for main menu)"<<endl;
	cin>>busline;
	if(busline !="0") // if user not type 0 
	{
		if (busline_check(busline,busline_pointer)==false) //Checking if busline is in linked list or not with busline_check function
		{
			cout<<"Bus line cannot be found. Going back to previous menu."<<endl;
		}
		else // if busline is in linked list
		{
			cout<<"The bus line information is shown below"<<endl;
			cout<<busline<<": ";
			busStop *stops_pointer=busline_pointer->busStops; //defining pointer that points the busstops
			print_bus_line(stops_pointer); //print this busline information with print_bus_line function
			cout<<"Enter the name of the new bus stop"<<endl;
			cin>>busstop;
			if (busstop_check(stops_pointer,busstop)) // checking whether the  busstop exists or not
			{
				cout<<"Bus stop already exists. Going back to previous menu."<<endl;
			}
			else
			{
				cout<<"Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)"<<endl;
				string previous_stop;
				cin>>previous_stop;
				if (previous_stop=="0") //if previos stop is 0 ,that means a stop to be added to the beginning 
				{
					busStop *temp=new busStop(busstop,NULL,busline_pointer->busStops); //create temp and put to head of the linked list of busstops
					busline_pointer->busStops->left=temp; //connecting old bussstops (rest of the linked list) with temp
					busline_pointer->busStops=temp; //changing the head of the busstop with temp
					printBusLines();
				}
				else //if previos stop is not 0,getting previous stop
				{
					bool cond=true; // to stop while loop
					while (cond && busstop_check(stops_pointer,previous_stop)==false)
					{
						cout<<"Bus stop does not exist. Typo? Enter again (0 for main menu)"<<endl;
						cin>>previous_stop;
						if (previous_stop=="0") //if user enter 0, going to main menu so, stop the loop
						{
							cond=false; //to stop while loop
						}
					}
					if (previous_stop !="0") //if previous stop is not 0, continue with adding busstop
					{
						busStop *Prev_s_ptr=finding_busstop(stops_pointer,previous_stop);//finding the previous_stop location with finding_busstop function
						if (Prev_s_ptr->right==NULL) // if we are going to add to the end of Busstops linked list
						{
							busStop *temp=new busStop(busstop,Prev_s_ptr,NULL);
							Prev_s_ptr->right=temp;
						}
						else //If we do not add to the beginning and the end of busstops
						{
							busStop *next_s_ptr=Prev_s_ptr->right; // getting the location of the bus stop on the right
							busStop *temp=new busStop(busstop,Prev_s_ptr,next_s_ptr); // create temp dynamically and allocating left and right busstops
							Prev_s_ptr->right=temp; // connecting right of previous Busstop to temp
							next_s_ptr->left=temp; // connecting left of next Busstop to temp
						}
						printBusLines();
					}
				}
			}

		}
	}
	
}
void deleteBusLine()
{
	string busline;
	busLine*busline_pointer;
	cout<<"Enter the name of the bus line to delete"<<endl;
	cin>>busline;
	if (busline_check(busline,busline_pointer)) //Checking if busline is in linked list or not with busline_check function
	{
		//if true ,continue with deleting
		busStop *stops_head=busline_pointer->busStops; //getting head of busstops
		busStop*temp;
		while (stops_head!=NULL) // first, deleting busstops
		{
			temp=stops_head->right; // going right and delete
			delete stops_head;
			stops_head=temp; 
		}
		if (head->busLineName==busline)
		{
			head=head->next;
			delete busline_pointer;
			printBusLines();
		}
		else
		{
			busLine*prev; //finding the previous bus line and match it with the next bus line from the deleted one
			prev=finding_prev_busline(head,busline); //finding the location of previos one
			prev->next=busline_pointer->next; //match it with the next bus line
			delete busline_pointer;
			printBusLines();
		}
	}
	else //if there is no busline
	{
		cout<<"Bus line cannot be found. Going back to the previous (main) menu."<<endl;
	}
}
void deleteBusStop()
{
	string bus_line,bus_stop;
	busLine*busline_pointer;
	cout<<"Enter the name of the bus line to delete a new bus stop (0 for main menu)"<<endl;
	cin>>bus_line;
	if(bus_line !="0") //checking if the user enters 0 to return main 
	{
		if (busline_check(bus_line,busline_pointer)) // if true, there is a busline.
		{
			cout<<"The bus line information is shown below"<<endl;
			cout<<bus_line<<": ";
			print_bus_line(busline_pointer->busStops);  //Printing busline with print_bus_line function
			cout<<"Enter the name of the bus stop to delete (0 for main menu)"<<endl;
			cin>>bus_stop;
			bool cond=true;
			if (bus_stop !="0") //checking if the user enters 0 to return main menu
			{
				while (cond && busstop_check(busline_pointer->busStops,bus_stop)==false) //  if busstop is not in linked list pf Busstops ,function will return false
				{
					cout<<"Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)"<<endl;
					cin>>bus_stop; // getting the new stop
					if (bus_stop=="0")
					{
						cond=false; //  to stop while loop, to return main menu
					}
				}
				if (cond==true) //if condition is true then user didn't enter 0 so,continue with deleting busstop
				{
					//getting bus stop location
					busStop *temp = finding_busstop(busline_pointer->busStops,bus_stop);
					if (temp->left == NULL && temp->right !=NULL) //if the first busttop is deleted
					{
						temp->right->left=temp->left; //updating the left of the next stop with left of the deleted one
						busline_pointer->busStops=temp->right; // uptading head of busstops
						printBusLines();
					}
					else if(temp->right==NULL && temp->left != NULL) // if deleting the last Busstop
					{
						temp->left->right=temp->right; //connecting right side to left side
						printBusLines();
					}
					else if (temp->left == NULL && temp->right ==NULL) // if one stop in the busline, deleting this busstop and deleting busline
					{
						busline_pointer->busStops=NULL;
						//finding the previous bus line and match it with the next bus line from the deleted one
						if (head->busLineName==bus_line) // if the bus line is at the beginning of the head
						{
							head=head->next;
							delete busline_pointer;
							printBusLines();
						}
						else // if busline is not at the beginning
						{
							busLine*prev; //finding the previous bus line and match it with the next bus line from the deleted one
							prev=finding_prev_busline(head,bus_line); //finding the location of previos one
							prev->next=busline_pointer->next; //match it with the next bus line
							delete busline_pointer;
							printBusLines();
						}	
					}
					else //deleting bus stops,if bus stop is not located at the end or beginning
					{
						temp->right->left=temp->left; //connecting the left side to the right side
						temp->left->right=temp->right; //connecting the right side to the left 
						delete temp; // deleting busstop
						printBusLines();
					}
				}
			}
		}
		else // if busline not in the linked list
		{
			cout<<"Bus line cannot be found. Going back to previous (main) menu."<<endl;
		}
	}
}
void pathfinder()
{
	string start,stop;
	cout<<"Where are you now?"<<endl;
	cin>>start;
	if (head_busstop_check(head,start)) // checking start busstop whether exist in linked list or not
	{
		cout<<"Bus stop does not exist in the table. Going back to previous menu."<<endl;
	}
	else // if start point exist ,getting the stop point
	{
		cout<<"Where do you want to go?"<<endl;
		cin>>stop;
		if (head_busstop_check(head,stop))//checking stop busstop whether exist in linked list or not
		{
			cout<<"Bus stop does not exist in the table. Going back to previous menu."<<endl;
		}
		else
		{
			if (start==stop)
			{
				cout<<"You are already at that bus stop"<<endl;
			}
			else
			{
				bool cond=false;
				busLine*temp_head=head; 
				busStop*temp_busstop;
				while (temp_head !=NULL)
				{
					bool before_exist=false;
					temp_busstop=temp_head->busStops; // taking the head of busstops 
					while (temp_busstop !=NULL && temp_busstop->busStopName!=start) //finding the start point 
					{
						if (temp_busstop->busStopName==stop) //while finding start point, if you pass the stopped bus stop, changing before_exist condition
						{
							before_exist=true;
						}
						temp_busstop=temp_busstop->right;
					}
					if (temp_busstop !=NULL)// if it has not reached the end of the busline, there is a starting busstop
					{
						if (before_exist)  // if stopped busstop passed while finding start point
						{
							//printing to the left direction 
							cout<<"You can go there by "<<temp_head->busLineName<<": ";
							while (temp_busstop->busStopName !=stop)
							{
								cout<< temp_busstop->busStopName << " -> ";
								temp_busstop=temp_busstop->left;
							}
							cout<<stop<<endl; //printing stopped busstop
						}
						else //if stopped busstop has not passed, stopped bus stop in the right side of the starting busstop
						{
							busStop*print_temp=temp_busstop;
							while (print_temp !=NULL && print_temp->busStopName !=stop) //finding the stopped busstop location
							{
								print_temp=print_temp->right;
							}
							if (print_temp==NULL && cond==false)  // if there is no path nad cond is false
							{
								cout<<"Sorry no path from "<<start<<" to "<<stop<<" could be found."<<endl;
							}
							else
							{
								//printing to the right direction 
								cout<<"You can go there by "<<temp_head->busLineName<<": ";
								while (temp_busstop->busStopName !=stop)
								{
									cout<<temp_busstop->busStopName<<" -> ";
									temp_busstop=temp_busstop->right;
								}
								cout<<stop<<endl;//printing stopped busstop
								cond=true;//if it is a pathway, the condition will be true
							}
						}
					}
					temp_head=temp_head->next; //moving next busline
				}
			}
		}
	}
}
void delete_all_bus(busLine*head) //delete all buslines and busstops before the program finish.
{
	busLine*busline_pointer;
	busStop*temp;
	busStop*temp_busstops;
	while (head !=NULL)
	{
		temp_busstops=head->busStops;
		while (temp_busstops != NULL)
		{
			temp=temp_busstops->right;
			delete temp_busstops;
			temp_busstops=temp;
		}
		busline_pointer=head->next;
		delete head;
		head=busline_pointer;
	}
}

void processMainMenu() //Main menu function
{
	string input;
	printMainMenu();
	cout << "Please enter your option " << endl;
	cin >> input;
	while (input !="0")
	{
		if(!consistencyCheck())
		{
			cout << "There are inconsistencies. Exit." << endl;
			input="0";
		}
		else
		{
			if (input=="1")
			{
				printBusLines();
			}
			else if (input=="2")
			{
				addBusLine();
			}
			else if (input=="3")
			{
				addBusStop();
			}
			else if (input=="4")
			{
				deleteBusLine();
			}
			else if (input=="5")
			{
				deleteBusStop();
			}
			else if (input=="6")
			{
				pathfinder();
			}
			else
			{
				cout << "Invalid option: please enter again" << endl;
			}
			printMainMenu();
			cout << "Please enter your option " << endl;
			cin >> input;
		}
	}
	delete_all_bus(head); //deleting all buslines and busstops before program finish
	cout << "Thanks for using our program" << endl;
}//processMainMenu
int main() {
	ifstream reader_file; // defining ifstream variable to read txt
	string file_name,file_line;// defining string varible for file name and lines
	string bus_line,bus_stop;
	cout<<"Please enter file name: ";
	cin>>file_name; // getting file name
	reader_file.open(file_name.c_str());// open a txt file with reader_file
	busLine *temp_busline=NULL;
	while (getline(reader_file,file_line))
	{
		istringstream lines(file_line);
		lines>>bus_line;
		bus_line=bus_line.substr (0,bus_line.length()-1); //removing ':' charachter from end of the string
		if (head==nullptr)
		{
			temp_busline= new busLine(bus_line,NULL,NULL);
			head=temp_busline;
		}
		else
		{
			temp_busline=adding_busline(head); //find the end of the busline linked list to add new one to the end
			temp_busline->next=new busLine(bus_line,NULL,NULL); //adding new busline
			temp_busline=temp_busline->next; //updating last element of busline linked list 
		}
		while (lines>>bus_stop) // getting bus_stops with istringstream
		{
			busStop* temp_busStop;
			if (temp_busline->busStops==NULL) // if there is no bus tops in the busstops of busline
			{
				temp_busline->busStops= new busStop(bus_stop,NULL,NULL); 
			}
			else // if there is at leas one busstop in the busstops of busline
			{
				temp_busStop = findleft_busstops(temp_busline->busStops); //finding last busstop location
				busStop *new_stop=new busStop(bus_stop,temp_busStop,NULL); //allocating new busstop
				temp_busStop->right = new_stop; //uptading end of the busstops
			}
		}
	}
	reader_file.close();
	processMainMenu();
	system("pause");
	return 0;
}