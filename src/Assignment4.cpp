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
	unsigned int enq = 0;
	infile.open("messageIn.txt");
	string* fileData = new string[32];	//there are 32 words in this file. Theoreticall this should work.
	if (infile.is_open())
	{
		int i = 0;
		while (!infile.eof() && i < IFWORDS)
		{
			infile >> fileData[i];
			i++;
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

	while (select != 7)
	{
		//cout list of options.
		cout << "======Main Menu=====" << endl
			<< "1. Build Network" << endl
			<< "2. Print Network Path" << endl
			<< "3. Enqueue" << endl
			<< "4. Dequeue" << endl
			<< "5. Print Queue" << endl
			<< "6. Send Entire Message" << endl
			<< "7. Quit" << endl;

		//switch
		cin >> select;
		switch (select)
		{
		case 1:	//build net
			net->build_net();
			break;
		case 2:	//print path
			if (net->buildIsGood())
				net->print_path();
			else
				cout << "Build a network before attempting to print path." << endl;
			break;
		case 3:	//enqueue
			if (enq < IFWORDS)	//if there are words to enqueue
			{
				if (!net->queueIsFull())	//check if queue is full
				{
					net->enqueue(fileData[enq]);	//enqueue
					cout << "E: " << fileData[enq] << endl;
					cout << "H: " << net->get_head() << endl;
					cout << "T: " << net->get_tail() << endl;
					enq++;
				}
				else
					cout << "Queue is full." << endl;
			}
			else
			{
				cout << "No more words to queue." << endl;
			}
			break;
		case 4:	//dequeue
			if (net->buildIsGood())
			{
				if (!net->queueIsEmpty())	//if queue is not empty
				{
//					cout << "H: " << net->get_head()+1 << endl;
//					cout << "T: " << net->get_tail() << endl;
					net->transfer_msg(net->dequeue());	//transmits the message given by dq'ing
				}
				else
					cout << "Queue is empty." << endl;
			}
			else
				cout << "Build a network before attempting to transmit a message." << endl;
			break;
		case 5:	//print queue
			if (!net->queueIsEmpty())
				net->print_queue();		//works just dandy
			else
				cout << "Empty" << endl;
			break;
		case 6:	//send entire network
			if (net->buildIsGood())
			{
				while (enq < IFWORDS)
				{
					while (!net->queueIsFull() && enq < IFWORDS)
					{
						net->enqueue(fileData[enq]);
						enq++;
					}
					while (!net->queueIsEmpty())
						net->transfer_msg(net->dequeue());
				}
			}
			else
				cout << "Build a network before attempting to transmit a message." << endl;
			break;
		case 7: //quit
			cout << "Goodbye!" << endl;
			break;
		default://no match
			cout << "\n That was not an option." << endl;
		}
	}
	delete net;
	return 0;
}
