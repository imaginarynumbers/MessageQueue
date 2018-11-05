#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
using namespace std;

int main() {
	srand(time(NULL));
    //int qid =  msgget(ftok(".",'u'),0);
    
    int qid = msgget(ftok(".",'u'), IPC_EXCL | IPC_CREAT | 0600);
    struct buf {
		long mtype;
		char greeting[50];
        int sid;
    };
	
    buf msg;
    int size = sizeof(msg)-sizeof(long);
	cout << "SENDER 997 Enters the battle" << endl;
    cout << "Queue created at : "<< qid <<endl;
    bool status997 = true;
    
    
    //event chance variable
    int randomNum;
    
    //Send message to receiver1 with mytype 100
    strcpy(msg.greeting, "Attempting to message receiever1 from sender 997.");
    cout << getpid() << ":  messaging receiver1" << endl;
    msg.mtype = 997;
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
    
    
	while (status997){
        
        cout << "Sending message to : " << qid<< " with mtype : " << msg.mtype << endl;
        //msg to rec2
        msg.mtype = 257;
        msg.sid = 997;
        strcpy(msg.greeting, "997 Reporting for duty");//dummy message
        msgsnd(qid, (struct buf *)&msg, size,0);
        //message to rec1
        msg.mtype = 251;
        msg.sid = 997;
        strcpy(msg.greeting, "997 Reporting for duty");//dummy message
        msgsnd(qid, (struct buf *)&msg, size,0);

        
        cout << "Generating Random Event" << endl;
        randomNum = (rand() % 10000 + 1);
        cout << randomNum << endl;
        
        
        if (randomNum < 10){
            
            cout << "KILL CHANCE SUCCESS = " << randomNum << endl;
            msg.mtype = 251;
            msg.sid = 997;
            strcpy(msg.greeting,"T his messenger says bye");
            msgsnd(qid, (struct buf *)&msg, size, 0);
            msg.mtype = 257;
            msg.sid = 997;
            msgsnd(qid, (struct buf *)&msg,size, 0);
            cout << "T-Attempting to receive my kill orders" << endl;
            msgrcv(qid,(struct buf *)&msg, size,777, 0);
            cout << "Messenger received end, goodbye" << endl;
            status997 = false;
            break;
            
        }
        
    
	}
    
    msgctl(qid, IPC_RMID, NULL);
    cout << qid << ": Queue destroyed" << endl;
	//Sender 257 Terminates
	cout << getpid() << ": now exits" << endl;
    
     exit(0);
}

