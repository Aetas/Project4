//CommunicationNetwork.h implementations

#include<iostream>
#include<string>
#include"CommunicationNetwork.h"


CommunicationNetwork::CommunicationNetwork(int arg)
{

}

CommunicationNetwork::~CommunicationNetwork()
{

}

//circular queue methods
void CommunicationNetwork::enqueue(std::string)
{

}

std::string CommunicationNetwork::dequeue() //should send through network, call transmit msg
{

}

void CommunicationNetwork::printQueue()
{

}

void CommunicationNetwork::buildNetwork()
{
	crawler = new beacon;
	head = crawler;
	crawler->set_key("Los Angeles");

	//repeat this forever, pretty much. Hard-coding initial build.
	beacon* n = new beacon("Phoenix");
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Denver");
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Dallas");
	crawler->set_next(n);
	crawler = n;
	n = new beacon("St. Louis");
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Chicago");
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Atlanta");
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Washington, D.C.");
	crawler->set_next(n);
	crawler = n;
	n = new beacon("New York");
	crawler->set_next(n);
	crawler = n;
	n = new beacon("Boston");
	crawler->set_next(n);
	crawler = n;

	print_path();
}

void CommunicationNetwork::printPath()
{

}

bool CommunicationNetwork::queueIsFull()
{

}//send when full

void CommunicationNetwork::transmitMsg(std::string)
{

}

