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
    /*
    int qid;
    if ( msgget(ftok(".",'u'), IPC_EXCL | IPC_CREAT | 0600) == -1 ){//if it exists already just use it
        qid = msgget(ftok(".",'u'),0);
    }else{
        qid = msgget(ftok(".",'u'), IPC_EXCL | IPC_CREAT | 0600);//or create a new one
    }
    */

    struct buf {
		long mtype;
		char greeting[50];
    };
	
    buf msg;
    int size = sizeof(msg)-sizeof(long);
	cout << "SENDER 997 Enters the battle" << endl;
    bool status997 = true;
    
    
    //event chance variable
    int randomNum;
    //marks the begginning of the loop
    cout <<" LAUNCHING MESSAGES FOOL" << endl;
    msg.mtype = 21;
    msgsnd(qid, (struct buf *)&msg, size, 0);
    
	while (status997){
        
        cout << "Sending message to : " << qid<< " with mtype : " << msg.mtype << endl;
        msg.mtype = 997;
        strcpy(msg.greeting, "997 Reporting for duty");//dummy message
        msgsnd(qid, (struct buf *)&msg, size,0);
        
        cout << "Generating Random Event" << endl;
        randomNum = (rand() % 500 + 1);
        
        if (randomNum < 100){
            cout << "Event random number detected, number = " << randomNum << endl;
            msg.mtype = 997;
            strcpy(msg.greeting,"Messenger says HI BITCH");
            msgsnd(qid, (struct buf *)&msg, size, 0);
                        //mtype code 405 = kill loop
            cout << "Attempting to receive my kill orders" << endl;
            msgrcv(qid,(struct buf *)&msg,size,405,0);
            cout << "Kill orders =(" << endl;
            
            if( msg.greeting[0] == 'G' ){
                cout << "Messenger received end, goodbye" << endl;
                status997 = false;
                break;
            }
        }
        
	}
    
    //once the code reaches the end of this, the queue is killed
	msgctl(qid, IPC_RMID, NULL);
    cout << qid << ": Queue destroyed" << endl;
	//Sender 257 Terminates
	cout << getpid() << ": now exits" << endl;
    
     exit(0);
}

