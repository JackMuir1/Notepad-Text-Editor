//Student Name : Jack Muir
//Student ID: 900783742

#include <iostream>
#include <conio.h>
#include "Editor.h" 
#include <string> //For file naming
using namespace std;

//Main Driver Function
int main()
{
	//Printing of the Title Screen and options centered
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << "                                            Welcome to Jacks Text Editor" << endl;
	cout << "                          Press 1 if you have a file to edit, or press 2 to start from scratch" << endl;
	cout << "                                      ";


	//Variables used to store driver selection
	int c;
	string fileName;

	//Creation of editor
	Editor e;

	//Input loop to select how to start the editor
	while (1)
	{
		c = _getch();

		//1 For Enter File
		if (c == '1')
		{
			//Prompt for file entry
			cout << "Enter your file name: ";
			cin >> fileName;

			//Read file and allow editing
			e.readFile(fileName);
			e.run();
			break;
		}

		//2 for new doc
		else if (c == '2')
		{
			system("cls"); //Clear start menu
			e.run(); //run editor
			break; //Terminate upon completion of the editor
		}
	}
	return 0;
}

