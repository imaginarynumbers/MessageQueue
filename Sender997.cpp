//Jason Shortino
//Receiver1.cpp Receiver2.cpp Sender251.cpp
//Sender257.cpp Sender997.cpp
//Contains the main() and connects to msg queue made by receiver2
//Connects to msg queue and sends messages to both receivers

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	srand(time(NULL));
	cout << "Sender 997 PID Number: " << getpid() << endl;

	int qid = msgget(ftok(".",'u'), 0);

	// declare my message buffer
	struct buf {
		long mtype; // required
		int number; // mesg content
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	int count = 0;
	int randNum = 997;
	bool end = false;
	bool over = false;
	bool rec1 = true;
	bool rec2 = true;
	msgrcv(qid, (struct msgbuf *)&msg, size, 23, 0); //wait for start message
	while(!over){
		if(end)
			over = true;
		if(rec2){
			// prepare my message to send
			if(end)
				msg.number = 99;
			else
				msg.number = randNum;	
			msg.mtype = 997; 	// set message type mtype = 997
			msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
			count++;
			cout << "Rec2 Message Number: " << count << " has been sent" << endl;
			if(!end){
				msgrcv(qid, (struct msgbuf *)&msg, size, 23, 0); // reading ack msg
				if(msg.number == 99){
					rec2 = false;
					cout << "Receiver2 is ending~~~~~~~~~~~~" << endl;
				}
			}
		}//end if(rec2)
		if(rec1){
			if(end)
				msg.number = 99;
			else
				msg.number = randNum;	
			msg.mtype = 998; 	// set message type mtype = 997
			msgsnd(qid, (struct msgbuf *)&msg, size, 0); // sending
			count++;
			cout << "Rec1 Message Number: " << count << " has been sent" << endl;
			if(!end)
				msgrcv(qid, (struct msgbuf *)&msg, size, 23, 0); // reading ack msg
		}
		randNum = 101;
		while(randNum % 997 != 0){
			randNum = rand();
			if(randNum < 100){
				end = true;
				cout << "Sender997 is done, sending final message" << endl;
			}//end if
		}//end while(randNum...
	}//end while(!end)
	
	cout << getpid() << ": now exits" << endl;
	exit(0);
}


