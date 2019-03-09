
#ifndef QUEUE_H
#define QUEUE_H

#include "Job.h"

#include <cstdio>

class Queue {
public:
    char ** data; //  "IP:PORT:FILE"
    int start;
    int end;
    int count;
    
    static int CAPACITY;

    pthread_mutex_t mtx;
    pthread_cond_t cond_nonempty;
    pthread_cond_t cond_nonfull;
    
    void make();
    void destroy();
    
    void place(char * data);
    char * obtain();
};


#endif /* GROUP_H */

