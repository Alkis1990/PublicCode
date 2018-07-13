
#include "Allocator.h"
#include "mymalloc.h"

static Allocator * myallocator = NULL;

char * mymalloc(size_t capacity) {
    if (myallocator == NULL) {
        myallocator = new Allocator();
        myallocator->make();
    }
    
    return myallocator->mymalloc(capacity);
}

void myfree(char* address) {
    myallocator->myfree(address);
}
