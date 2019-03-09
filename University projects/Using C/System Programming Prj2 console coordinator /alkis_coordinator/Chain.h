
#ifndef CHAIN_H
#define CHAIN_H

#include "Pool.h"

#include <cstdio>

class Chain {
public:
    Pool * pool;
    Pool * lastPool;
    int number_of_jobs;
    int number_of_pools;
    
    void make();
    void destroy();       
};

#endif /* CHAIN_H */

