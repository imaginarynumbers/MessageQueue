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
    int randomNumber;
    int totalMessages = 0;
    bool status = true;
    cout << getpid() << " sender257 ready!" << endl;

    while (status) {
        cout << "Total Messages = " << totalMessages <<endl;
        randomNumber = rand() * INT_MAX;
        cout << "Random number = " << randomNumber << endl;
        if (randomNumber % 257 == 0){
            msg.mtype = 257;
            strcpy(msg.greeting,"257 had an accident");
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);
            totalMessages++;
            cout << "Message " << totalMessages <<randomNumber<< endl;
        }
        
        totalMessages++;
        if (totalMessages > 10000){
            break;
        }
    }
    
    // send terminating message to sender997
    cout << "Teriminating 257" << endl;
    msg.mtype = 703;
    strcpy(msg.greeting, "Terminated (Sender 257)");
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
    
    // terminate sender257
    cout << getpid() << ": sender 257 now exits" << endl;
    exit(0);
}
