#include <iostream>
#include <time.h>
#include "myconsole.h"
#include "mygraphics.h"
#include "stacks.h"
#include "Queue.h"
using namespace std;

void text_print_stack()			//it will print number of cells taken by rat to reach their destination through stack
{
	char ch1[] = "It takes ";
	char ch3[] = " Cells";
	char ch;
	char aa[4] = { '\0' };
	if (stacklinklist::number_of_cells / 10 == 0)
	{
		ch = stacklinklist::number_of_cells + 48;
		aa[0] = ch;
	}
	else if (stacklinklist::number_of_cells / 100 == 0)
	{
		int temp1 = stacklinklist::number_of_cells / 10;
		ch = temp1 + 48;
		aa[0] = ch;
		int temp2 = stacklinklist::number_of_cells % 10;
		ch = temp2 + 48;
		aa[1] = ch;
	}
	else if (stacklinklist::number_of_cells / 1000 == 0)
	{
		int temp1 = stacklinklist::number_of_cells / 100;
		ch = temp1 + 48;
		aa[0] = ch;
		temp1 = stacklinklist::number_of_cells / 10;
		int temp2 = temp1 / 10;
		ch = temp2 + 48;
		aa[1] = ch;
		int temp3 = temp2 % 10;
		ch = temp3 + 48;
		aa[2] = ch;
	}
	myDrawTextWithFont(200, 20, 50, ch1, RGB(0, 0, 255), RGB(0, 255, 0));
	myDrawTextWithFont(200, 70, 50, aa, RGB(0, 0, 255), RGB(255, 255, 0));
	myDrawTextWithFont(200, 120, 50, ch3, RGB(0, 0, 255), RGB(0, 255, 0));
}
void text_print_Queue()		//it will print number of cells taken by rat to reach their destination through Queue
{
	char ch1[] = "It takes ";
	char ch3[] = " Cells";
	char ch;
	char aa[4] = { '\0' };
	if (QueueLinkList::number_of_cells / 10 == 0)
	{
		ch = QueueLinkList::number_of_cells + 48;
		aa[0] = ch;
	}
	else if (QueueLinkList::number_of_cells / 100 == 0)
	{
		int temp1 = QueueLinkList::number_of_cells / 10;
		ch = temp1 + 48;
		aa[0] = ch;
		int temp2 = QueueLinkList::number_of_cells % 10;
		ch = temp2 + 48;
		aa[1] = ch;
	}
	else if (QueueLinkList::number_of_cells / 1000 == 0)
	{
		int temp1 = QueueLinkList::number_of_cells / 100;
		ch = temp1 + 48;
		aa[0] = ch;
		temp1 = QueueLinkList::number_of_cells / 10;
		int temp2 = temp1 / 10;
		ch = temp2 + 48;
		aa[1] = ch;
		int temp3 = temp2 % 10;
		ch = temp3 + 48;
		aa[2] = ch;
	}
	myDrawTextWithFont(200, 20, 50, ch1, RGB(0, 0, 255), RGB(0, 255, 0));
	myDrawTextWithFont(200, 70, 50, aa, RGB(0, 0, 255), RGB(255, 255, 0));
	myDrawTextWithFont(200, 120, 50, ch3, RGB(0, 0, 255), RGB(0, 255, 0));
}
void comparison()		//it will print the result of shortest distance taken by rat between the queue and the stack
{

	char ch;
	char ch1;
	char aa[4] = { '\0' };
	char bb[4] = { '\0' };

	if (stacklinklist::number_of_cells / 10 == 0)
	{
		ch = stacklinklist::number_of_cells + 48;
		aa[0] = ch;
	}
	else if (stacklinklist::number_of_cells / 100 == 0)
	{
		int temp1 = stacklinklist::number_of_cells / 10;
		ch = temp1 + 48;
		aa[0] = ch;
		int temp2 = stacklinklist::number_of_cells % 10;
		ch = temp2 + 48;
		aa[1] = ch;
	}
	else if (stacklinklist::number_of_cells / 1000 == 0)
	{
		int temp1 = stacklinklist::number_of_cells / 100;
		ch = temp1 + 48;
		aa[0] = ch;
		temp1 = stacklinklist::number_of_cells / 10;
		int temp2 = temp1 / 10;
		ch = temp2 + 48;
		aa[1] = ch;
		int temp3 = temp2 % 10;
		ch = temp3 + 48;
		aa[2] = ch;
	}
	if (QueueLinkList::number_of_cells / 10 == 0)
	{
		ch1 = QueueLinkList::number_of_cells + 48;
		bb[0] = ch1;
	}
	else if (QueueLinkList::number_of_cells / 100 == 0)
	{
		int temp1 = QueueLinkList::number_of_cells / 10;
		ch1 = temp1 + 48;
		bb[0] = ch1;
		int temp2 = QueueLinkList::number_of_cells % 10;
		ch1 = temp2 + 48;
		bb[1] = ch1;
	}
	else if (QueueLinkList::number_of_cells / 1000 == 0)
	{
		int temp1 = QueueLinkList::number_of_cells / 100;
		ch1 = temp1 + 48;
		bb[0] = ch1;
		temp1 = QueueLinkList::number_of_cells / 10;
		int temp2 = temp1 / 10;
		ch1 = temp2 + 48;
		bb[1] = ch1;
		int temp3 = temp2 % 10;
		ch1 = temp3 + 48;
		bb[2] = ch1;
	}

	if (QueueLinkList::number_of_cells == stacklinklist::number_of_cells)
	{
		char ch2[] = "Hence both contain Same number of cells";
		myDrawTextWithFont(100, 20, 50, ch2, RGB(0, 0, 255), RGB(0, 255, 0));
		myDrawTextWithFont(790, 20, 50, aa, RGB(0, 0, 255), RGB(255, 255, 0));

	}
	else if (QueueLinkList::number_of_cells < stacklinklist::number_of_cells)
	{
		char ch2[] = "Hence Queue Method measures shortest distance So it is more efficient.";
		myDrawTextWithFont(100, 20, 50, ch2, RGB(0, 0, 255), RGB(0, 255, 0));
		myDrawTextWithFont(550, 80, 50, bb, RGB(0, 0, 255), RGB(255, 255, 0));
		char ch3[] = "vs";
		myDrawTextWithFont(600, 80, 50, ch3, RGB(0, 0, 255), RGB(255, 255, 0));
		myDrawTextWithFont(670, 80, 50, aa, RGB(0, 0, 255), RGB(255, 255, 0));
	}
}
//Time complexity
//Time complexity of both is almost same and it is Big-O(n^2);

int main()
{
	Maximized();
	cout << "Enter the size of the grid: ";
	int s;
	cin >> s;
	while (s < 2)
	{
		cout << "\nInvalid Input : Enter againg: ";
		cin >> s;
	}
	cout << endl;
	stacklinklist grid1(s);
	grid1.graphical_output();
	bool input_check = grid1.input_source_destination();
	while (!input_check)
	{
		ClearScreen();
		grid1.graphical_output();
		PlaceCursor(0, 0);
		input_check = grid1.input_source_destination();
	}
	int** arr = new int* [s];
	for (int i = 0; i < s; i++)
	{
		arr[i] = new int[s];
	}
	grid1.GetArrayData(arr);			// copying data to arr for usage of second array
	grid1.graphical_output();
	Sleep(1000);
	grid1.game_menu();
	if (!stacklinklist::destination_found)
	{
		text_print_stack();
		Sleep(2000);
		ClearScreen();

		QueueLinkList grid2(s);
		grid2.Set_data(arr);
		grid2.graphical_output_queue();
		Sleep(1000);
		grid2.game_menu();
		text_print_Queue();
		Sleep(2000);
		ClearScreen();
		comparison();
		Sleep(4000);
	}
	
	for (int i = 0; i < s; i++)
		delete[]arr[i];
	delete[]arr;
	arr = nullptr;
	return 0;
}