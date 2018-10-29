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
    };
    
    buf msg;
    int size = sizeof(msg)-sizeof(long);
    //--------------------------------------
    
    
}
