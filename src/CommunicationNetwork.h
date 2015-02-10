#ifndef COMMUNICATIONNETWORK_H
#define COMMUNICATIONNETWORK_H
#include<string>
struct node{
	
	node();					//std construct - may not be used.
	node(node* prev, node* nxt);	//will need both previous and next at creation time.
	node(node* prev);				//works well for single linked list, will have to see about this
    std::string name;		//name
    std::string message;	//intended to hold one word
    node *next;				//pointing the way to mordor
    node *previous;			//poiting the way to the shire

};

class CommunicationNetwork
{
    public:
        CommunicationNetwork(int);		
        virtual ~CommunicationNetwork();	//virtual destructor..? no derivation anyhow
        //circular queue methods
        void enqueue(std::string);			//read until full. 
        std::string dequeue(); 				//pops queue when full
        void printQueue();					//reads what is being stored in the q, mostly testing
        void buildNetwork();				//builds.
        void printPath();					//prints path
        bool queueIsFull(); 				//send when full
        void transmitMsg(std::string);		//deq master call, pushes through network

    private:
        node *head;				//yop
        node *tail;				//bottom
        unsigned int queueSize;	//
        unsigned int queueHead;	//
        unsigned int queueTail;	//
        std::string *arrayQueue;//
};

#endif // COMMUNICATIONNETWORK_H
