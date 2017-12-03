// teamQueue.h

#pragma once
#include<string>
using namespace std;

struct Node
{
	int Data;
	int ID;
	Node* Next;
};

<template T> class teamQueue
{

public:
	//Default constructor
	teamQueue();

	//Checks if queue is empty
	bool Empty();

	//Adds an item to queue
	void enqueue(int,int);

	//Removes an item from queue
	int dequeue();

	//Prints out queue
	void Print();

	//Destructor
	~teamQueue();
private:
	Node* Front;
	Node* Rear;
	Node *curr;

};

#include "teamQueue.cpp"
