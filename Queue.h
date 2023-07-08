#pragma once

#include <iostream>
#include <time.h>
#include "myconsole.h"
#include "mygraphics.h"
#include "stacks.h"
using namespace std;

class node {
public:
	
	int x_axis;
	int y_axis;
	int data;
	node* next;
	node()
	{
		x_axis = 0;
		y_axis = 0;
		data = 0;
		next = nullptr;
	}
};

class QueueLinkList
{
	node* head;
	node* tail;
	int** grid_2d;
	int size;
	int pos_x;
	int pos_y;
public:
	static int count;
	static int number_of_cells;
	QueueLinkList()
	{
		head = nullptr;
		tail = nullptr;
		grid_2d = nullptr;
		size = 0;
		pos_x = 0;
		pos_y = 0;
	}
	QueueLinkList(int s)
	{
		head = nullptr; 
		tail = nullptr;
		size = s;
		grid_2d = new int* [size];
		for (int i = 0; i < size; i++)
		{
			grid_2d[i] = new int[size];
		}
		pos_x = 0;
		pos_y = 0;
	}
	void Set_data(int** arr)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				grid_2d[i][j] = arr[i][j];
			}
		}
		pos_x = stacklinklist::source_x;
		pos_y = stacklinklist::source_y;
		grid_2d[stacklinklist::source_x][stacklinklist::source_y] = 0;
		grid_2d[stacklinklist::dest_x][stacklinklist::dest_y] = 92;
	}
	void insertAtTail(int x,int y,int dat) //insert at end
	{
		node* n = new node;
		n->data = dat;
		n->x_axis = x;
		n->y_axis = y;

		if (tail == nullptr)
		{
			head = n;
			tail = n;

		}
		else
		{
			tail->next = n;
			tail = n;
		}

	}
	void print() const //print
	{
		if (head != nullptr)
		{
			node* current = head;
			cout << "\nData is: ";
			while (current != nullptr)
			{
				cout << current->data;
				current = current->next;
			}
		}
	}
	int DeleteFromHead(int &x,int &y) //delete at start
	{
		if (head != nullptr)
		{
			node* curr = head;
			int Dvalue = curr->data;
			x = curr->x_axis;
			y = curr->y_axis;
			//cout << endl << "Deleted\n" ;
			if (head == tail)
			{
				head = nullptr;
				tail = nullptr;
			}
			else
			{
				head = head->next;
			}
			delete curr;
			return Dvalue;
		}

	}
	~QueueLinkList() //destructor
	{
		if (head != nullptr)
		{
			while (head != tail)
			{
				node* temp = head;
				head = head->next;
				delete temp;
			}
			delete tail;
		}

	}
	void Enque(int x, int y, int dat)
	{
		insertAtTail(x, y, dat);
	}
	int Deque(int& x, int &y)
	{
		return DeleteFromHead(x,y);
	}

	bool up()
	{
		bool flag = false;
		if (pos_x > 0)
		{
			if (grid_2d[pos_x - 1][pos_y] != 95					//hurdle
				&& (grid_2d[pos_x - 1][pos_y] > count))				//its own number
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
				&& (grid_2d[pos_x][pos_y - 1] > count))			//its own number
			{
				flag = true;
			}
		}
		return flag;
	}
	bool right()
	{
		bool flag = false;
		if (pos_y < size - 1)
		{
			if (grid_2d[pos_x][pos_y + 1] != 95				//hurdle
				&& grid_2d[pos_x][pos_y + 1] > count)			//its own number
			{
				flag = true;
			}
		}
		return flag;
	}
	bool down()
	{
		bool flag = false;
		if (pos_x < size - 1)
		{
			if (grid_2d[pos_x + 1][pos_y] != 95			//hurdle
				&& grid_2d[pos_x + 1][pos_y] > count)		//its own number	
			{
				flag = true;
			}
		}
		return flag;
	}
	void input_source_destination()
	{
		Enque(pos_x, pos_y, count);			//storing first part in queue
	}
	void game_menu()
	{
		input_source_destination();

		bool found = false;
		bool rightfound = false;
		bool leftfound = false;
		bool upfound = false;
		bool downfound = false;

		//ClearScreen();
		graphical_output_queue();
		//auto game control
		while (!found)
		{
			count = Deque(pos_x, pos_y);
			count++;
			if (right() && !found)
			{
				pos_y++;
				if (grid_2d[pos_x][pos_y] == 92)  //if destination found
				{
					found = true;
					rightfound = true;
				}
				grid_2d[pos_x][pos_y] = count;
				Enque(pos_x, pos_y, count);						//pushing data to nodes
				pos_y--;
			}
			if (down() && !found)
			{
				pos_x++;
				if (grid_2d[pos_x][pos_y] == 92)  //if destination found
				{
					found = true;
					downfound = true;
				}
				grid_2d[pos_x][pos_y] = count;
				Enque(pos_x, pos_y,count);
				pos_x--;
			}
			if (left() && !found)
			{
				pos_y--;
				if (grid_2d[pos_x][pos_y] == 92)  //if destination found
				{
					found = true;
					leftfound = true;
				}
				grid_2d[pos_x][pos_y] = count;
				Enque(pos_x, pos_y,count);
				pos_y++;
			}
			if (up() && !found)
			{
				pos_x--;
				if (grid_2d[pos_x][pos_y] == 92)  //if destination found
				{
					found = true;
					upfound = true;
				}
				grid_2d[pos_x][pos_y] = count;
				Enque(pos_x, pos_y, count);
				pos_x++;
			}
			Sleep(400);
			//ClearScreen();
			graphical_output_queue();
		}

		if (rightfound)
			pos_y++;
		else if (downfound)
			pos_x++;
		else if (leftfound)
			pos_y--;
		else if (upfound)
			pos_x--;

		grid_2d[pos_x][pos_y] = 97;			//destination found and then replace with backtrack cell
		count--;

		bool backtrack = false;
		while (!backtrack)
		{
			
			if (pos_y > 0 && grid_2d[pos_x][pos_y - 1] == count && !backtrack )	//left check
			{
				grid_2d[pos_x][pos_y - 1] = 97;
				pos_y--;
				count--;
			}
			else if (pos_y < size - 1 && grid_2d[pos_x][pos_y + 1] == count && !backtrack) //right check
			{
				grid_2d[pos_x][pos_y + 1] = 97;
				pos_y++;
				count--;
			}
			else if (pos_x > 0 && grid_2d[pos_x - 1][pos_y] == count && !backtrack)		//up check
			{
				grid_2d[pos_x - 1][pos_y] = 97;
				pos_x--;
				count--;
			}
			else if (pos_x < size - 1 && grid_2d[pos_x + 1][pos_y] == count && !backtrack)	//down check
			{
				grid_2d[pos_x + 1][pos_y] = 97;
				pos_x++;
				count--;
			}

			if (pos_x == stacklinklist::source_x && pos_y == stacklinklist::source_y)
			{
				backtrack = true;
			}
			number_of_cells++;
			Sleep(400);
			//ClearScreen();
			graphical_output_queue();
		}

		Sleep(2000);
	}

	void graphical_output_queue()
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
				else if (grid_2d[i][j] == 91 || grid_2d[i][j] == 0)			//yellow
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(255, 255, 0));
				}
				else if (grid_2d[i][j] == 92)				//green
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(0, 255, 0));
				}
				else if (grid_2d[i][j] == 97)			//rat purple
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(128, 0, 128));
					myEllipse(40 + x_incre, 210 + y_incre, 50 + x_incre, 220 + y_incre, RGB(0, 0, 0), RGB(128, 128, 128));
				}
				else if (grid_2d[i][j] == 95)				//blue
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(0, 0, 255));
				}
				else
				{
					myRect(30 + x_incre, 200 + y_incre, 60 + x_incre, 230 + y_incre, RGB(255, 255, 255), RGB(255, 255, 0));
					
					char ch;
					char aa[4] = { '\0' };
					if (grid_2d[i][j] / 10 == 0)
					{
						ch = grid_2d[i][j] + 48;
						aa[0] = ch;
					}
					else if (grid_2d[i][j] / 100 == 0 )
					{
						int temp1 = grid_2d[i][j] / 10;
						ch = temp1 + 48;
						aa[0] = ch;
						int temp2 = grid_2d[i][j] % 10;
						ch = temp2 + 48;
						aa[1] = ch;
					}
					else if (grid_2d[i][j] / 1000 == 0)
					{
						int temp1 = grid_2d[i][j] / 100;
						ch = temp1 + 48;
						aa[0] = ch;
						temp1 = grid_2d[i][j] / 10;
						int temp2 = temp1 / 10;
						ch = temp2 + 48;
						aa[1] = ch;
						int temp3 = temp2 % 10;
						ch = temp3 + 48;
						aa[2] = ch;
					}
					myDrawTextWithFont(40 + x_incre, 205 + y_incre, 15, aa ,RGB(128, 128, 128), RGB(255, 255, 255));
				}
				x_incre = x_incre + 30;
			}
			y_incre = y_incre + 30;
		}
	}
	
};
int QueueLinkList::count = 0;
int QueueLinkList::number_of_cells = 1;

