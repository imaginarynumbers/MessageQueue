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
        int sid;
	};
    
	//initialize struct and size
    buf msg;
	int size = sizeof(msg)-sizeof(long);
    
    //await message from sender 997
	cout << qid << " : RECEIVER 2 awaiting response" << endl;
    msgrcv(qid, (struct buf *)&msg,size,997,0);
    cout << qid << " Rec 2 got 997" << endl;
    
    //check message from 997
    if(msg.greeting[0] == 'A'){
        cout << qid << " : RECEIVER 2 got 997 message, beggining execution" << endl;
        msg.mtype = 222;//message for r1
        msgsnd(qid, (struct buf *)&msg,size,0);
        msg.mtype = 21;// starter message for sender
        msgsnd(qid, (struct buf *)&msg,size,0);
        msg.mtype = 21;//starter message for sender
        msgsnd(qid, (struct buf *)&msg,size,0);
        msg.mtype = 210;//acknowledgement for 997
        strcpy(msg.greeting," 2 says Go 997");
        msgsnd(qid, (struct buf *)&msg, size, 0);

    }
    
    
	bool status997 = true;
	while (msgCount < 5000) {
        cout << qid <<" : Receiver2 Looping" << endl;
        //receive from 257
        msgrcv(qid, (struct buf *)&msg, size,257,0);
        if( msg.sid == 257){
            cout << "Message from 257: " << msg.greeting << endl;
            if (msg.greeting[0] == 'T'){
                msg.mtype = 667;
                msgsnd(qid, (struct buf *)&msg,size,0);
            }
        }
        if (msg.sid == 997){
            cout << "Message from 997: " <<msg.greeting<< endl;
            
            if( msg.greeting[0] == 'T'){
                cout<< "997 needs to terminate, sending it to the END BOYS"<< endl;
                strcpy(msg.greeting,"Goodbye 997");
                
                msg.mtype = 777;
                msgsnd(qid,(struct buf *)&msg, size, 0);
                }

        }
        //receive from 997
        
        
        cout << "Loop increment" << endl;
        msgCount++;
    }
    
    msg.mtype = 666;
    strcpy(msg.greeting,"Terminate");
    msgsnd(qid,(struct buf *)&msg, size, 0);
    msgsnd(qid,(struct buf *)&msg, size, 0);
    msg.mtype = 777;//endcode for 997
    msgsnd(qid,(struct buf *)&msg, size ,0);
    cout << getpid() << ": now exits" << endl;
    
    
    
     exit(0);
}
