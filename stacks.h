#pragma once

#include <iostream>
#include <time.h>
#include "myconsole.h"
#include "mygraphics.h"
using namespace std;

class Node
{
public:
	int x_data;
	int y_data;
	Node* next;

	Node()
	{
		x_data = 0;
		y_data = 0;
		next = nullptr;
	}
};

class stacklinklist
{
	Node* top;
	int** grid_2d;
	int size;
	int pos_x;
	int pos_y;
public:
	static int number_of_cells;
	static int source_x;
	static int source_y;
	static int dest_x;
	static int dest_y;
	static bool destination_found;
	stacklinklist()
	{
		top = nullptr;
		grid_2d = nullptr;
		size = 0;
		pos_x = 0;
		pos_y = 0;
	}
	stacklinklist(int s)
	{
		top = nullptr;
		pos_x = 0;
		pos_y = 0;
		size = s;
		grid_2d = new int* [size];						//creating 2d dynamic array
		for (int i = 0; i < size; i++)
		{
			grid_2d[i] = new int[size];
		}
		for (int i = 0; i < size; i++)					//initiallizing whole 2d array with 0's
		{
			for (int j = 0; j < size; j++)
			{
				grid_2d[i][j] = 90;
			}
		}

		random_hurdles_place();						//calling random hurdles place function

	}
	void random_hurdles_place()
	{
		int hurdle_value = (size * size) - ((size * size) * 75 / 100);

		srand((unsigned) time(0));
		int rand_count = 0;
		int hurdle_count = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (rand_count == 0)
				{
					rand_count = 1 + (rand() % (size - 1));
				}
				if (rand_count == 1 && hurdle_count != hurdle_value)
				{
					grid_2d[i][j] = 95;
					rand_count--;
					hurdle_count++;
				}
				else
				{
					rand_count--;
				}
			}
		}
	}
	bool up() 
	{
		bool flag = false;
		if (pos_x > 0)
		{
			if (grid_2d[pos_x - 1][pos_y] != 95					//hurdle
				&& grid_2d[pos_x - 1][pos_y] != 91				//its own yellow area
				&& grid_2d[pos_x - 1][pos_y] != 94)				//red area which rat already visited
			{
				flag = true;
			}
		}
		return flag;
	}
	bool left() 
	{
		bool flag = false;
		if (pos_y > 0)
		{
			if (grid_2d[pos_x][pos_y - 1] != 95				//hurdle
				&& grid_2d[pos_x][pos_y - 1] != 91			//its own yellow area
				&& grid_2d[pos_x][pos_y - 1] != 94)			//red area which rat already visited
			{
				flag = true;
			}
		}
		return flag;
	}
	bool right() 
	{
		bool flag = false;
		if (pos_y < size-1)
		{
			if (grid_2d[pos_x][pos_y + 1] != 95				//hurdle
				&& grid_2d[pos_x][pos_y + 1] != 91			//its own yellow area
				&& grid_2d[pos_x][pos_y + 1] != 94)			//red area which rat already visited
			{
				flag = true;
			}
		}
		return flag;
	}
	bool down() 
	{
		bool flag = false;
		if (pos_x < size-1)
		{
			if (grid_2d[pos_x + 1][pos_y] != 95			//hurdle
				&& grid_2d[pos_x + 1][pos_y] != 91		//its own yellow area
				&& grid_2d[pos_x + 1][pos_y] != 94)		//red area which rat already visited	
			{
				flag = true;
			}
		}
		return flag;
	}
	bool input_source_destination()
	{
		//inputting source cell of rat:
		cout << "\nEnter cell for position of putting rat: ";
		cout << "\nEnter X co-ordinate: ";
		cin >> pos_x;
		while (pos_x >= size || pos_x < 0)
		{
			cout << "\n--------------- Wrong Input --------------- Enter valid cell: ";
			cin >> pos_x;
		}
		source_x = pos_x;				//updating source location
		cout << "\nEnter Y coordinate: ";
		cin >> pos_y;
		while (pos_y >= size || pos_y < 0)
		{
			cout << "\n--------------- Wrong Input --------------- Enter valid cell: ";
			cin >> pos_y;
		}
		source_y = pos_y;

		//placing rat position
		if (grid_2d[pos_x][pos_y] == 95)			//check if user enter rat position on the hurdle
		{
			cout << "\n--------------- Wrong Placement of rat.. Hurdle is present in this cell --------------- Enter valid cell: ";
			return false;
		}
		else
		{
			grid_2d[pos_x][pos_y] = 99;
			push(pos_x, pos_y);
		}


		//inputting destination cell
		cout << "\nEnter cell for destination of rat: ";
		cout << "\nEnter X co-ordinate: ";
		int t_x, t_y;
		cin >> t_x;
		while (t_x >= size || t_x < 0)
		{
			cout << "\n--------------- Wrong Input --------------- Enter valid cell: ";
			cin >> t_x;
		}
		dest_x = t_x;
		cout << "\nEnter Y coordinate: ";
		cin >> t_y;
		while (t_y>=size || t_y < 0)
		{
			cout << "\n--------------- Wrong Input --------------- Enter valid cell: ";
			cin >> t_y;
		}
		dest_y = t_y;

		if (grid_2d[t_x][t_y] == 95)			//check if user enter destination position on the hurdle
		{
			cout << "\n--------------- Wrong Placement of destination.. Hurdle is present in this cell --------------- Enter valid cell: ";
			return false;
		}
		else
		{
			grid_2d[t_x][t_y] = 92;
		}
		
		return true;
	}
	void game_menu() 
	{
		bool found = false;
		bool notfound = false;
		bool upflag = false;
		bool downflag = false;
		bool rightflag = true;
		bool leftflag = false;
		ClearScreen();
		graphical_output();
		//auto game control
		while (!found)
		{
			if (rightflag)
			{
				if (right())
				{
					grid_2d[pos_x][pos_y] = 91;
					pos_y++;
					if (grid_2d[pos_x][pos_y] == 92)  //if destination found
					{
						grid_2d[pos_x][pos_y] = 98;
						found = true;
					}
					else
					{
						grid_2d[pos_x][pos_y] = 99;
					}
					push(pos_x, pos_y);						//pushing data to nodes
					Sleep(300);
					//ClearScreen();
					graphical_output();
					
				}
				else
				{
					rightflag = false;
					downflag = true;
				}
			}
			else if (downflag)
			{
				if (down())
				{
					grid_2d[pos_x][pos_y] = 91;
					pos_x++;
					if (grid_2d[pos_x][pos_y] == 92)  //if destination found
					{
						grid_2d[pos_x][pos_y] = 98;
						found = true;
					}
					else
					{
						grid_2d[pos_x][pos_y] = 99;
					}
					push(pos_x, pos_y);
					Sleep(300);
					//ClearScreen();
					graphical_output();
				}
				else
				{
					downflag = false;
					leftflag = true;
					
				}
			}
			else if (leftflag)
			{
				if (left())
				{
					grid_2d[pos_x][pos_y] = 91;
					pos_y--;
					if (grid_2d[pos_x][pos_y] == 92)  //if destination found
					{
						grid_2d[pos_x][pos_y] = 98;
						found = true;
					}
					else
					{
						grid_2d[pos_x][pos_y] = 99;
					}
					push(pos_x, pos_y);
					Sleep(300);
					//ClearScreen();
					graphical_output();
				}
				else
				{
					leftflag = false;
					upflag = true;
					
				}
			}
			else if (upflag)
			{
				if (up())
				{
					grid_2d[pos_x][pos_y] = 91;
					pos_x--;
					if (grid_2d[pos_x][pos_y] == 92)  //if destination found
					{
						grid_2d[pos_x][pos_y] = 98;
						found = true;
					}
					else
					{
						grid_2d[pos_x][pos_y] = 99;
					}
					push(pos_x, pos_y);
					Sleep(300);
					//ClearScreen();
					graphical_output();
				}
				else
				{
					upflag = false;
					rightflag = true;
					
				}
			}
			if (!up() && !down() && !right() && !left() && !found)
			{
				pop(pos_x, pos_y);
				grid_2d[pos_x][pos_y] = 94;
				if (isEmpty())
				{
					notfound = true;
					break;
				}
				pop(pos_x, pos_y);
				grid_2d[pos_x][pos_y] = 99;
				push(pos_x, pos_y);
				//redHurdleCount = 0;
				Sleep(300);
				//ClearScreen();
				graphical_output();
			}
		}
		destination_found = notfound;
		if (!notfound)
		{
			bool backtrack = false;
			while (!backtrack)
			{
				pop(pos_x, pos_y);
				grid_2d[pos_x][pos_y] = 97;
				Sleep(300);
				//ClearScreen();
				graphical_output();
				if (top == nullptr)
				{
					backtrack = true;
				}
				number_of_cells++;
			}
		}
		else
		{
			//ClearScreen();
			char ch[] = "Way not possible.\nSource or Destinition may be blocked";
			myDrawTextWithFont(100, 50, 50, ch, RGB(0, 0, 0), RGB(255, 255, 0));
		}
		Sleep(2000);
	}
	void GetArrayData(int** arr)				//returning value for usage in second question part
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				arr[i][j] = grid_2d[i][j];
			}
		}
	}
	void insertAthead(int x,int y)
	{
		Node* n = new Node;
		n->x_data = x;
		n->y_data = y;
		if (top == nullptr)
		{
			top = n;
		}
		else
		{
			n->next = top;
			top = n;
		}
	}
	void DeleteFormHead(int& x,int& y)
	{
		if (top != nullptr)
		{
			Node* curr = top;
			top = top->next;
			x = curr->x_data;
			y = curr->y_data;
			delete curr;
		}
	}
	bool isEmpty()
	{
		if (top == nullptr)
		{
			return true;
		}
		return false;
	}
	bool isFull()
	{
		return false;
	}
	void push(int x,int y)
	{
		if (!isFull())
		{
			insertAthead(x,y);
		}
	}
	void pop(int& x,int &y)
	{
		if (!isEmpty())
		{
			DeleteFormHead(x,y);
		}
	}
	void graphical_output()
	{
		int y_incre = 30;
		int x_incre = 30;
		for (int i = 0; i < size; i++)								//graphical output
		{
			x_incre = 30;
			for (int j = 0; j < size; j++)
			{
				if (grid_2d[i][j] == 90)				//orange printing
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(255, 165, 0));
				}
				else if (grid_2d[i][j] == 91)			//yellow
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(255, 255, 0));
				}
				else if (grid_2d[i][j] == 99)			//rat yello
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(255, 255, 0));
					myEllipse(40 + x_incre, 210 + y_incre, 50 + x_incre, 220 + y_incre, RGB(0, 0, 0), RGB(128, 128, 128));
				}
				else if (grid_2d[i][j] == 92)				//green
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(0, 255, 0));
				}
				else if (grid_2d[i][j] == 98)			//rat green
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(0, 255, 0));
					myEllipse(40 + x_incre, 210 + y_incre, 50 + x_incre, 220 + y_incre, RGB(0, 0, 0), RGB(128, 128, 128));
				}
				else if (grid_2d[i][j] == 97)			//rat purple
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(128, 0, 128));
					myEllipse(40 + x_incre, 210 + y_incre, 50 + x_incre, 220 + y_incre, RGB(0, 0, 0), RGB(128, 128, 128));
				}
				else if (grid_2d[i][j] == 94)				//red
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(255, 0, 0));
				}
				else if (grid_2d[i][j] == 95)				//blue
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(0, 0, 255));
				}
				x_incre = x_incre + 30;
			}
			y_incre = y_incre + 30;
		}

	}
	//deallocation of stack and 2d array
	~stacklinklist()
	{
		if (top != nullptr)
		{
			Node* curr = top;
			while (top != nullptr)
			{
				curr = top;
				top = top->next;
				delete curr;
			}
		}

		if (grid_2d != nullptr)
		{
			for (int i = 0; i < size; i++)
			{
				delete[]grid_2d[i];
			}
			delete[]grid_2d;
		}
		grid_2d = nullptr;
	}

};

int stacklinklist::source_x = 0;
int stacklinklist::source_y = 0;
int stacklinklist::dest_x = 0;
int stacklinklist::dest_y = 0;
int stacklinklist::number_of_cells = 0;
bool  stacklinklist::destination_found = false;