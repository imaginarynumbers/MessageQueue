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
    };
    
    buf msg;
    int size = sizeof(msg) - sizeof(long);
    //--------------------------------------
    int counter = 0;
    
    cout << "Receiver 1 PID: " << getpid() << endl;
    bool send997and251 = false;
    
    //get message from other receiver
    msgrcv(qid, (struct msgbuf *)&msg, size, 21, 0);
    
    while(!send997and251)
    {
        msgrcv(qid, (struct buf *)&msg, size, 100, 0);
        cout << "Message received: " << getpid() << msg.greeting << endl;
        if(msg.greeting[0] == '9')
        {
            msg.mtype = 110;
            strcpy(msg.greeting, "Message Delivered.");
            msgsnd(qid, (struct msgbuf *)&msg, size,0);
        }
        if(msg.greeting[0] == '2')
        {
            msg.mtype = 117;
            strcpy(msg.greeting, "Message Delivered.");
            msgsnd(qid, (struct msgbuf *)&msg, size,0);
        }
        if(msg.greeting[0] == 'T')
        {
            counter = counter + 1; //increment counter
        }
        if(counter == 2)
        {
            //break the while loop
            send997and251 = true;
        }
    }
    msg.mtype = 110;
    strcpy(msg.greeting, "Receiver1 finished(110).");
    msgsnd(qid, (struct msgbuf *)&msg, size,0);
    
    msg.mtype = 700;
    strcpy(msg.greeting, "Receiver1 finished(700).");
    msgsnd(qid, (struct msgbuf *)&msg, size,0);
    cout << "Receiver1 completed. " << getpid() << endl;
}

