//Jason Shortino
//Receiver1.cpp Receiver2.cpp Sender251.cpp
//Sender257.cpp Sender997.cpp
//Contains the main() and makes the msg queue and deletes it
//receives messages from Sender257 and Receiver2

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
	char begin;	//placeholder for the cin
	cout << "Reciever 2 PID: " << getpid() << endl;

	// create my msgQ with key value from ftok()
	int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);

	// declare my message buffer
	struct buf {
		long mtype; // required
		int number; // mesg content
	};

	buf msg;	//create the msg struct
	int size = sizeof(msg)-sizeof(long);//size of the msg
	bool send997 = true;
	cout << "Enter anything when ready to begin: " << endl;
	cin >> begin;		//Waits for user to enter anything to begin execution

	//Sends messages to tell the other programs to begin execution, to start at same time
	//Uses mtype of 20(s257), 21(rec2), 22(s251), 23(s997)
	for(int i = 20; i <= 23; i++){
		msg.number = 15;
		msg.mtype = i; 
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	}//end for
	int count = 0;		//message counter
	while(count <= 5000){
		cout << "257 message receive" << endl;
		msgrcv(qid, (struct msgbuf *)&msg, size, 257, 0); // read mesg from 257
		count++;
		cout << count << "-From: " << msg.mtype << " Message: " << msg.number << endl;
		if(count >= 5000){	//if message count has reached the limit
			cout << "Message limit reached first if" << endl;
			msg.number = 99;//set msg.number to 99 so 257 knows rec is ending
			send997 = false;
		}
		else
			msg.number = 15;//else stay at 15
		msg.mtype = 20; 	//msg number for communication between rec2 and 257
		cout << "sending 257 message" << endl;
		msgsnd(qid, (struct msgbuf *)&msg, size, 0); //msg to flag to 257 when rec2 ends
	
		if(send997){
			cout << "997 message receive" << endl;
			msgrcv(qid, (struct msgbuf *)&msg, size, 997, 0); // read mesg from 997
			count++;
			cout << count << "-From: " << msg.mtype << " Message: " << msg.number << endl;
			if(msg.number == 99){
				cout << "997 has finished setting it to false" << endl;
				send997 = false;
			}
			if(send997){
				if(count >= 5000)	//check for exit 
					msg.number = 99;
				else
					msg.number = 101;
				msg.mtype = 23; //message for sender997
				cout << "sending 997 message" << endl;
				msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			}//end if(send997)
		}//end if(send997)
	}//end while(count <= 5000)

	cout << "Reciever 2 has finished it's task. ~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Enter any single key to delete the Queue when ready" << endl;
	char over;
	cin >> over;
	// now safe to delete message queue
	msgctl (qid, IPC_RMID, NULL);

	exit(0);
}


