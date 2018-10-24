//Jason Shortino
//Receiver1.cpp Receiver2.cpp Sender251.cpp
//Sender257.cpp Sender997.cpp
//Contains the main() and connects to msg queue made by receiver2
//Sends messages to Receiver1.cpp until the kill command is used

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include "get_info.h"
using namespace std;

int main() {
	cout << "Sender 251 PID Number: " << getpid() << endl;

	int qid = msgget(ftok(".",'u'), 0);	//connect to the message queue

	// declare my message buffer
	struct buf {
		long mtype; // required
		int number; // mesg content
	};
    
	buf msg;				//create a msg struct
	int size = sizeof(msg)-sizeof(long);	//get the size of the message
	int randNum = 251;			//assign to be first number passed
	bool end = false;			//boolean for while loop
	msg.mtype = 251;			
	msg.number = -1;			//will be sent with number = 99 when killed
	get_info(qid, (struct msgbuf *)&msg, size, 251);//will send one last message when killed
	
	msgrcv(qid, (struct msgbuf *)&msg, size, 22, 0); //get message to begin from rec2
	int count = 0;				//counts the messages

	while(!end){
		// prepare my message to send
		msg.number = randNum;		//put the num thats divisible 251 in the msg
		msg.mtype = 251; 		// set message type mtype = 117
		msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
		cout << "Message Number: " << count << " has been sent" << endl;
		count++;			//increment counter
		msgrcv(qid, (struct msgbuf *)&msg, size, 22, 0); // read mesg
		//this will stop the 251 sender from filling up the queue
		randNum = 101;			//set to force a new random number to be generated
		while(randNum % 251 != 0){	//loop until its divisible by 251
			randNum = rand();	//set to new random number
		}//end while(randNum...
	}//end while(!end)
	cout << getpid() << " (Send251): now exits" << endl;
	exit(0);
}


