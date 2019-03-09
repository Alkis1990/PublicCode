
#ifndef POOL_H
#define POOL_H

#include "Job.h"

#include <cstdio>

class Pool {
public:
    char poolid[20];
    pid_t pid;
    
    Job * jobs;
    Pool * nextPool;
    
    bool current_state; // true: running    false: finished
    
    int number_of_jobs;
    int poolid_rcv;
    int poolid_send;
    
    static int POOL_CAPACITY;   
    
    Pool(int poolid);
    
    void makepipes();
    void openpipes();
};


#endif /* GROUP_H */

