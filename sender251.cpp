//Jordan Dorham, Brandon Mitchell, Kacy Rowe
//Message Queue Project
//CECS 326 - Operating Systems
//Professor Ratana Ngo


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {

	int qid = msgget(ftok(".",'u'), 0);	//pulls from the message queue

	// message buffer struct
	struct buf {
		long mtype; 
		int number; 
	};
    
    buf msg;				
	int size = sizeof(msg) - sizeof(long);
    
    // Initiate Sender 251
    cout << getpid() << "Sender 251 ready!" << endl;
    

	int randomNum = 251;			
	bool status251 = false;			//boolean for while loop
	msg.mtype = 251;			
	msg.number = -1;			// sent with number = 99 to kill

	// confirmation message when process is killed
	get_info(qid, (struct msgbuf *)&msg, size, 251);  
	
	msgrcv(qid, (struct msgbuf *)&msg, size, 252, 0); //get message to begin from receiver1
	int totalMessages = 0;				//counts the messages

	while(!status251){
		msg.number = randomNum;		// send message with number divisible 251
		
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
		
		totalMessages++;			//increment counter
		cout << "Message " << totalMessages << " has been sent" << endl;
		
		msgrcv(qid, (struct msgbuf *)&msg, size, 252, 0); 
		
		// stop 251 sender from filling up message queue
		randomNum = 91;			// set up for a new random number
		while(randomNum % 251 != 0){	//loop until its divisible by 251
			randomNum = rand();	
		}
	} 
	cout << getpid() << " (Sender251): now exits" << endl;
	exit(0);
}



