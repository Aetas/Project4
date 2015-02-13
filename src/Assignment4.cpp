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

/*
 * There are a few functions in the NetworkComminucation class that are not used simply 
 * because I brought them over from the last assignment with singly linked lists 
 * (meaning not only are they not used, but they have extremely poor error handling and don't actually
 * function well with a doubly linked list) 
 * Then there are the functions like get_tail/head and peek() that I was using to check for 
 * queue status, but ended up ditching because COG wanted things to be done within functions, so
 * I wrote a pair of functions to check for complete or empty queue and that handed that. 
 * I rather like the peek function, but I feel like I could change it to a temple or bool
 * so that inputs/requests can be 0/1, etc. extensibility increased.
*/
#ifndef IFWORDS
#define IFWORDS 32	//sets an upper limit based on the words in the file. Which I know by reading it with mein own eyes
#endif
#include"CommunicationNetwork.h"	//CommunicationNetwork + beacon
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
	unsigned int enq = 0;	//number of times enqueued so 
	infile.open("messageIn.txt");
	string* fileData = new string[32];	//there are 32 words in this file. Theoreticall this should work.
	if (infile.is_open())	//check if open
	{
		int i = 0;			//while loop wound up being better so that the newline character was not extracted. Also I can ditch a buffer string
		while (!infile.eof() && i < IFWORDS)	//32 words, no need for more
		{
			infile >> fileData[i];
			i++;
		}
	}
	else
	{
		cout << "----File was not found. Check local folder for \"messageIn.txt\"----"	//I intend to change this later to match my file structure when i don't have to deal with COG
			<< endl
			<< endl;
		return 0;
	}
	infile.close();	//close

	unsigned int select = 0;

	while (select != 7)	//7 = exit
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
			if (net->buildIsGood())	//if the network was built. Really it just checks if a bool was kicked.
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
					enq++;
				}
				else
					cout << "Queue is full." << endl;
			}
			else
			{
				cout << "No more words to queue." << endl;	//if enq is 32, then all of the words have been read
			}
			break;
		case 4:	//dequeue
			if (net->buildIsGood())
			{
				if (!net->queueIsEmpty())	//if queue is not empty
					net->transfer_msg(net->dequeue());	//transfers the message given by dq'ing
				else
					cout << "Queue is empty." << endl;
			}
			else
				cout << "Build a network before attempting to transmit a message." << endl;
			break;
		case 5:	//print queue
			if (!net->queueIsEmpty())	//nothing to print if the queue is empty
				net->print_queue();		//works just dandy
			else
				cout << "Empty" << endl;
			break;
		case 6:	//send entire network
			if (net->buildIsGood())	//if net was built
			{
				while (enq < IFWORDS)	//there are only IFWORDS(32) in the array, do not go over
				{
					while (!net->queueIsFull() && enq < IFWORDS)	//while the queue is filling and index is less than 32...
					{
						net->enqueue(fileData[enq]);
						enq++;	//number pulled
					}
					while (!net->queueIsEmpty())	//dqueue until empty. Rinse repeat.
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
