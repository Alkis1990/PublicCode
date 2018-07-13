
#ifndef BUCKET_H
#define BUCKET_H

#include <cstdio>

class Bucket {
public:
    char * memoryPointer;
    Bucket * nextBucket;
    Bucket * previousBucket;
    
    char * bitmap;
    int number_of_bits;
    
    Bucket(size_t capacity);
};


#endif /* GROUP_H */

