
#ifndef POOLCHAIN_H
#define POOLCHAIN_H

#include "Pool.h"
#include "PoolJob.h"

#include <cstdio>

class PoolChain {
public:
    PoolJob * pooljob;
    PoolJob * lastPooljob;
    int number_of_jobs;
    
    void make();
    void destroy();       
};

#endif /* CHAIN_H */

