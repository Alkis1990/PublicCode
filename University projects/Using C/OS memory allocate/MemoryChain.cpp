

#include <stddef.h>

#include "MemoryChain.h"

void MemoryChain::make() {
    number_of_memory_buckets = 0;
    number_of_used_pages = 0;
    memoryBucket = NULL;
}

void MemoryChain::destroy() {
   
}