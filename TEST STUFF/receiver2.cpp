// Second Receiver
//   - accepts messages from 257 and 997 only
//   - terminates after it has receieved a total of 5000 messages

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
	int msgCount = 0;
    //join queue
    
    int qid = msgget(ftok(".", 'u'),0);
    cout<< "Receiver is getting stuff at queue : " << qid << endl;
    struct buf {
		long mtype;
		char greeting[50];
	};
	//initialize struct and size
    buf msg;
	int size = sizeof(msg)-sizeof(long);
    
    //await message from sender 997
	cout << qid << " : RECEIVER 2 awaiting response" << endl;
    msgrcv(qid, (struct buf *)&msg,size,997,0);
    
    //check message from 997
    if(msg.greeting[0] == 'A'){
        cout << qid << " : RECEIVER 2 got 997 message, beggining execution" << endl;
        msg.mtype = 210;
        strcpy(msg.greeting," 2 says Go 997");
        msgsnd(qid, (struct buf *)&msg, size, 0);
    }
    
    
	bool status997 = true;
	while (msgCount < 5000) {
        cout << qid <<" : Receiver2 Looping" << endl;
        //receive from 257
        msgrcv(qid, (struct buf *)&msg, size,257,0);
        if( msg.greeting[0] == '2'){
            cout << "Message from 257: " << msg.greeting << endl;
        }
        //receive from 997
        msgrcv(qid, (struct buf *)&msg, size, 997,0 );
        cout << "Message Received from 997" << endl;
        if( msg.greeting[0] == 'T'){
            cout<< "997 needs to terminate, sending it to the END BOYS"<< endl;
            strcpy(msg.greeting,"Goodbye 997");
            msg.mtype = 405;
            msgsnd(qid,(struct buf *)&msg, size, 0);
        }

        
        cout << "Loop increment" << endl;
        msgCount++;
    }
    
    msg.mtype = 666;
    strcpy(msg.greeting,"Terminate");
    msgsnd(qid,(struct buf *)&msg, size, 0);
    msgsnd(qid,(struct buf *)&msg, size, 0);
    cout << getpid() << ": now exits" << endl;
    
    
    
     exit(0);
}
