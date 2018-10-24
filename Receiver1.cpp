//Jason Shortino
//Receiver1.cpp Receiver2.cpp Sender251.cpp
//Sender257.cpp Sender997.cpp
//Contains the main() and connects to msg queue made by receiver2
//Receives messages from Sender251.cpp and Sender997.cpp

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
	cout << "Reciever 1 PID: " << getpid() << endl;
	//int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);
	int qid = msgget(ftok(".",'u'), 0);

	// declare my message buffer
	struct buf {
		long mtype; // required
		int number; // mesg content
	};

	buf msg;
	int size = sizeof(msg)-sizeof(long);
	int count = 0;
	bool end997 = false;
	bool end251 = false;

	msgrcv(qid, (struct msgbuf *)&msg, size, 21, 0); //get message to begin from rec2

	while(!end251 || !end997){
		if(!end251){
			msgrcv(qid, (struct msgbuf *)&msg, size, 251, 0); // read mesg
						
			cout << "Message From " << msg.mtype << " : " << msg.number << endl;
			if(msg.number == 0){
				end251 = true;
			}
			else{
				msg.mtype = 22;
				msgsnd(qid, (struct msgbuf *)&msg, size, 0); // send msg
				//this message serves to slow the entry of messages by
				//the 251 sender so it doesnt fill up the queue
			}
		}//end if(!end251)
		if(!end997){
			msgrcv(qid, (struct msgbuf *)&msg, size, 998, 0); // read mesg
			cout << "Message From " << msg.mtype << " : " << msg.number << endl;
			if(msg.number == 99){
				end997 = true;
			}//end if
			else{
				msg.mtype = 23; 	// set message type mtype = 23
				msgsnd(qid, (struct msgbuf *)&msg, size, 0); // send ack msg
			}//end else
		}//end if(!end997)
		
	}//end while(!end251 || !end997)

	cout << "Reciever 1 has finished it's task. ~~~~~~~~~~~~~~~~~~~" << endl;
	

	exit(0);
}


