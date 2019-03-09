
#ifndef ADDRESS_BUCKET_H
#define ADDRESS_BUCKET_H

#include <cstdio>

class AddressBucket {
public:
    char * memoryPointer;
    Bucket * bucketPointer;
    
    AddressBucket * nextAddressBucket;
};


#endif /* GROUP_H */

