#ifndef COMMUNICATIONNETWORK_H
#define COMMUNICATIONNETWORK_H
#include<string>
class beacon
{
public:
	beacon();						//initial build
	template<typename T>
	beacon(T k);					//builds with key
	template<typename T>
	beacon(T k, beacon* prev);		//builds with key and previous

	std::string get_key();			//returns key (aka name here)
	std::string get_message();		//return value
	beacon* get_next();				//return next node
	beacon* get_previous();			//return previous node
	void set_message(std::string);	//commits values
	void set_key(std::string);		//commits key/name
	void set_next(beacon*);			//commits next in chain

private:
	std::string key;		//name, really.
	std::string message;	//value(s)
	beacon* next;			//next in the chain
	beacon* previous;		//previous in the chain
};

class CommunicationNetwork
{
    public:
        CommunicationNetwork(int);
        virtual ~CommunicationNetwork();
        //circular queue methods
        void enqueue(std::string);
		
        std::string dequeue();		//should send through network, call transmit msg
        void print_queue();
		void build_net();			//builds the network. hardcoded initial names
		void print_path();			//prints whole chain with names
        bool queueIsFull();			//send when full
		bool queueIsEmpty();
		void transfer_msg(std::string);		//pushes a message through the nodes.
		template<typename T>
		beacon* find_city(T k);		//finds a city by name
		void add_city();			//inserts city
		void delete_city();			//calls the delete query
		bool buildIsGood();			//checks if the network has been built
		int get_tail();
		int get_head();
		std::string peek(std::string);

    private:
		bool ini;
        beacon* head;
        beacon* tail;
		beacon* crawler;	//may not need. could have just made one every time i needed it
        int queueSize;
        int queueHead;
        int queueTail;
        std::string *arrayQueue;
};

#endif // COMMUNICATIONNETWORK_H
