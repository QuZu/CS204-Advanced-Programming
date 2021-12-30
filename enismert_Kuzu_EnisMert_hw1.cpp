#include <iostream>
#include <vector>
#include <string>
#include <iomanip>  // for setw
#include "randgen.h" // for random variables


/*
Author: Enis Mert Kuzu 28174
Date: October 2021
Description: This program was written to develop a simplified version of the Minesweeper game by getting coordinates from the user
*/
using namespace std;

// Functions part
char int_to_char(int a) // defining a function to convert integer to char 
{
	char c='0'+a;
	return c;
}
int char_to_int(char c) //defining a function to convert char to integer
{
	int number=c-'0';
	return number;
}
bool check_bomb(int a,int b,vector<vector<int>> cord ) //Checking if bomb coordinates have been used by defining a check_bomb function
{
	for (int i = 0; i < cord.size(); i++) 
	{
		if ((cord[i][0]==a) && (cord[i][1]==b)) // returns false if (a) row and (b) column coordinates have been used before
		{
			return false;
		}
	}
	return true;
}
int find_neighborhood_bombs(int row,int column,int total_row,int total_column,vector<vector<char>> cord) // Defining a function to calculate the number of neighboring bombs in specific coordinates (row,column) from given matrix (cord)
{
	int total_b=0; // defining total_b to keep the total number of bombs
	if ((row-1 >=0) && (row<total_row) && (column>=0) && (column<total_column)) //to check if there is a bomb in the top coordinate of the coordinate
	{
		if (cord[row-1][column]=='B')
		{
			total_b+=1;
		}
	}
	if ((row+1 >=0) && (row+1 <total_row) && (column>=0) && (column<total_column)) // to check if there is a bomb in the bottom coordinate of the coordinate
	{
		if (cord[row+1][column]=='B')
		{
			total_b+=1;
		}
	}
	if ((row >=0) && (row <total_row) && (column+1 >=0) && (column+1 <total_column)) //to check if there is a bomb in the the right coordinate of the coordinate
	{
		if (cord[row][column+1]=='B')
		{
			total_b+=1;
		}
	}
	if ((row >=0) && (row <total_row) && (column-1 >=0) && (column-1 <total_column)) //to check if there is a bomb in the left coordinate of the coordinate
	{
		if (cord[row][column-1]=='B')
		{
			total_b+=1;
		}
	}
	if ((row-1 >=0) && (row-1 <total_row) && (column+1 >=0) && (column+1 <total_column)) // to check if there is a bomb in diagonally top right coordinate of the coordinate
	{
		if (cord[row-1][column+1]=='B')
		{
			total_b+=1;
		}
	}
	if ((row+1 >=0) && (row+1 <total_row) && (column+1 >=0) && (column+1 <total_column)) // to check if there is a bomb in diagonally bottom right coordinate of the coordinate
	{
		if (cord[row+1][column+1]=='B')
		{
			total_b+=1;
		}
	}
	if ((row-1 >=0) && (row-1 <total_row) && (column-1 >=0) && (column-1 <total_column)) //to check if there is a bomb in diagonally top left coordinate of the coordinate
	{
		if (cord[row-1][column-1]=='B')
		{
			total_b+=1;
		}
	}
	if ((row+1 >=0) && (row+1 <total_row) && (column-1 >=0) && (column-1 <total_column)) //to check if there is a bomb in diagonally bottom left coordinate of the coordinate
	{
		if (cord[row+1][column-1]=='B')
		{
			total_b+=1;
		}
	}
	return total_b;
}
void questions(int &select) //to show selection questions and store select number
{
	cout<<endl<<"Press: "<<endl<<endl;
	cout<<"1. If you want to find out the surrounding of a cell"<<endl<<endl;
	cout<<"2. If you want to open the cell"<<endl <<endl;
	cout<<"3. If you want to exit."<<endl<<endl;
	cin>>select;
	while (select>3 || select<1)
	{
		cout<<"Your input is wrong. Please select one of the options: 1, 2 or 3.";
		cin>>select;
	}

}
bool bomb_here(int row,int column,vector<vector<char>> bomb_cord) // defining bomb_here function to check the specific coordinate to find out if there is a bomb.
{
	if (bomb_cord[row][column]=='B')
	{
		return true;
	}
	return false;
}
void print_matrix(vector<vector<char>> &matrix) // to print spesific matrix
{
	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix[i].size(); j++)
		{
			cout<<setw(4)<<matrix[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
}
bool check_all_open(vector<vector<char>> open_matrix,vector<vector<char>> close_matrix) // defining a function to determine whether all coordinates are open in the matrix except bombs, to win the game.
{
	for (int i = 0; i <close_matrix.size(); i++) // close_matrix consists of 'X' and numbers that denote the number of bombs in neighboring coordinates
	{
		for (int j = 0; j < close_matrix[i].size(); j++)
		{
			if ((close_matrix[i][j]=='X') && open_matrix[i][j] !='B') // open_matrix consist of 'B' and numbers that denote the number of bombs in neighboring coordinates
			{
				return false; //If there is still an X that matches (same index) a number from the open_matrix, that means there are coordinates that have not been opened yet.
			}
		}
	}
	return true;
}

// main function
int main() {
	int row,col; // define a raws of matrix as row and columns of matrix as col
	cout << "Give the dimensions of the matrix: "; 
	cin>> row >> col; // get the dimensions (rows and colums of matrix) from user
	int nrMines; // define a number of mines as nrMines
	cout << "How many bombs: ";
	cin>>nrMines; // get input for number of mines from user
	while (nrMines<=0 || nrMines>= (row*col)) // checking whether the number of mines is between 0 and total dimensions (0<nrMines<row*col)
	{
		if (nrMines<=0 ) //if the number of mines is less than 0 we should get another input
		{
			cout <<"The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin>>nrMines;
		}
		if (nrMines>= (row*col)) // if the number of mines is greater than total dimension we should get another input
		{
			cout<<"The number of bombs can not be greater than the whole number of cells minus one. Please give the number of bombs again: ";
			cin>>nrMines;
		}
	}
	int bomb_row,bomb_col; //define the coordinates of the bomb 
	RandGen ran; 
	vector <vector <int>> coordinates_bombs(nrMines); //define a matrix to store coordinates of bombs
	for (int i = 0; i < coordinates_bombs.size(); i++) // Assigning the (-1,-1) coordinate to the entire vector as a default value
	{
		coordinates_bombs[i].push_back(-1); //Assigning the -1 default value as a row number of bomb 
		coordinates_bombs[i].push_back(-1); //Assigning the -1 default value as a column number of bomb
	}
	for (int i = 0; i < coordinates_bombs.size(); i++) //Assigning random coordinates for bombs
	{
		bomb_row=ran.RandInt(0,row-1); // assigning a random value  for row value with randgen class  between 0 and row-1 index
		bomb_col=ran.RandInt(0,col-1); //assigning a random value  for column value with randgen class  between 0 and col-1 index
		while(check_bomb(bomb_row,bomb_col,coordinates_bombs)==false) // checking for random values (bomb_row, bomb_col) whether used before, using check_bomb() function
		{
			bomb_row=ran.RandInt(0,row-1); //if used before, assigning new random variable for row value
			bomb_col=ran.RandInt(0,col-1); //if used before, assigning new random variable for col value
		}
		coordinates_bombs[i][0]=bomb_row; // replacing -1 with new row number found from randgen class 
		coordinates_bombs[i][1]=bomb_col; // replacing -1 with new column number found from randgen class
	}
	vector<vector<char>> open_matrix(row,vector<char>(col)); // defining open_matrix to store bombs coordinates as a 'B' and numbers that denote the number of bombs in neighboring coordinates.
	vector<vector<char>> close_matrix(row,vector<char>(col,'X')); // defining close_matrix to store unopened coordinates as a 'X'
	// I will use the open_matrix to keep numbers and bomb locations and I will use close_matrix to show the matrix to the user

	for (int i = 0; i < coordinates_bombs.size(); i++) //assigning 'B' to the bomb coordinates in the open_matrix to store the bomb coordinates
	{
		int b_row=coordinates_bombs[i][0]; // getting bomb row coordinate
		int b_col=coordinates_bombs[i][1]; // getting bomb column coordinate 
		open_matrix[b_row][b_col]='B'; //assigning "B" to the open matrix for the coordinates of the bombs
	}
	for (int i = 0; i < open_matrix.size(); i++) //assigning neighbor bomb numbers to open_matrix coordinates
	{
		for (int j = 0; j < open_matrix[i].size(); j++)
		{
			if (open_matrix[i][j] !='B')
			{ 
				//finding the number of neighbor bombs with the find_neighborhood_bomb function
				int bombs=find_neighborhood_bombs(i,j,open_matrix.size(),open_matrix[i].size(),open_matrix); 
				open_matrix[i][j]=int_to_char(bombs); //assigning the total number of bombs around coordinate the by converting them to char
			}
		}
	}
	cout<<endl;
	print_matrix(close_matrix); // show matrix shape with print_matrix function for user
	int select; // defining select to keep user option
	bool cond=true; // defining boolean value to stop program
	int get_row,get_col; // defining variables for coordinate
	while (cond)
	{
		questions(select);
		if (select==3)
		{
			cout<<"Program exiting ... "<<endl;
			cond=false; // changing the cond to false to stop program
		}
		if (select==2)
		{
			cout<<"Give the coordinates: ";
			cin>>get_row>>get_col;
			cout<<endl;
			while ((get_row)<0 || (get_row >row-1)|| (get_col)<0 || (get_col >col-1)) // Checking coordinates until they are in the range.
			{
				cout<<"It is out of range. Please give a valid coordinates: ";
				cin>>get_row>>get_col;
			}
			cout<<endl;
			cout<<"Opening cell ("<<get_row<<","<<get_col<<"):"<<endl<<endl;
			if (bomb_here(get_row,get_col,open_matrix)==true) //checking if there is a bomb at that coordinate (get_row,get_col) with bomb_here function
			{
				char open=open_matrix[get_row][get_col]; //get the 'B' char from open_matrix
				close_matrix[get_row][get_col]=open; //assinging 'B' to close_matrix 
				print_matrix(close_matrix); // show close_matrix with print_matrix function for user
					cout<<"Unfortunately, you stepped on a mine"<<endl<<endl;
					cout<<"Arrangement of mines:"<<endl<<endl;
					print_matrix(open_matrix); // show bomb coordinates and numbers that denote the number of bombs in neighboring coordinates for user
					cout<<">>>>> Game Over! <<<<<"<<endl;
					cond=false; // changing the cond to false to stop program
			}
			else //there is not a bomb at that coordinate (get_row,get_col)
			{
				char open=open_matrix[get_row][get_col]; // get the number that denote the number of bombs in neighboring coordinates from open_matrix
				close_matrix[get_row][get_col]=open; // assigning the coordinate taken from open matrix to closed matrix and changing the number of bombs with 'X'
				if (check_all_open(open_matrix,close_matrix)==true) //checking if all coordinates are open except bombs with check_all_open function
				{
					print_matrix(close_matrix); // if all cooordinates open print matrix
					cout<<"Congratulations! All the non-mined cells opened successfully"<<endl<<endl; //print congratulations messages
					cout<<"You won!"<<endl<<endl;
					cout<<">>>>> Game Over! <<<<<"<<endl;
					cond=false; // changing the cond to false to stop program
				}
				else
				{
					print_matrix(close_matrix); // if not all coordinates are opened, show close matrix with opened coordinate (get_row,get_col) for the user
				}
			}
				
		}
		if (select==1)
		{
			int total=0; // to keep total number that denote the number of bombs in neighboring coordinates for ('B') bomb coordinate
			cout<<"Give the coordinates: ";
			cin>>get_row>>get_col;
			cout<<endl;
			while ((get_row)<0 || (get_row >row-1)|| (get_col)<0 || (get_col >col-1)) //Checking coordinates until they are in the range.
			{
				cout<<"It is out of range. Please give a valid coordinates: ";
				cin>>get_row>>get_col;
			}
			cout<<endl;
			cout<<"Displaying the surrounding of (" << get_row <<"," << get_col<<"):"<<endl<<endl;
			for (int i = 0; i < close_matrix.size(); i++)
			{
				for (int j=0; j<close_matrix[i].size(); j++) 
				{
					if ((i==get_row) && j==(get_col)) //printing displaying coordinate
					{
						if ((open_matrix[i][j] !='B')) //if there is no bomb in the displayed coordinate
						{
							cout<<setw(4)<<open_matrix[i][j]; //print the number showing the number of bombs around this coordinate
							total=char_to_int(open_matrix[i][j]); // convert to int with char_to_int funtion to show user
						}
						else //if there is a bomb in the displayed coordinate
						{
							total=find_neighborhood_bombs(i,j,close_matrix.size(),close_matrix[i].size(),open_matrix); // finding the number showing total neighbours bombs number around this coordinate with find_neighborhood_bombs function
							cout<<setw(4)<<int_to_char(total); // print this total number by converting it to char with int_to_char function
						}
					}
					else //printing other coordinates except the displaying coordinate with close_matrix
					{
						cout<<setw(4)<<close_matrix[i][j];
					}
				}
				cout<<endl;
			}
			cout<<endl;
			cout<<"Around ("<< get_row <<"," << get_col<<")"<<" you have "<< total<<" bomb(s)"<<endl;
		}

	}
	cin.ignore();
	cin.get();
	return 0;
}