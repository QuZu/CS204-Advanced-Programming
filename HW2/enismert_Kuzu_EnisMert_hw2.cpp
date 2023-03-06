#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
/*
Author: Enis Mert Kuzu 28174
Date: October 2021
Description: This program was written to develop a Add/Drop period that stores the courses taken by students organized (sorted in ascending order) according to the name of the courses.
For this reason,Linked lists and coursenode struct were used to store courses and it's information.
*/
struct courseNode  // defining a course node struct 
{
string courseCode, courseName;  // defining strings for course name and code
vector<int> studentsAttendingIDs; // defining a vector to store students ids
courseNode * next; // defining pointer to points to next node
};
bool check_course(courseNode*head,string coursename,string courscode,courseNode*&ptr)
// defining a function to check whether course is in linked list or not and if course in linked list return position to reference parameter as a ptr
{
	bool cond=true; 
	while ( head!=NULL && cond && head->courseName<=coursename )
	//Since the course names are listed alphabetically, the loop continues until the course name comes alphabetically true before the next course.
	{
		if (head->courseName==coursename && head->courseCode==courscode) // if coursename and code match, cond will be false
		{
			cond=false; // changing cond to stop loop 
			ptr=head; // return course position to ptr using reference paramater
		}
		else
		{
			head=head->next; // if not match, move the next node until is null
		}
	}
	// after the while loop if condition false,this means course in the linked list and return true
	if (cond==false)  //
	{
		return true;
	}
	else
	{
		return false; // course is not in linked list and return false
	}
}
courseNode *adding_sorting_node(courseNode *ptr,string c_name,string c_code,courseNode *&course_pointer)
//defining a function that adds new course node in this linked list and sorting this linked list
{
	courseNode *loc=ptr; //getting head of linked list
	courseNode *temp=new courseNode; // dynamically defining a new course node
	if (ptr==NULL || ptr->courseName >= c_name) // checking for linked list whether empty or not and first element bigger than inserting element
	{
		//if linked list empty or first course name greater than the course name taken. Add this course at the beginning of linked list.
		temp->courseCode=c_code;
		temp->courseName=c_name;
		temp->next=ptr;
		ptr=temp; // new head(beginning od linked list) is ptr
		course_pointer=temp; //return course position to course_pointer using reference parameter
	}
	else
	{
		while (loc->next !=NULL && loc->next->courseName <=c_name)
		{
			loc=loc->next;
		}
		//new course node to be inserted just after the coursenode loc points
		temp->courseCode=c_code;
		temp->courseName=c_name;
		temp->next=loc->next; // take the next pointer of the temp pointer and connect the rest
		loc->next=temp; // take the pointer of previous one and connect previous linked list
		course_pointer=temp;//return course position to course_pointer using reference parameter
	} 
	return ptr;
}
void deleting_sorting_node(courseNode *&head,courseNode *deleted_ptr)//deleting course node using pointer of deleted coursenode
{
	courseNode *temp; //defining course node pointer to select deleted node 
	if (deleted_ptr==head) // if deleted course in the first node of linked list
	{
		head=head->next; //moving next node for head of linked list
		delete deleted_ptr; //deleting delete_ptr course node
	}
	else // if deleted course node not in head of linked list
	{
		temp=head;
		while (temp->next !=deleted_ptr)  // finding the previous position of delete_ptr 
		{
			temp=temp->next;
		}
		//after while loop, temp points to course node found before deleted_ptr
		temp->next=deleted_ptr->next; //temp->next points to next node of deleted_ptr
		delete deleted_ptr; // deleting delete_ptr course node
	}
}
void option_func(int &select) // defining function that prints options for user and getting select number as a referecne parameter
{
cout<<endl;
cout<<"Please select one of the choices:"<<endl;
cout<<"1. Add to List"<<endl<<"2. Drop from List"<<endl<<"3. Display List"<<endl<<"4. Finish Add/Drop and Exit"<<endl;
cin>>select;
}
void insert_id_and_sorting(vector<int>&id_vector,int id)
//defining function that insert the id to the proper position of sorted vector 
{
	int last = id_vector.size();  // size of vector before insertion
	id_vector.push_back(id);   // increase size of id_vector with inserting id at the end but inserted value is not important
	while (last > 0 && id_vector[last-1] > id)
	{    
		id_vector[last] = id_vector[last-1]; // shift right ids until the proper insertion index
		last--;   
    }
	id_vector[last] = id;  //after finding index,doing actual insertion 
}
void print_linkedlist(courseNode*ptr)
// defining a function to print the course informations with enrolled ids
{
	while (ptr !=NULL) // loop until end of the linked list
	{
		cout<<ptr->courseCode<<" "<<ptr->courseName<<":";
		for (int i = 0; i < ptr->studentsAttendingIDs.size(); i++) //getting ids from vector with for loop
		{
			cout<<" "<<ptr->studentsAttendingIDs[i];
		}
		cout<<endl;
		ptr=ptr->next;// moving next node
	}
}
int check_id(vector <int> &student_id, int id)
//defining a function that checks whether id in course vector or not and if id is in the vector return index
{
	// using bineary search for finding id
	int low_index = 0;						// possible starting  index
	int high_index= student_id.size()-1;    // possible last index
    int mid_index;                       
	bool check=true;
	while (low_index<=high_index && check)
	{
		mid_index=(low_index +high_index)/2;
		if (student_id[mid_index]==id) //we found the id and changing cond to exit loop 
		{
			check=false;
		}
		else if (student_id[mid_index]<id) //if id in upper half of the vector
		{
			low_index=mid_index+1; // changing lower bound
		} 
		else   // id in lower half of the vector
		{
			high_index=mid_index-1; //changing upper bound
		}
	}
	if (check==false) // if check is false,this means id is in the vector at mid_index position ,so return mid_index
	{
		return mid_index;
	}
	else
	{
		return -1; //if check true, there is no id in the vector , and return -1 
	}
}
void remove_id(vector<int> & std_ids,int loc)
// defining function to remove the id at loc index from vector and return new vector as a reference parameter
{
	int lastIndex = std_ids.size()-1;
	for (int i=loc; i < lastIndex; i++) // begin with index of id (loc) and continue until end of the vector size to remove id
	{
		std_ids[i] = std_ids[i+1];   // shifting all elements on the right of loc one cell left ,so get rid of the id in the loc index.
	}
	//reduce the size of the vector
	std_ids.pop_back();  // removing the last element of vector (same as the previous one because of shifting)
}
void print_add_drop_finished(courseNode*ptr)
// defining function to print all of the elements in the linked list that has at least 3 student id for fourth selection.
{
	while (ptr!=NULL) // loop until end of the linked list
	{
		if (ptr->studentsAttendingIDs.size()<3) // if the course node vector size is not greater than 3
		{
			cout<<ptr->courseCode <<" "<<ptr->courseName<<" -> This course will be closed"<<endl;
		}
		else // if coursenode vector size grater and equal than 3
		{
			cout<<ptr->courseCode<<" "<<ptr->courseName<<":";
			for (int i = 0; i < ptr->studentsAttendingIDs.size(); i++) // printing enrolled ids for this course
			{
				cout<<" "<<ptr->studentsAttendingIDs[i];
			}
			cout<<endl;
		}
		ptr=ptr->next;
	}
}
void deleting_linkedlist(courseNode*head)
// defining function to delete all dynamically allocated course node before termination
{
	courseNode*temp;
	while (head != NULL)
	{
		temp=head->next; // moving next node
		delete head; // delete previous node
		head=temp; // allocating a new head
	}
}
int main(){
	ifstream reader_file; // defining ifstream variable to read txt
	string file_name,file_line;// defining string varible for file name and lines
	string course_code,course_name;// defining string variable for course name and code
	int S_id;// defining integer variable for student id
	cout<<"Please enter file name: ";
	cin>>file_name; // getting file name
	reader_file.open(file_name.c_str());// open a txt file with reader_file
	cout<<"Successfully opened file "<<file_name<<endl;
	courseNode *head = NULL; //defining pointer that points head of the linked list
	courseNode *course_pointer = NULL; // defining pointer that points specific course location
	while (getline(reader_file,file_line)) // reading txt file line by line
	{
		istringstream lines(file_line); //reading lines with istringstream
		lines>>course_code>>course_name>>S_id;
		if (check_course(head,course_name,course_code,course_pointer))  //Checking whether the course is a linked list or not
		{
			//if course in linked list,getting pointer that points to course node as course_pointer
			//insert id in the vector at this pointer with insert_id_and_sorting function
			insert_id_and_sorting(course_pointer->studentsAttendingIDs,S_id);
		}
		else  // if course not in  linked list 
		{
			//adding course in the linked list with adding_sorting_node function and getting new course_pointer thanks to refence parameter
			head=adding_sorting_node(head,course_name,course_code,course_pointer);
			//insert id in the vector at this pointer (course_pointer) with insert_id_and_sorting function
			insert_id_and_sorting(course_pointer->studentsAttendingIDs,S_id);
		}

	}
	cout<<"The linked list is created."<<endl;
	cout<<"The initial list is:"<<endl;
	//courseNode*ptr=head;
	print_linkedlist(head); //printing linked list with print_linkedlist function with head parameter
	int select;// defining integer to get selection number
	bool cond=true;
	string input;
	while(cond)
	{
		option_func(select); //printing options for user and getting selection with select parameter
		if (select==1) // if user want to add course 
		{
			cout<<"Give the student ID and the course names and course codes that he/she wants to add:"<<endl;
			string c_code,c_name;
			int ids;
			cin.ignore();//Clearing the buffer to use getline
			getline(cin,input); 
			istringstream reader(input);
			while (reader>>c_code>>c_name) // getting course code and course name from input string
			{
				if (check_course(head,c_name,c_code,course_pointer))
				//if the course is in the linked list check_course function returns true also return course_pointer becasue of the reference parameter
				{
					while(reader>>ids)
					{
						if (check_id(course_pointer->studentsAttendingIDs,ids)<0) //Checking the id, if not in the vector, we add it to the vector
						//check_id function returns -1 if the id is not in the vector.
						{
							//insert id in the vector at this pointer (course_pointer) with insert_id_and_sorting function
							insert_id_and_sorting(course_pointer->studentsAttendingIDs,ids);
							cout<<"Student with id "<<ids<<" is enrolled to "<<c_code<<"."<<endl;
						}
						else // if id is in the vector
						{
							cout<<"Student with id "<<ids <<" already is enrolled to "<<c_code<<". No action taken."<<endl;
						}
					}
					reader.clear();//to get rid of the error when no integer comes in istringstream
				}
				else // if course is not in the linked list
				{
					cout<<c_code<<" does not exist in the list of Courses. It is added up."<<endl;
					//adding course in the linked list with adding_sorting_node function and getting new course_pointer thanks to refence parameter
					head=adding_sorting_node(head,c_name,c_code,course_pointer);
					while(reader>>ids)
					{
						//insert id in the vector at this pointer (course_pointer) with insert_id_and_sorting function
						insert_id_and_sorting(course_pointer->studentsAttendingIDs,ids);
						cout<<"Student with id "<<ids<<" is enrolled to "<<c_code<<"."<<endl;
					}
					reader.clear();//to get rid of the error when no integer comes in istringstream
				}
			}
		}
		else if(select==2) // if user want to course drop
		{
			cout<<"Give the student ID and the course names and course codes that he/she wants to drop:"<<endl;
			string c_code,c_name;
			int ids;
			cin.ignore();//Clearing the buffer to use getline
			getline(cin,input);
			istringstream reader(input);
			while (reader>>c_code>>c_name)
			{
				if (check_course(head,c_name,c_code,course_pointer)) //if the course to be deleted is in the linked list
				{
					while(reader>>ids)
					{
						if (check_id(course_pointer->studentsAttendingIDs,ids)<0)//check_id function returns -1 if the id is not in the vector.
						{
							cout<<"Student with id "<<ids<<" is not enrolled to "<<c_code<<", thus he can't drop that course."<<endl;
						}
						else
						{
							//if id is in the vector, check_id function returns index of this id in the vector
							int loc=check_id(course_pointer->studentsAttendingIDs,ids);
							remove_id(course_pointer->studentsAttendingIDs,loc); // remove_id function removes the id in this index(loc)
							cout<<"Student with id "<<ids<<" has dropped "<<c_code<<"."<<endl;
						}
					}
					reader.clear();//to get rid of the error when no integer comes in istringstream
				}
				else //if the course to be deleted is not in the linked list
				{
					while (reader>>ids) // reading ids until get error
					{
						cout<<"The "<<c_code<<" course is not in the list, thus student with id "<<ids<<" can't be dropped."<<endl;
					}
					reader.clear();// get rid of the error when no integer comes in istringstream
				}
			}
		}
		else if(select==3) // if user want to print current list
		{
			cout<<"The current list of course and the students attending them:"<<endl;
			print_linkedlist(head);// printing all list with using print_linkedlist function 
		}
		else
		{
			cout<<"The add/drop period is finished. Printing the final list of courses and students attending them."<<endl;
			cout<<"NOTE: Courses with less than 3 students will be closed this semester."<<endl;
			print_add_drop_finished(head);// print the last list with courses that has at least 3 student ids with print_add_drop_finished function
			deleting_linkedlist(head); // delete all linked list thanks to dynamically allocated coursenode with deleting_linkedlist function
			cond=false;  // changing a cond to stop the while loop
		}
	}
	system("pause");
	return 0;
}