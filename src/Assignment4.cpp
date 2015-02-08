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

#include"CommunicationNetwork.h"
#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::string;


int main()
{

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
			//net->build_net();
			break;
		case 2:	//print path
			//net->print_path();
			break;
		case 3:	//enqueue
			//
			break;
		case 4:	//dequeue
			//
			break;
		case 5:	//print queue
			//
			break;
		case 6:	//send entire network
			//
			break;
		case 7: //quit
			break;
		default:	//no match
			cout << "\n That was not an option.";
		}
	}

	cout << endl
		<< endl;

	return 0;
}
