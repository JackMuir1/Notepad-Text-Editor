#pragma once
class Node
{
public:
	char letter; //Data Stored

	//Used for linked list navigation
	Node* prev;
	Node* next;

	//Null Constructor
	Node();

	//Parameterized Constructor for holding char
	Node(char c);


};