//
//  msgQ-A.cpp
//  CECS326 - Message Queue
//
//  Created by Kacy Rowe on 10/22/18.
//  Copyright © 2018 Kacy Rowe. All rights reserved.
//

#include "msgQ-A.hpp"
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
    
    msg.mtype = 111; //set message type mtype = 111
    strcpy(msg.greeting,"Fake message");
    
    msgsnd(qid,(struct msgbuf *)&msg, size, 0);
    
    msg.mtype = 113; //set message type mtype = 113
    strcpy(msg.greeting,"Another fake message");
    
    msgrcv(qid, (struct msgbuf *)&msg, size,0);
    
    cout << getpid()  << ": gets message" << endl;
    
    cout << "message: " << msg.greeting << endl;
    
    //prepare my message to send
    strcpy(msg.greeting, "Hello there");
    
    cout << getpid() << ": sends greeting" << endl;
    msg.mtype = 117;    //set message type mtype = 117
    msgsnd(qid, (struct msgbuf *)&msg, size, 0); //halt here until message is copied successfully
    
    msgrcv(qid, (struct msgbuf *)&msg, size 314, 0) //halt here until message is copied successfully
    cout << getpid() << ": gets reply" << endl;
    cout << "reply: " << msg.greeting << endl;
    cout << getpid() << ": now exits" << endl;
    
    msg.mtype = 117;
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
    
    exit(0);
    
}
