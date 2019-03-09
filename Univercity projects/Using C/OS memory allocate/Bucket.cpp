
#include "Bucket.h"


Bucket::Bucket(size_t max_capacity) { // capacity in bytes
    memoryPointer = NULL;
    nextBucket = NULL;
    previousBucket = NULL;
    
    int total_pieces = 4096/max_capacity;
    number_of_bits = total_pieces;
    
    int oktades = number_of_bits / 8;
    if (oktades == 0) {
        oktades = 1;
    }
    
    bitmap = new char[oktades];
    
    for (int i=0;i<oktades;i++) {
        bitmap[i] = 0;
    }
}