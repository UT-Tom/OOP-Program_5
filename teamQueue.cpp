//This is just a basic queue.Still needs modification to
//enqueue

#include"teamQueue.h"


//Default constructor
teamQueue::teamQueue() 
{
	Front = Rear = NULL;
}

/**
 *  MethodName: Empty()
 *  Desctription: Checks if queue is empty
 *  Parameters: n/a
 *  Returns: bool - empty or not
**/

bool teamQueue:: Empty() 
{
	return Front == NULL;
}

//Adds an item to queue next to its team member
void teamQueue:: enqueue(int val)
{
	Node* Temp = new Node;
	Temp->Data = val;
	Temp->Next = NULL;

	if (Empty())
	{
		Front = Rear = Temp;
	}
	else
	{
		Rear->Next = Temp;
		Rear = Temp;
	}
}

//Removes front item in queue
int teamQueue:: dequeue()
{
	int TempData = Front->Data;
	Node* TempNodePtr = Front;
	Front = Front->Next;
	delete TempNodePtr;
	return TempData;
}

//Prints out queue
void teamQueue:: Print()
{
	Node* Temp = Front;
	while (Temp)
	{
		cout << Temp->Data << "->";
		Temp = Temp->Next;
	}
	cout << endl;
}
