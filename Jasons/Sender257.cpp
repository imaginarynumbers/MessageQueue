//Jason Shortino
//Receiver1.cpp Receiver2.cpp Sender251.cpp
//Sender257.cpp Sender997.cpp
//Contains the main() and connects to msg queue made by receiver2
//Sends messages to Receiver2 until rec2 ends

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main() {
	cout << "Sender 257 PID Number: " << getpid() << endl;

	int qid = msgget(ftok(".",'u'), 0);	//connect to message queue

	// declare my message buffer
	struct buf {
		long mtype; // required
		int number; // mesg content
	};
	buf msg;				//create msg struct
	int size = sizeof(msg)-sizeof(long);	//get size of msg
	int count = 0;				//message counter
	int randNum = 257;			//set to be first msg
	bool end = false;			//boolean to control while loop

	msgrcv(qid, (struct msgbuf *)&msg, size, 20, 0); //get message to begin from rec2

	while(!end){
		// prepare my message to send
		msg.number = randNum;	
		msg.mtype = 257; 	// set message type mtype = 117
		msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
		count++;
		cout << "Message Number: " << count << " has been sent" << endl;

		randNum = 101;			//set to force a new random number
		while(randNum % 257 != 0){	//loop until a number is evenly divisible by 257
			randNum = rand();	//get random number
		}
		msgrcv(qid, (struct msgbuf *)&msg, size, 20, 0); //get msg to check for rec2 end
		if(msg.number == 99)		//check msg number for rec2 ending
			end = true;		//if its 99 rec2 is ending so end the while loop
		
	}
	cout << getpid() << ":(Sender257) now exits" << endl;
	exit(0);
}


