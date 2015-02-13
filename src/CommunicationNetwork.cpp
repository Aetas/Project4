//CommunicationNetwork.h implementations

#include<iostream>
#include<string>
#include"CommunicationNetwork.h"

//*************
//=BEACON=
//*************
//Standard constructor, no all to null
beacon::beacon()
{
	next = nullptr;
	previous = nullptr;
	message = "";
}

//Takes a key value to assign while making. 
template<typename T>//template because I don't intend to always use strings
beacon::beacon(T k)
{
	key = k;
	previous = nullptr;
	next = nullptr;
	message = "";
}

//Takes a key value as well as the previous pointer. Next pointer isn't really needed as there almost never is one when a beacon/node is made
template<typename T>
beacon::beacon(T k, beacon* prev)
{
	key = k;
	previous = prev;
	next = nullptr;
	message = "";
}

std::string beacon::get_key()
{
	return key;
}

std::string beacon::get_message()
{
	return message;
}

beacon* beacon::get_next()
{
	return next;
}

beacon* beacon::get_previous()
{
	return previous;
}

void beacon::set_message(std::string arg)
{
	message = arg;
}

void beacon::set_key(std::string arg)
{
	key = arg;
}

void beacon::set_next(beacon *nxt)
{
	next = nxt;
}
//*************
//=END BEACON=
//*************


//*************
//=NETWORK=
//*************
//constructor that makes the arrayQueue to specified size. No default constructor, actually. whoops.
CommunicationNetwork::CommunicationNetwork(int qsize)
{
	crawler = nullptr;
	head = nullptr;
	queueSize = qsize;
	arrayQueue = new/*("")*/ std::string[queueSize];	//might be better implimented in a queue function
	for (int i = 0; i < queueSize; i++)	//initialize all to 'null' strings
	{
		arrayQueue[i] = "";
	}
	queueHead = 0;
	queueTail = 0;
	ini = false;	//not made yet. This is just the encaps class that dangles the nodes
}

CommunicationNetwork::~CommunicationNetwork()
{
	crawler = head;
	beacon* hitman;	//stores the node to be deleted so that the rest of the list can move on
	while (crawler != nullptr)
	{
		hitman = crawler;
		crawler = crawler->get_next();
		delete hitman;
	}
	delete[]arrayQueue;
	ini = false;	//nodes were just unmade after all
}

//builds the network
void CommunicationNetwork::build_net()
{
	crawler = new beacon("Los Angeles", nullptr);	//top of the list, no previous. thus NULL
	head = crawler;

	//repeat this forever, pretty much. Hard-coding initial build.
	beacon* n = new beacon("Phoenix", crawler);	//sets previous to crawler, which is one step behind the creation of n
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Denver", crawler);
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Dallas", crawler);
	crawler->set_next(n);
	crawler = n;
	n = new beacon("St. Louis", crawler);
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Chicago", crawler);
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Atlanta", crawler);
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Washington, D.C.", crawler);
	crawler->set_next(n);
	crawler = n;
	n = new beacon("New York", crawler);
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Boston", crawler);
	crawler->set_next(n);
	crawler = n;
	tail = crawler;

	ini = true;	//might change this later. Very easy way to see if the network has built.
	print_path();
}

void CommunicationNetwork::print_path()
{
	crawler = head;						//take it from the top
	std::cout << "===CURRENT PATH===" << std::endl;
	while (crawler != NULL)	//while it isnt the end of the list
	{
		std::cout << crawler->get_key() << " -> ";
		crawler = crawler->get_next();
	}
	std::cout << "NULL";
	std::cout << std::endl << "==================" << std::endl;
}

//circular queue methods
void CommunicationNetwork::enqueue(std::string fileData)
{
	arrayQueue[queueTail] = fileData;	//assigns argument
	queueTail++;
	if (queueTail == queueSize)	//it will equal 10 and not 9 because of the incriment after adding to 9
		queueTail = 0;
	std::cout << "E: " << fileData << std::endl;
	std::cout << "H: " << queueHead << std::endl;
	std::cout << "T: " << queueTail << std::endl;
}

std::string CommunicationNetwork::dequeue()
{
	std::string temp = arrayQueue[queueHead];	//stores return value in a temp so that it can delete before returning
	arrayQueue[queueHead] = "";	//'null'
	queueHead++;				//move head
	if (queueHead == queueSize)	//restart the loop if required
		queueHead = 0;
	return temp;
}

void CommunicationNetwork::print_queue()
{
	if (queueIsEmpty())
	{
		std::cout << "Empty" << std::endl;
		return;	//nothing to print
	}
	int i = queueHead;		//preserve queuehead since this is not a dequeue, just a print
	if (queueIsFull())		//needed a special case because head will = tail here and it is hard to tell the computer where to go from that. still looking for an alternative
	{
		std::cout << i << ": " << arrayQueue[i] << std::endl;	//print the first initial to break the case
		i++;													//properly shash it.
		while (i != queueTail)	//then go through normal loop to flush the rest.
		{
			std::cout << i << ": " << arrayQueue[i] << std::endl;
			i++;
			if (i == queueSize)	//restart if needed
				i = 0;
		}
	}
	else
	{
		while (i != queueTail)	//same loop as above
		{
			std::cout << i << ": " << arrayQueue[i] << std::endl;
			i++;
			if (i == queueSize)
				i = 0;
		}
	}
}

bool CommunicationNetwork::queueIsFull()
{
	if ((queueHead == queueTail) && (arrayQueue[queueHead] != ""))
		return true;	//queue is full when the tail and hed are on the same node, but head is not empty. Probably a better way somewhere
	return false;
}
bool CommunicationNetwork::queueIsEmpty()
{
	if (arrayQueue[queueHead] == "")
		return true;	//head will never be empty unless it has dq'd until there is nothing left. dq sets to null as well
	return false;
}

//checks if built
bool CommunicationNetwork::buildIsGood()
{
	return ini;	//true = built | false = nada
}


void CommunicationNetwork::transfer_msg(std::string msg)	//pushes a message through the nodes.
{
	std::cout << "H: " << queueHead << std::endl;
	std::cout << "T: " << queueTail << std::endl;
	crawler = head;							//set to top of the chain
	while (crawler != nullptr)				//while it is not the last one
	{
		crawler->set_message(msg);			//commit word
		std::cout << crawler->get_key() << " received " << crawler->get_message() << std::endl;	//print condition
		crawler->set_message("");			//effectively NULLs the string after it has been printed
		crawler = crawler->get_next();		//update condition
	}
	crawler = tail->get_previous();			//sets to the 2nd last to not repeat Boston
	while (crawler != nullptr)				//same loop in reverse
	{
		crawler->set_message(msg);			//commit word
		std::cout << crawler->get_key() << " received " << crawler->get_message() << std::endl;	//print condition
		crawler->set_message("");			//effectively NULLs the string
		crawler = crawler->get_previous();	//update condition
	}
}

//wound up not needing these two. Will see if they stay
int CommunicationNetwork::get_head()
{
	return queueHead;
}

int CommunicationNetwork::get_tail()
{
	return queueTail;
}

//looks at the first or last input. Could be better implemented as a bool instead of string (the argument)
std::string CommunicationNetwork::peek(std::string location)
{
	if (location == "head")
		return arrayQueue[queueHead];
	else if (location == "tail")
		return arrayQueue[queueTail];
	else
		return "";

}

//old f()
template<typename T>
beacon* CommunicationNetwork::find_city(T k)
{
	crawler = head;	//start at head
	while (crawler->get_next() != NULL)	//while it is not the end of the chain
	{
		if (crawler->get_key() == k)	//if it finds a match, return chain
			return crawler;
		crawler = crawler->get_next();	//else move on to the next city
	}
	return head;	//same as returning the last crawler iteration, really.
}

//old f()
void CommunicationNetwork::add_city()	//update to a double linked
{
	std::string ncity, pcity;				//control strings
	std::cout << "Enter a city name: " << std::endl;
	std::cin.ignore(1000, '\n');
	getline(std::cin, ncity);				//get new city
	std::cout << std::endl << "Enter a previous city name: " << std::endl;
	getline(std::cin, pcity);				//get previous city

	crawler = find_city(pcity);			//sets crawler to previous
	beacon* temp = new beacon(ncity);	//creates new node with specified name
	temp->set_next(crawler->get_next());//sets it's link to the original next
	crawler->set_next(temp);			//sets the previous node to the new one in the chain
	/*
	 * make a case for adding to the beginning of the network, as in if prev is 'first', then create new and reassign head
	*/
}

//olf f()
void CommunicationNetwork::delete_city()	//update to a double linked
{
	std::cout << "Name of the city:" << std::endl;
	std::string dcity;						//to store city name
	std::cin.ignore(1000, '\n');
	getline(std::cin, dcity);				//grab name
	beacon* temp;
	temp = find_city(dcity);				//make a temporary that points to the deleted-to-be
	crawler = head;
	while (crawler->get_next() != temp)		//find node right before delete
		crawler = crawler->get_next();		//^^
	crawler->set_next(temp->get_next());	//set the node prior to temp (the to-be-deleted) to point to the node after the one to be deleted
	delete temp;							//delete node
}
//*************
//=END NETWORK=
//*************
