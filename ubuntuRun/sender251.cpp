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
        int sid;
    } msg;      // buf object 'msg'

    int size = sizeof(msg) - sizeof(long);
    
    
    
    strcpy(msg.greeting, "Terminate process sender251 to receiver1");
    msg.mtype = 100;
    get_info(qid, (struct msgbuf *)&msg, size, 300);
    
    // Initiate Sender 251
    cout << getpid() << "Sender 251 ready!" << endl;
	
    int totalMessages = 0;
   // int INT_MAX = 2147483647;
    srand(time(NULL));
    int randomNumber;
    //waits for r2
    msgrcv(qid, (struct buf *)&msg,size,21,0);
    while (true){
        msg.mtype = 251;
        msg.sid = 251;
        strcpy(msg.greeting,"251 says hi");
        msgsnd(qid, (struct msgbuf *)&msg, size, 0);

        randomNumber = rand() * INT_MAX;
        if (randomNumber % 251 == 0){
            msg.mtype = 251;
            msg.sid = 251;
            strcpy(msg.greeting,"T");
            msgsnd(qid, (struct buf *)&msg, size, 0);
            msgrcv(qid, (struct buf *)&msg, size,661, 0);
            break;
        }

        totalMessages++;
        cout << "Message " << totalMessages << " has been sent, value sent: " << randomNumber << endl;
        
    }
    
    // send terminating message to sender997
    msg.mtype = 700;
    strcpy(msg.greeting, "Terminated receiver1");
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
    
    // terminate sender251
    cout << getpid() << " (Sender251): now exits" << endl;
    exit(0);
}



