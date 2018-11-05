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

using namespace std;

int main()
{
    int qid = msgget(ftok(".", 'u'), 0);
    
    //message buffer struct
    struct buf
    {
        long mtype; //message type
        char greeting[50];
        int sid;
    };
    
    buf msg;
    int size = sizeof(msg) - sizeof(long);
    //--------------------------------------
    int counter = 0;
    
    cout << "Receiver 1 PID: " << getpid() << endl;
    bool send997and251 = false;
    
    //get message from 997
    msgrcv(qid, (struct buf *)&msg, size, 997, 0);
    cout << qid << " : RECEIVER 1 continuing execution" << endl;
    
    if (msg.greeting[0] == 'A' ){
        cout << "Message received from sender 997, beginning runtime" << endl;
        msg.mtype = 110;
        strcpy(msg.greeting," 1 says Go 997");
        msgsnd(qid, (struct buf *)&msg, size, 0);
        cout<< "Awaiting message from r2" << endl;
        msgrcv(qid, (struct buf *)&msg, size,222,0);//receive message from r2
    }
    
    while(!send997and251)
    {
        msgrcv(qid, (struct buf *)&msg, size, 251, 0);
        cout << "Message received: "<< msg.greeting << endl;
                
        if(msg.greeting[0] == 'T'){
            counter++;
        }
        if(counter == 2){
            send997and251 = true;
            msg.mtype = 405;
            msgsnd(qid,(struct buf *)&msg,size,0);
            msg.mtype = 661;
            msgsnd(qid,(struct buf *)&msg,size,0);
        }
        
    }
    msg.mtype = 110;
    strcpy(msg.greeting, "Receiver1 finished(110).");
    msgsnd(qid, (struct msgbuf *)&msg, size,0);
    
    msg.mtype = 700;
    strcpy(msg.greeting, "Receiver1 finished(700).");
    msgsnd(qid, (struct msgbuf *)&msg, size,0);
    cout << getpid() <<  "Receiver1 now exits. " << getpid() << endl;
    exit(0);
}

