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
    
    int qid = msgget(ftok(".", 'u'),0); //IPC_EXCL|IPC_CREAT|0600);
    cout<< "Receiver is getting stuff at queue : " << qid << endl;
    struct buf {
		long mtype;
		char greeting[50];
	};
	
    buf msg;
	int size = sizeof(msg)-sizeof(long);

	cout << "RECEIVER 2 awaiting response" << endl;
    
    //msgrcv(qid, (struct buf *)&msg, size, 21, 0);
    
    
    
	bool status997 = true;
	while (msgCount < 5000) {
        //cin.get();
        msg.mtype = 405;
        strcpy(msg.greeting,"Goodbye 997");

        msgsnd(qid,(struct buf *)&msg, size, 0);
        cout << "Looping" << endl;
        
        msgrcv(qid, (struct buf *)&msg, size, 997,0 );
        
        if( msg.greeting[0] == 'M'){
            cout<< "997 needs to terminate, sending it to the END BOYS"<< endl;
            strcpy(msg.greeting,"Goodbye 997");
            msg.mtype = 405;
            msgsnd(qid,(struct buf *)&msg, size, 0);
            break;
        }
        
        msgrcv(qid,(struct buf *)&msg, size, 257, 0);
        cout << "Loop increment" << endl;
        msgCount++;
    }

	cout << getpid() << ": now exits" << endl;
    
    
    
     exit(0);
}
