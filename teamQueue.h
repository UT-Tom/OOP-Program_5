// teamQueue.h

#pragma once
#include<string>

using namespace std;

template<class T>
struct Node
{
	T Data;
	int ID;
	Node<T>* Next;
};

template<class T> class teamQueue
{

public:
	//Default constructor
	teamQueue<T>();

	//Checks if queue is empty
	bool Empty();

	//Adds an item to queue
	void enqueue(T,int);

	//Removes an item from queue
	T dequeue();

	//Prints out queue
	string Print();

	//Destructor
	~teamQueue<T>();

private:
	Node<T>* Front;
	Node<T>* Rear;
	Node<T>* curr;

};

#include "teamQueue.cpp"
