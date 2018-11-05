//Jordan Dorham, Brandon Mitchell, Kacy Rowe
//Message Queue Project
//CECS 326 - Operating Systems
//Professor Ratana Ngo

#include<iostream>
#include<signal.h>
#include<unistd.h>
#include <sys/types.h>

void get_info(int qid, msgbuf *exitmsg, int size, long mtype);
