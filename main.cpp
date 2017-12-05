/**
* @Name: Jakob Lopez && Tom Johnson
* @Description:
*    This program implements a list-based queue to solve a team queue
*		problem. It also demonstrates our ability to work with templated classes.
* @Date:
*    12/03/17
* @Instructor:
*    Dr. Stringfellow
*/

#include<iostream>
#include<fstream>
#include<string>
#include"teamQueue.h"

using namespace std;

//function prototypes
void closeFiles(ifstream&, ofstream&);
void freeArray(int**&, int);
int getTeamNum(int**&, int, int);
void initTeams(ifstream&, int**&, int&);
void initQueue(ifstream&, ofstream&, teamQueue<int>*&, int**&, int);
void openFiles(ifstream&, ofstream&);
void printBorder(ofstream&);
void printCaseNumber(ofstream&, int);

int main()
{
	int t;
	int scenario = 1;

	//open files
	ifstream infile;
	ofstream outfile;
	openFiles(infile, outfile);

	//Pointer to pointer of teams
	int **team;

	//Initializes team array
	initTeams(infile, team, t);


	//Loops until t is 0
	while (t != 0)
	{
		printBorder(outfile);

		//Initializes teamQueue
		teamQueue<int> *Q = new teamQueue<int>();

		//Prints Scenario #
		printCaseNumber(outfile, scenario);

		//Updates scenario number
		scenario++;

		//Adds or removes items to teamQueue
		initQueue(infile, outfile, Q, team, t);

		//Frees memory of team
		freeArray(team, t);

		//Initializes team array
		initTeams(infile, team, t);

		// printBorder(outfile);
	}

	//closes files
	closeFiles(infile, outfile);

	return 0;
}

/**
* @FunctionName: closeFiles
* @Description:
*    closes opened files
* @Params:
*    ifstream &ifile - allows to read from file
*    ofstream &ofile - allows to write to file
* @Returns:
*    void
*/

void closeFiles(ifstream &ifile, ofstream &ofile)
{
	ifile.close();
	ofile.close();
}

/**
* @FunctionName: freeArray
* @Description:
*    Frees memory in 2D array
* @Params:
*    int **&team - refernce to 2D array
*	 int row - number of rows
* @Returns:
*    void
*/

void freeArray(int **&team, int row)
{
	for (int i = 0; i < row; i++)
	{
		delete[] team[i];
	}
	delete[] team;
}


/**
* @FunctionName: getTeamNum
* @Description:
*    Searches through 2D array and finds team number of item
* @Params:
*    int **&team - refernce to 2D array
*	 int target - item being searched for
*    int t - Number of teams
* @Returns:
*    int - row number in array if found,otherwise -1
*/

int getTeamNum(int **&team, int target, int t)
{

	for (int i = 0; i < t; i++)
	{
		//Gets number of team members
		int tMembers = team[i][0];

		for (int j = 1; j <= tMembers; j++)
		{
			//Returns team number
			if (team[i][j] == target)
				return i;
		}
	}
	return -1;
}

/**
* @FunctionName: initTeams
* @Description:
*    Adds items to a 2D array
* @Params:
*    ifstream &ifile - allows to read from file
*    int **&team - refernce to 2D array
*    int &t - Reference to the number of teams
* @Returns:
*    void
*/

void initTeams(ifstream &ifile, int **&team, int &t)
{
	int person;
	int tMembers;

	//Number of teams
	ifile >> t;

	team = new int*[t];

	//Reads each team
	for (int i = 0; i < t; i++)
	{
		//Number of team members
		ifile >> tMembers;

		team[i] = new int[tMembers + 1];

		//First col on each row contains number of team members
		team[i][0] = tMembers;

		//Reads each team member
		for (int j = 1; j <= tMembers; j++)
		{
			ifile >> person;
			team[i][j] = person;
		}
	}

}

/**
* @FunctionName: initQueue
* @Description:
*    Adds or removes item onto/from queue
* @Params:
*    ifstream &ifile - allows to read from file
*    teamQueue *&Q - pointer to instance of teamQueue
*    int **&team - reference to 2D array
*    int t - Number of teams
* @Returns:
*    void
*/

void initQueue(ifstream &ifile, ofstream &ofile, teamQueue<int> *&Q, int **&team, int t)
{
	string method;
	int member;

	//Reads method
	ifile >> method;

	//Loops until STOP
	while (method != "STOP")
	{
		//If method is enqueue
		if (method == "ENQUEUE")
		{
			//Reads member
			ifile >> member;

			//Gets team number
			int id = getTeamNum(team, member, t);

			//Puts item in queue
			Q->enqueue(member, id);

			ofile << Q->Print();
		}
		else
		{
			//Exception
			try
			{
				//If queue is empty
				if (Q->Empty())
					throw string("Q is empty");

				int dequeued = Q->dequeue();
				ofile << "Dequeued: " << dequeued << endl;
			}
			catch (string message)
			{
				ofile << message << endl;
			}	
		}
		//Reads method
		ifile >> method;
	}

	ofile << endl;
	ofile << "FINAL QUEUE:" << endl;

	//Prints final queue
	if (Q->Empty())
		ofile << "There is nothing in the queue";
	else
		ofile << Q->Print();

	ofile << endl;
}

/**
* @FunctionName: openFiles
* @Description:
*    opens files
* @Params:
*    ifstream &ifile - allows to read from file
*    ofstream &ofile - allows to write to file
* @Returns:
*    void
*/

void openFiles(ifstream &ifile, ofstream &ofile)
{
	string i = "input.txt";
	ifile.open(i);

	string o = "output.txt";
	ofile.open(o);
}

/**
* @FunctionName: printBorder
* @Description:
*    prints "*" as a border
* @Params:
*    ofstream &ofile - allows to write to file
* @Returns:
*    void
*/

void printBorder(ofstream &ofile)
{
	ofile << "\n**************************************************************\n";
	ofile << endl;
}

/**
* @FunctionName: printCaseNumber
* @Description:
*    prints out case number
* @Params:
*    ofstream &ofile - allows to write to file
*    int number - case number
* @Returns:
*    void
*/

void printCaseNumber(ofstream &ofile, int number)
{
	ofile << "Scenario #" << number << endl;
}
