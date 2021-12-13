#pragma once
#include <string>
#include "Node.h"

class Editor
{
	public: 
		//Constructor for initalizing editor
		Editor();

		//Destructor for deallocating memory
		~Editor();

		//Function for editing files
		void run();

		//Read and insert file into editor
		void readFile(std::string file);

		//Prints screen
		void printarea();

		//Used for cursor navigation
		void gotoxy(int x, int y);

	protected:
		//Nodes used in linked list
		Node* start;
		Node* curr;
		Node* end;

		//Stores coordinates of cursor
		int x, y;

		//Used for storing rows in editor
		Node* rows[7]; //Max rows of 7
		int rowNumber;
};