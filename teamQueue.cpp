//teamQueue.cpp

//This is a linked-list based queue that inserts data values next
//to their "team" members.
// #include"teamQueue.h"


//Default constructor
template<class T> teamQueue<T>::teamQueue()
{
	Front = Rear = curr = NULL;
}

/**
*  MethodName: dequeue()
*  Description: Removes front item in queue
*  Parameters: n/a
*  Returns: int - number at the front of queue
**/
template<class T>
int teamQueue<T>::dequeue()
{
	int TempData = Front->Data;
	Node<T>* TempNodePtr = Front;
	Front = Front->Next;
	curr = Front;
	delete TempNodePtr;
	return TempData;
}

/**
*  MethodName: Empty()
*  Description: Checks if queue is empty
*  Parameters: n/a
*  Returns: bool - empty or not
**/
template<class T> bool teamQueue<T>:: Empty()
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
template<class T> void teamQueue<T>:: enqueue(T val,int team)
{
	Node<T>* Temp = new Node<T>;
	Temp->Data = val;
	Temp->ID = team;
	Temp->Next = NULL;

	if (Empty())
	{
		Front = Rear = curr = Temp;
	}
	else
	{
		//Updates pointer to find if there is a Node
		//with the same team as Temp
		while (Temp->ID != curr->ID && curr->Next != NULL)
		{
				curr = curr->Next;
		}

		//If Temp has the same team as a Node
		if (curr->ID == Temp->ID)
		{
			Node<T> *prev = new Node<T>();

			//If first/last node is team member of temp
			if (curr->Next == NULL)
			{
				Rear->Next = Temp;
				Rear = Temp;
			}
			else
			{
				//Finds last node of the same team
				while (curr->ID == Temp->ID && curr->Next != NULL)
				{
					prev = curr;
					curr = curr->Next;
				}

				//If current node is at end of queue and is on the same team
				if (curr->Next == NULL && curr->ID == Temp->ID)
				{
					Rear->Next = Temp;
					Rear = Temp;
				}
				//Inserts in middle of queue
				else
				{
					prev->Next = Temp;
					Temp->Next = curr;
				}

			}

			//Moves rear to back of queue if it is not already there
			if (Rear->Next != NULL)
			{
				while (Rear->Next != NULL)
				{
					Rear = Rear->Next;
				}
			}
		}
		//If Temp has no team members
		else
		{
			Rear->Next = Temp;
			Rear = Temp;
		}
		curr = Front;
	}
}


/**
*  MethodName: Print()
*  Description: prints out queue
*  Parameters: n/a
*  Returns: string - string of data
**/
//Prints out queue
template<class T> string teamQueue<T>:: Print()
{
	string s = "";
	Node<T>* Temp = Front;
	while (Temp)
	{
		 s += to_string(Temp->Data) + "->";
		Temp = Temp->Next;
	}
	s += '\n';
	return s;
}

//Destructor
template<class T> teamQueue<T>::~teamQueue()
{
	Front = Rear = curr = NULL;
}
