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
    srand(time(NULL));
    
    //message buffer struct
    struct buf {
        long mtype;
        char greeting[50];
    };
    
    buf msg;
    int size = sizeof(msg)-sizeof(long);
    //--------------------------------------
    
    //initiate Sender 997
    cout << getpid() << "Sender 997 is here and ready to initialize." << endl;
    //verification boolean declarations
    bool receiverStatus = false; //verification
    bool receiverStatus2 = false; //verification
    bool statusOf997 = false; //verification
    //random number generators
    unsigned long maximumRandomNumber = 1306784398;
    unsigned long generateRandomNumber;
    
    //begin messaging
    while(receiverStatus || receiverStatus2 )
    {
        if(msgrcv(qid, (struct msgbuf *)&msg, size, 999, 0) == 0)
        {
            receiverStatus2 = true; //message received 2
            if(msgrcv(qid, (struct msgbuf *)&msg, size, 998, 0) == 0)
            {
                //message received 1
                receiverStatus = true;
                statusOf997 = true;
            }
            else
            {
                //sends last message to receiver 1
                strcpy(msg.greeting, "Final message sender 997 to receiver1");
                msg.mtype = 100;
                msgsnd(qid, (struct msgbuf *)&msg, size, 0);
                statusOf997 = true;
            }
        }
        //check if message to receiver 1 was successful
        if(msgrcv(qid, (struct msgbuf *)&msg, size, 998, 0) == 0)
        {
            receiverStatus = true; //message received
            if(msgrcv(qid, (struct msgbuf *)&msg, size, 999, 0) == 0)
            {
                //check if message to receiver 2 was successful
                receiverStatus2 = true;
                statusOf997 = true;
            }
            else
            {
                //sends last message to receiver2
                strcpy(msg.greeting, "Final message sender 997 to receiver1");
                msg.mtype = 997;
                msgsnd(qid, (struct msgbuf *)&msg, size, 0);
                statusOf997 = true;
            }
        }
        //If all status check out
        if(receiverStatus && receiverStatus2 && statusOf997)
        {
            //generate random number
            generateRandomNumber = rand()%maximumRandomNumber;
            cout << "Random number = " << generateRandomNumber; //debug purposes
            if(generateRandomNumber < 100)
            {
                //last message to receiver1
                strcpy(msg.greeting, "Terminate sender 997 to receiver1");
                msg.mtype = 100;
                msgsnd(qid, (struct msgbuf *)&msg, size, 0);
                
                //last message to receiver2
                strcpy(msg.greeting, "Terminate sender 997 to receiver2");
                msg.mtype = 201;
                msgsnd(qid, (struct msgbuf *)&msg, size, 0);
                
                statusOf997 = true;
            }
            //check if message was successful
            if(generateRandomNumber%997 == 0)
            {
                //message receiver 1
                strcpy(msg.greeting, "Attempting to message receiever1 from sender 997.");
                cout << getpid() << ":  messaging receiver1" << endl;
                msg.mtype = 100;
                msgsnd(qid, (struct msgbuf *)&msg, size, 0);
                
                //verification of message
                msgrcv(qid, (struct msgbuf *)&msg, size, 110, 0);
                cout << getpid() << ": " << msg.greeting << endl;
                
                //Attempt to message
                strcpy(msg.greeting, "Attempting to message receiver2 from sender 997.");
                cout << getpid() << ": messaging to receiver2" << endl;
                msg.mtype = 997;
                msgsnd(qid, (struct msgbuf *)&msg, size, 0);
                
                //verification of message
                msgrcv(qid, (struct msgbuf *)&msg, size, 210, 0);
                cout << getpid() << ": " << msg.greeting << endl;
            }
        }
    }
    //end of messaging, purge queue and end all tasks
    msgctl(qid, IPC_RMID, NULL); //purge queue
    cout << getpid() << ": now exits" << endl; //end of 997 task
    exit(0);
    
}
