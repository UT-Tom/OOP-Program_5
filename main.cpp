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

/*******************************PROTOTYPES*****************************************/
//Closes files
void closeFiles(ifstream&, ofstream&);

//Frees memory of array
void freeArray(int**&, int);

//Gets team number of item
int getTeamNum(int**&, int, int);

//Initializes teams
void initTeams(ifstream&, int**&, int&);

//Initializes queue
void initQueue(ifstream&, ofstream&, teamQueue<int>*&, int**&, int);

//Opens files
void openFiles(ifstream&, ofstream&);

//Prints border of "*"
void printBorder(ofstream&);

//Prints scenario number
void printCaseNumber(ofstream&, int);
/**********************************************************************************/

int main()
{
	int t;
	int scenario = 1;

	//open files
	fstream infile, outfile;
	openFiles(infile, outfile);

	//Pointer to pointer of teams
	int **team;

	//Initializes team array
	initTeams(infile, team, t);


	//Loops until t is 0
	while (t != 0)
	{
		//Initializes teamQueue
		teamQueue<int> *Q = new teamQueue<int>();

		//Prints Scenario #
		printBorder(outfile,false);
			printCaseNumber(outfile, scenario);
		printBorder(outfile,false);

		//Updates scenario number
		scenario++;

		//Adds or removes items to teamQueue
		initQueue(infile,outfile, Q, team, t);

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

void closeFiles(fstream &ifile, fstream &ofile)
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

int getTeamNum(int **&team,int target,int t )
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

void initTeams(fstream &ifile,int **&team,int &t)
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

void initQueue(fstream &ifile,fstream &ofile, teamQueue<int> *&Q,int **&team,int t )
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
			int id = getTeamNum(team, member,t);

			//Puts item in queue
			Q->enqueue(member, id);

			ofile<<Q->Print();
		}
		else
		{
			//Extra credit try-catch
			try
			{
				//If Q is not empty
				if (Q->Empty())
					throw string("Q is empty");

				int dequeued = Q->dequeue();
				ofile << "Dequeued: " << dequeued << endl;
			}
			catch(string message)
			{
				ofile << message << "\n";
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

void openFiles(fstream &ifile, fstream &ofile)
{

	#ifdef __linux__
		system("clear");
	#endif

	int choice;
	string i, o;

	cout << "Choose input file:\n1. input.txt\n2. Custom file\n";
	cin >> choice;

	if(choice != 1 && choice != 2){
		cout << "Not an option, try again.\n";
		openFiles(ifile,ofile);
	} else if(choice == 1) {
		i = "input.txt";
	} else {
		cout << "Name of file: ";
		cin >> i;
	}

	#ifdef _WIN32
		system("cls");
	#elif __linux__
		system("clear");
	#endif

	cout << "Choose output file:\n1. output.txt\n2. Custom file\n";
	cin >> choice;

	if(choice != 1 && choice != 2){
		cout << "Not an option, try again.\n";
		openFiles(ifile,ofile);
	} else if(choice == 1) {
		o = "output.txt";
	} else {
		cout << "Name of file: ";
		cin >> o;
	}

	ifile.open(i, ios::in);
	ofile.open(o, ios::out);

	if(!ifile.is_open() || !ofile.is_open())
		cout << "One or both of the files couldn't open. Check the filesnames!\n\n";

	printHeading(ofile,i);

	cout << "Processed " << i << " into " << o << "!\n";
}

/**
 * @FunctionName: printHeading
 * @Description:
 *    Prints out ouput heading
 * @Params:
 *    ofstream &ofile - allows to write to file
 * @Returns:
 *    void
 */

void printHeading(fstream &ofile, string input)
{
	printBorder(ofile,true);
		ofile << "Jakob Lopez && Tom Johnson\n";
	// printBorder(ofile,true);
		ofile << "Output for " << input << "\n";
	printBorder(ofile,true);
		ofile << "\n";
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

 void printBorder(fstream &ofile, bool type)
 {
 	string s;
 	for(int i = 0; i < 62; i++)
 		s += (type?"=":"*");
 	ofile << s << "\n";
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

void printCaseNumber(fstream &ofile, int number)
{
	ofile << "Scenario #" << number << "\n";
}
