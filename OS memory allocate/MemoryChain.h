
#ifndef MEMORYBUCKET_CHAIN_H
#define MEMORYBUCKET_CHAIN_H

#include "MemoryChainBucket.h"

#include <cstdio>

class MemoryChain {
public:
    MemoryChainBucket * memoryBucket;
    int number_of_memory_buckets;
    int number_of_used_pages;
    
    void make();
    void destroy();
};

#endif /* CHAIN_H */

