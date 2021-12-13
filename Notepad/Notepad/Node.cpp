#include "Node.h"

//Default Empty Constructor
Node::Node()
{
	prev = next = nullptr;
}

//Parameterized Constructor for holding char
Node::Node(char c)
{
	prev = next = nullptr;
	letter = c;
}