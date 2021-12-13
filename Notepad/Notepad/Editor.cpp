//Student Name : Jack Muir
//Student ID: 900783742

#include <iostream>
#include <conio.h>
#include "Editor.h"
#include <Windows.h>
#include <fstream>
#include <string>
#include "Node.h"
using namespace std;

//Constructor that creates empty editor
Editor::Editor()
{
	//Start with empty linked list
	start = nullptr;
	end = nullptr;
	curr = nullptr;

	//Cursor at start
	x = y = 0;

	//Initializes 7 rows of empty linked lists
	rowNumber = 0;
	for (int i = 0; i < 7; i++)
	{
		rows[i] = nullptr;
	}
	
}

//Destructor for deallocating memory
Editor::~Editor()
{
	//Delete lists in all 7 rows
	for (int i = 0; i < 7; i++)
	{
		Node* current = rows[i];
		Node* next = nullptr;

		//Delete through entire list
		while (current != nullptr)
		{
			next = current->next;
			delete(current);
			current = next;
		}
	}
}

//Function for moving location of cursor
void Editor::gotoxy(int x, int y)
{
	COORD pos = { x + 8, y + 5 }; //position translated for interface access
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

//Main Function
void Editor::run()
{
	//Temporary variable initialization
	Node* temp = nullptr;
	int tempX;
	
	//Used for storing typed info
	char c;
	
	//Print empty editor
	printarea();

	//Continuous loop until escaped
	while (1)
	{
		
		c = _getch(); //Get key pressed

		//Exit case ESC key
		if (c == 27)
			break;

		//Function Button
		if (c == 0)
		{
			c = _getch();

			//F2
			if (c == 60)
			{
				//Create file for writing
				ofstream outFile;

				//Prompt for file naming and .txt appending
				cout <<endl << "        Please enter an name for your file. '.txt' will be automatically added: ";
				string fileName;
				cin >> fileName;
				fileName = fileName + ".txt";

				//Open file for writing - will save to directory with program files
				outFile.open(fileName.c_str());

				//Loop through rows, print entire list of each row
				for (int i = 0; i < 7; i++)
				{
					//print only non empty rows
					if (rows[i] != nullptr)
					{
						Node* t = rows[i];

						//Print until no more characters in list
						while (t != nullptr)
						{
							outFile << t->letter; //Write char to file
							t = t->next;
						}
						outFile << endl;
					}
				}
				//Close File
				outFile.close();
			}
		}

		//Backspace
		else if (c == 8)
		{
			//If not first node
			if (end != nullptr && end->prev != nullptr)
			{
				//deleting last item, then patching pointers
				end = end->prev;
				delete(end->next);
				end->next = nullptr;

				//Move cursor to end of line
				if (x > 0)
				{
					//Loop through list until at end, place x at end
					temp = rows[y];
					tempX = 1;				
					while (temp->next != nullptr)
					{
						temp = temp->next;
						tempX++;
					}
					x = tempX;
				}
				//Align current with cursor
				curr = end;
			}
			//If first node
			else if (end != nullptr)
			{
				//Delete all nodes, start at 0
				delete(end);
				start = end = curr = rows[y] = nullptr;
				x = 0;
			}
		}

		//Arrow Keys
		else if (c == -32)
		{
			c = _getch();

			if (c == 75) //Left
			{
				//Left hand boundry 
				if (curr != start)
				{
					//Move current and cursor left
					curr = curr->prev;
					x--;
				}
			}
			else if (c == 77) //Right
			{
				//Right boundry
				if (curr != end)
				{
					//Move current and cursor left
					curr = curr->next;
					x++;
				}
			}
			else if (c == 80) //Down
			{
				//Lower Boundary
				if (y < 6 && rows[y + 1] != nullptr)
				{
					//move y down one, set start to new row
					y++;
					start = rows[y];

					//Find last node in row, set end and current to it
					temp = rows[y];
					tempX = 1;
					while (temp->next != nullptr)
					{
						temp = temp->next;
						tempX++;
					}
					end = temp;
					curr = end;

					//Align x with current
					x = tempX;
				}
			}
			else if (c == 72)//Up
			{
				//Upper Boundary
				if (y > 0 && rows[y - 1] != nullptr)
				{
					//move y up one, set start to new row
					y--;
					x = 0;
					start = rows[y];

					//Find last node in row, set end and current to it
					temp = rows[y];
					tempX = 1;
					while (temp->next != nullptr)
					{
						temp = temp->next;
						tempX++;
					}
					end = temp;
					curr = end;

					//Align x with current
					x = tempX;
				}
			}
		}

		//Enter
		else if (c == 13)
		{
			//Lower Boundary
			if (y < 6 && rows[y] != nullptr)
			{
				//Add new row, create empty list, start at 0
				rowNumber++;
				start = end = curr = rows[rowNumber];
				y = rowNumber;
				x = 0;
			}
		}

		//Character Keys
		else if (start == nullptr) //Used only when linked list is empty
		{
			//Create a new node at beginning, start from there
			Node* n = new Node(c);
			start = n;
			end = n;
			curr = n;
			x++;
			rows[rowNumber] = start;
		}
		else if(curr == end)//Used to add a new node to the list at the end
		{
			//Create a new node at the end, move everything to the end
			Node* n = new Node(c);
			end->next = n;
			n->prev = end;
			end = n;
			curr = end;
			x++;
		}
		else if (curr->next != nullptr ) //Add nodes to the middle
		{
			//Insert in middle, move up 1
			Node* n = new Node(c);
			n->next = curr->next;
			curr->next->prev = n;
			n->prev = curr;
			curr->next = n;
			curr = n;
			x++;
		}
		
		//Displaying of List and moving cursor
		system("cls");
		printarea();
		gotoxy(x, y);
		
	}
}

//Function to print iterface and linked list
void Editor::printarea()
{
	//Top of editor with controls

	cout << "                                                                                                                        " << endl;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, 12 | BACKGROUND_BLUE | BACKGROUND_GREEN |BACKGROUND_RED); //red text on gray background
	cout << " Jacks Text Editor                                                                                                      " << endl;
	cout << "                                                                                                                        " << endl;
	cout << " F2: save to file         ESC: exit        Arrow Keys to Navigate       Enter for new Line                              " << endl;
	cout << "                                                                                                                        " << endl;
	SetConsoleTextAttribute(hStdOut, 15); //reset text color


	//Printing of linked list - body of editor

	for (int i = 0; i < 7; i++)//each row 
	{
		//Gray boundary to the left
		SetConsoleTextAttribute(hStdOut, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		cout << "        ";
		SetConsoleTextAttribute(hStdOut, 15);//reset text color

		//Print entire linked list
		if (rows[i] != nullptr)//only non empty rows
		{
			Node* t = rows[i];
			while (t != nullptr)//print full list
			{
				cout << t->letter;
				t = t->next;
			}

		}
		cout << endl;
	}

	//Side bar along entire editor

	SetConsoleTextAttribute(hStdOut, 12 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);//Gray color
	for (int i = 0; i < 18; i++)
	{
		cout << "        " << endl;
	}
	SetConsoleTextAttribute(hStdOut, 15); //reset text color
}


//Used for reading and printing file for editing - uses same mechanics as typing
void Editor::readFile(string file)
{
	//Create and open file of specified name
	ifstream infile;
	infile.open(file);

	//Used for storing typed info
	char c;


	//Continuous loop until no more characters in file - stores next char in c
	while (infile.get(c))
	{

		//Enter
		if (c == '\n') //Detect end of line
		{
			if (y < 6)
			{
				rowNumber++;
				start = end = curr = rows[rowNumber];
				y++;
				x = 0;
			}
		}

		//Character Keys
		else if (start == nullptr) //Used only when linked list is empty
		{
			Node* n = new Node(c);
			start = n;
			end = n;
			curr = n;
			x++;
			rows[rowNumber] = start;
		}
		else if (curr == end)//Used to add a new node to the list
		{
			Node* n = new Node(c);
			end->next = n;
			n->prev = end;
			end = n;
			curr = end;
			x++;
		}

		system("cls");

		//Printing of linked list
		printarea();
		gotoxy(x, y);
	}
	//Clear screen for running
	system("cls");

	//Close file
	infile.close();
}
