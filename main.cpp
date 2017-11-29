#include<iostream>
#include<fstream>
#include<string>
#include"teamQueue.h"
using namespace std;

void closeFiles(ifstream&, ofstream&);
void freeArray(int**&,int);
int getTeamNum(int**&,int,int,int);
void initTeams(ifstream&,int**&,int&,int&);
void initQueue(ifstream&, teamQueue*&,int**&,int,int);
void openFiles(ifstream&, ofstream&);

int main()
{
	int t = 1;
	int tMembers;

	//open files
	ifstream infile;
	ofstream outfile;
	openFiles(infile, outfile);

	//Pointer to pointer of teams
	int **team;

	//Initializes team array
	initTeams(infile, team, t, tMembers);


	while (t != 0)
	{
		//Initializes teamQueue
		teamQueue *Q = new teamQueue();

		//Adds or removes items to teamQueue
		initQueue(infile, Q, team, t, tMembers);

		Q->Print();

		//Free up memory
		freeArray(team, t);

		//Initializes team array
		initTeams(infile, team, t, tMembers);


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
void freeArray(int **&team,int row)
{
	for (int i = 0; i < row; i++)
	{ //Delete subchildren of array
		delete[] team[i];
	}
	//Delete rest of array
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
*    int tMember - Number of members on team
* @Returns:
*    int - row number in array if found,otherwise -1
*/
int getTeamNum(int **&team,int target,int t,int tMembers)
{
	for (int i = 0; i < t; i++)
	{
		for (int j = 0; j < 10; j++)
		{
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
*    int &tMember - Reference to number of members on team
* @Returns:
*    void
*/
void initTeams(ifstream &ifile,int **&team,int &t,int &tMembers)
{
	int person;

	//Number of teams
	ifile >> t;

	team = new int*[t];

	//Reads each team
	for (int i = 0; i < t; i++)
	{
		//Number of team members
		ifile >> tMembers;

		team[i] = new int[10];

		//Reads each team member
		for (int j = 0; j < tMembers; j++)
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
*    int **&team - refernce to 2D array
*    int t - Number of teams
*    int tMember - Number of members on team
* @Returns:
*    void
*/
void initQueue(ifstream &ifile, teamQueue *&Q,int **&team,int t,int tMember)
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
			int id = getTeamNum(team, member,t,tMember);

			//Puts item in queue
			Q->enqueue(member, id);
		}
		else
		{
			//If Q is not empty
			if(!Q->Empty())
				Q->dequeue();
			//If queue is empty
			else
				cout << "Q is empty" << endl;
		}
		//Reads method
		ifile >> method;
	}
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
