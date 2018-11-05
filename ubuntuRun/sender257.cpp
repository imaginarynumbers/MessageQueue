//Jordan Dorham, Brandon Mitchell, Kacy Rowe
//Message Queue Project
//CECS 326 - Operating Systems
//Professor Ratana Ngo

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int qid = msgget(ftok(".",'u'), 0); //pulls from the message queue
    
    // message buffer struct
    struct buf {
        long mtype;
        char greeting[50];
        int sid;
    } msg;          // buf object 'msg'
    
    int size = sizeof(msg)-sizeof(long);
    //--------------------------------------
    int randomNumber;
    int totalMessages = 0;
   // int INT_MAX = 2147483647;
    bool status = true;
    
    cout << getpid() << " sender257 ready!" << endl;
    //waits for r2
    msgrcv(qid, (struct buf *)&msg,size,21,0);
    while (status) {
        randomNumber = rand() * INT_MAX;
        cout << "Random number = " << randomNumber << endl;
        
        if (randomNumber % 257 == 0){
            msg.mtype = 257;
            msg.sid = 257;
            strcpy(msg.greeting,"T-257 had an accident");
            cout<< msg.greeting << endl;
            msgsnd(qid, (struct buf *)&msg, size, 0);
            msgrcv(qid, (struct buf *)&msg,size,667,0);//receives message from r2
            break;
        }
        
        
    }
    
    // send terminating message to sender997
    /*
    cout << "Teriminating 257" << endl;
    msg.mtype = 703;
    msg.sid = 257;
    strcpy(msg.greeting, "Terminated (Sender 257)");
     */
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
    
    // terminate sender257
    cout << getpid() << ": Sender 257 now exits" << endl;
    exit(0);
}
