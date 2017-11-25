//teamQueue.cpp

//This is a linked-list based queue that inserts data values next 
//to their "team" members.
#include"teamQueue.h"


//Default constructor
teamQueue::teamQueue() 
{
	Front = Rear = curr = NULL;
}

/**
*  MethodName: dequeue()
*  Description: Removes front item in queue
*  Parameters: n/a
*  Returns: int - number at the front of queue
**/
int teamQueue::dequeue()
{
	int TempData = Front->Data;
	Node* TempNodePtr = Front;
	Front = Front->Next;
	delete TempNodePtr;
	return TempData;
}

/**
*  MethodName: Empty()
*  Description: Checks if queue is empty
*  Parameters: n/a
*  Returns: bool - empty or not
**/
bool teamQueue:: Empty() 
{
	return Front == NULL;
}

/**
*  MethodName: enqueue()
*  Description: Adds an item to queue next to its team member
*  Parameters: int val - a number
*			   int team - team number
*  Returns: void
**/
void teamQueue:: enqueue(int val,int team)
{
	Node* Temp = new Node;
	Temp->Data = val;
	Temp->ID = team;
	Temp->Next = NULL;

	if (Empty())
	{
		Front = Rear = curr = Temp;
	}
	else
	{
		
		while (Temp->ID != curr->ID && curr->Next != NULL)
		{
				curr = curr->Next;			
		}
		if (curr->ID == Temp->ID)
		{
			Node *prev = curr;
			curr = curr->Next;

			prev->Next = Temp;
			Temp->Next = curr;

			if (Rear->Next != NULL)
			{
				while (Rear->Next != NULL)
				{
					Rear = Rear->Next;
				}
			}
		}
		else
		{
			Rear->Next = Temp;
			Rear = Temp;
		}
		curr = Front;
	}
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

//Destructor
teamQueue::~teamQueue()
{
	Front = Rear = curr = NULL;
}
