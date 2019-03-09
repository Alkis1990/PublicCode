
#ifndef MEMORY_BUCKET_CHAIN_H
#define MEMORY_BUCKET_CHAIN_H

#include <cstdio>

class MemoryChainBucket {
public:
    MemoryChainBucket * nextBucket;
    char * memPointer;
    
    MemoryChainBucket();
};


#endif /* GROUP_H */

