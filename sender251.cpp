//Jordan Dorham, Brandon Mitchell, Kacy Rowe
//Message Queue Project
//CECS 326 - Operating Systems
//Professor Ratana Ngo

#include "get_info.h"
#include <cstdio>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include<bits/stdc++.h>

using namespace std;

int main() {

    // pulls from the message queue
	int qid = msgget(ftok(".",'u'), 0);

	// message buffer struct
	struct buf {
		long mtype; 
		char greeting[50];
	} msg;      // buf object 'msg'
    
	int size = sizeof(msg) - sizeof(long);
    
    // Last message to patch, to receiver1
    strcpy(msg.greeting, "Terminate process sender251 to receiver1");
	msg.mtype = 99;
	get_info(qid, (struct msgbuf *)&msg, size, 300);
    
    // Initiate Sender 251
    cout << getpid() << "Sender 251 ready!" << endl;
	
//    msgrcv(qid, (struct msgbuf *)&msg, size, 252, 0); //get message to begin from receiver1
	int totalMessages = 0;				//counts the messages
    
    srand(time(NULL));
    int randomNumber;

	while (true){
        
        // generate random number for message
        do {
            randomNumber = rand() * INT_MAX;
        } while (randomNumber % 251 != 0);
        
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
		
		totalMessages++;			//increment counter
        cout << "Message " << totalMessages << " has been sent, value sent: " << randomNumber << endl;
				
	}
    
    // send terminating message to sender997
    msg.mtype = 702;
    strcpy(msg.greeting, "Terminated receiver1");
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
    
    // Terminate sender251
	cout << getpid() << " (Sender251): now exits" << endl;
	exit(0);
}



