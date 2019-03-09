
#ifndef POOLJOB_H
#define POOLJOB_H

#include "Job.h"

#include <cstdio>

class PoolJob {
public:
    char jobid[20];
    char jobstatus[20]; // "active", "inactive", "terminated"
    time_t created_time; 
    pid_t pid;
    
    PoolJob * nextPoolJob;
};


#endif /* GROUP_H */

