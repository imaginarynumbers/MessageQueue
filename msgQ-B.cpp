//
//  msgQ-B.cpp
//  CECS326 - Message Queue
//
//  Created by Kacy Rowe on 10/22/18.
//  Copyright © 2018 Kacy Rowe. All rights reserved.
//

#include "msgQ-B.hpp"
#include <iostream>

using namespace std;

int main()
{
    //create message queue with key value from ftok()
    int messageCounter = 0;
    int qid = msgget(ftok(".",'u'), IPC_EXCL|PC_CREAT|0600);
    
    //declare my message buffer
    struct buf
    {
        long mtype; //required
        char greeting[50]; //mesg content
    };
    
    buf msg;
    
    int size = sizeof(msg)-sizeof(long);
    
    msgrcv(qid,(struct msgbuf *)&msg, size 117,0); //read real message
                                                   //don't read fake message
    cout << getpid() << ": gets message" << endl;
    cout << "message: " << msg.greeting  << endl;
    
    strcat(msg.greeting, " and Adios.");
    cout << getpid() << ": sends reply" << endl;
    msg.mtype = 314; //only reading mesg with type mtype = 314
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
    cout << getpid() << ": now exits" << endl;
    
    msgrcv(qid, (struct msgbuf *)&msg, size -112, 0);
    msgrcv(qid, (struct msgbuf *)&msg, size, 0, 0);
    
    msgrcv(qid, (struct msgbuf *)&msg, size 117, 0);
    
    //now safe to delete message queue
    msgctl(qid, IPC_RMID, NULL);
    
    exit(0);
}


