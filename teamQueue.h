
#pragma once
#include<iostream>
using namespace std;

struct Node
{
	int Data;
	Node* Next;
};

class teamQueue
{

public:
	//Default constructor
	teamQueue();

	//Checks if queue is empty
	bool Empty();

	//Adds an item to queue
	void enqueue(int val);

	//Removes an item from queue
	int dequeue();
	
	//Prints out queue
	void Print();
private:
	Node* Front;
	Node* Rear;

};
