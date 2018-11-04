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
    int qid = msgget(ftok(".",'u'), 0); //pulls from the message queue
    
    // message buffer struct
    struct buf {
        long mtype;
        char greeting[50];
    } msg;          // buf object 'msg'
    
    int size = sizeof(msg)-sizeof(long);
    //--------------------------------------
    
    int totalMessages = 0;
    bool status = true;
    cout << getpid << " sender257 ready!" << endl;

    while (status) {
        // generate random number for message
        do {
            randomNumber = rand() * INT_MAX;
        } while (randomNumber % 257 != 0);
        
        msg.mtype = 200;
        msgsnd(qid, (struct msgbuf *)&msg, size, 0);
        
        totalMessages++;
        cout << "Message " << totalMessages << " has been sent, value sent: " << randomNumber << endl;
        
        // retrieve terminating message from receiver2
        msgrcv(qid, (struct msgbuf *)&msg, size, 410, 0);
        
        if (msg.greeting[0] == 'T') {
            status = false;
        }
    }
    
    // send terminating message to sender997
    msg.mtype = 703;
    strcpy(msg.greeting, "Terminated (Sender 257)");
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
    
    // terminate sender257
    cout << getpid() << ": sender 257 now exits" << endl;
    exit(0);
}
