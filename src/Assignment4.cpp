/*
 * Derek Prince
 * 2-7-15
 * CSCI 2270 - Rhonda Hoenigman
 * CU@Boulder
 * Assignment 4
 * Taking the ring to Boston (Again.)
 * Deque control with classes
 *
*/
#ifndef IFWORDS
#define IFWORDS 32	//sets an upper limit based on the words in the file. Which I know by reading it with mein own eyes
#endif
#include"CommunicationNetwork.h"
#include<iostream>
#include<fstream>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	CommunicationNetwork* net = new CommunicationNetwork(10);	//queue size of 10
	std::ifstream infile;
	unsigned int fdcount = 0;
	infile.open("messageIn.txt");
	string* fileData = new string[32];	//there are 32 words in this file. Theoreticall this should work. a simple string might be even better. meh.
	if (infile.is_open())
	{
		string buffer;
		while (getline(infile, buffer, ' '))
		{
			fileData[fdcount] = buffer;
		}
	}
	else
	{
		cout << "----File was not found. Check local folder for \"messageIn.txt\"----"
			<< endl
			<< endl;
		return 0;
	}
	infile.close();


	unsigned int select = 0;
	//cout list of options.
	cout << "======Main Menu======" << endl
		<< "1. Build Network" << endl
		<< "2. Print Network Path" << endl
		<< "3. Enqueue" << endl
		<< "4. Dequeue" << endl
		<< "5. Print Queue" << endl
		<< "6. Send Entire Network" << endl
		<< "7. Quit" << endl;

	while (select != 7)
	{
		//switch
		cin >> select;
		switch (select)
		{
		case 1:	//build net
			net->build_net();
			break;
		case 2:	//print path
			if(net->checkbuild())
				net->print_path();
			else
				cout << "Build a network before attempting to print path." << endl;
			break;
		case 3:	//enqueue
			if (fdcount < IFWORDS)
			{
				net->enqueue(fileData[0]);
				fdcount++;
			}
			break;
		case 4:	//dequeue
			if (net->checkbuild())	//this is the problem child
			{
				net->transfer_msg(net->dequeue());	//transmits the message given by dq'ing
			}
			else
				cout << "Build a network before attempting to transmit a message." << endl;
			break;
		case 5:	//print queue
			//net->print_path();
			break;
		case 6:	//send entire network
			if (net->checkbuild())
				net->print_path();
			else
				cout << "Build a network before attempting to transmit a message." << endl;
			break;
		case 7: //quit
			cout << "Goodbye!" << endl;
			break;
		default:	//no match
			cout << "\n That was not an option.";
		}
	}

	cout << endl
		<< endl;

	return 0;
}
