//CommunicationNetwork.h implementations

#include<iostream>
#include<string>
#include"CommunicationNetwork.h"

//*************
//=BEACON=
//*************
beacon::beacon()
{
	next = NULL;
	previous = NULL;
	message = "";
}

template<typename T>
beacon::beacon(T k)
{
	key = k;
	previous = NULL;
	next = NULL;
	message = "";
}
template<typename T>
beacon::beacon(T k, beacon* prev)
{
	key = k;
	previous = prev;
	next = NULL;
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
CommunicationNetwork::CommunicationNetwork(int qsize)
{
	crawler = NULL;
	head = NULL;
	queueSize = qsize;
	arrayQueue = new/*("")*/ std::string[queueSize];	//might be better implimented in a queue function
	for (int i = 0; i < queueSize; i++)	//initialize all to 'null' strings
	{
		arrayQueue[i] = "";
	}
	queueHead = 0;
	queueTail = 0;
	ini = false;
}

CommunicationNetwork::~CommunicationNetwork()
{
	crawler = head;
	beacon* hitman;
	while (crawler != NULL)
	{
		hitman = crawler;
		crawler = crawler->get_next();
		delete hitman;
	}
	delete[]arrayQueue;
}

//builds the network
void CommunicationNetwork::build_net()
{
	crawler = new beacon("Los Angeles", NULL);	//top of the list, no previous. thus NULL
	head = crawler;
	//crawler->set_key("Los Angeles");

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
	std::cout << std::endl << "=================" << std::endl;
}

//circular queue methods
void CommunicationNetwork::enqueue(std::string fileData)
{
	if (queueIsFull())
	{
		std::cout << "Queue is full." << std::endl;
	}
	else
	{
		arrayQueue[queueHead] = fileData;
		queueHead++;
	}
}

std::string CommunicationNetwork::dequeue()
{
	if (arrayQueue[queueTail] != "")
	{	
		std::string tmp = arrayQueue[queueTail];	//must have a temporary to delete before exit
		for (int i = queueTail; i < queueHead; i++)	//shifts the array down onto tail so it does not overflow
		{
			std::string shifty = arrayQueue[i + 1];
			arrayQueue[i] = shifty;
		}
		queueHead--;
		return tmp;	//tail is the first in, as i'm proverbially stacking them, so first out.
	}
	std::cout << "Queue is empty." << std::endl;
	return arrayQueue[queueTail];
}

void CommunicationNetwork::print_queue()
{
	for (int i = 0; i < queueSize; i++)
	{
		std::cout << i + 1 << ": " << arrayQueue[i];
		//if(arrayQueue != "") {...};
	}
}

bool CommunicationNetwork::queueIsFull()
{
	if (queueHead == queueSize)
		return true;
	return false;
}

//checks if built
bool CommunicationNetwork::checkbuild()
{
	if (ini)	//ini is only true if net_build() has run
		return true;
	return false;
}


void CommunicationNetwork::transfer_msg(std::string msg)	//pushes a message through the nodes.
{
		crawler = head;							//set to top of the chain
		while (crawler != NULL)	//while it is not the last one
		{
			crawler->set_message(msg);			//commit word
			std::cout << crawler->get_key() << " recieved " << crawler->get_message() << std::endl;	//print condition
			crawler->set_message("");			//effectively NULLs the string after it has been printed
			crawler = crawler->get_next();		//update condition
		}
		/*while (crawler != NULL)	//same loop in reverse
		{
			crawler->set_message(msg);			//commit word
			std::cout << crawler->get_key() << " recieved " << crawler->get_message() << std::endl;	//print condition
			crawler->set_message("");			//effectively NULLs the string
			crawler = crawler->get_previous();	//update condition
		}*/
}

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
}

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
