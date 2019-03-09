#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Allocator.h"
#include "AddressBucket.h"

#define PAGES_PER_BLOCK (((1024*1024)/4096)-1)

void Allocator::make() {
    this->number_of_address_buckets = PAGES_PER_BLOCK;

    memoryChain.make();

    // initialize chain
    chains[0].make(1, 32);
    chains[1].make(33, 64);
    chains[2].make(65, 128);
    chains[3].make(129, 256);
    chains[4].make(257, 512);
    chains[5].make(513, 1024);
    chains[6].make(1025, 2048);
    chains[7].make(2049, 4096);

    // initialize address chain
    for (int i = 0; i < NUMBER_OF_ADDRESSCHAINS; i++) {
        addressChains[i].addressBucket = NULL;
    }

    // allocate 1st big block
    memoryChain.memoryBucket = new MemoryChainBucket();
    memoryChain.memoryBucket->memPointer = allocateAlignedBlock();
    memoryChain.memoryBucket->nextBucket = NULL;
    memoryChain.number_of_memory_buckets = 1;
    memoryChain.number_of_used_pages = 0;
    
    currentMemoryPage = memoryChain.memoryBucket->memPointer;
}

char * Allocator::mymalloc(size_t capacity) {
    // if more than 4KB call standard malloc
    if (capacity > 4096) {
        return (char *) malloc(capacity);
    }

    // if capacity is 0 return NULL
    if (capacity == 0) {
        return NULL;
    }

    // if less than 4KB then implement algorithm...
    unsigned int ich = findchain(capacity);

    int ibkt, ibitm;

    Bucket * b = chains[ich].bucket;

    // insert into chain structure
    for (ibkt = 0; ibkt < chains[ich].number_of_buckets; ibkt++) {
        for (ibitm = 0; ibitm < b->number_of_bits; ibitm++) {
            int oktada = ibitm / 8;
            int thesi = ibitm % 8;
            int bit = (b->bitmap[oktada] & (1 << thesi)) != 0;

            if (bit == 0) {
                b->bitmap[oktada] = b->bitmap[oktada] | (1 << thesi); // set bit to 1

                if (b != chains[ich].bucket) { // if bucket is not the first bucket
                    // move bucket to the beginning of list
                    if (b->nextBucket != NULL) {
                        // o proigoumenos tou epomenou tou trexontos einai o proigoumenos tou trexontos
                        b->nextBucket->previousBucket = b->previousBucket;
                    }

                    if (b->previousBucket != NULL) {
                        b->previousBucket->nextBucket = b->nextBucket;
                    }

                    b->previousBucket = NULL;
                    b->nextBucket = chains[ich].bucket;
                    chains[ich].bucket->previousBucket = b;
                    chains[ich].bucket = b;
                }

                // return local address within page
                
                // b->memoryPointer  is page address
                // chains[ich].max : size of a part
                return b->memoryPointer + chains[ich].max * ibitm;
            }
        }
        b=b->nextBucket;
    }

    memoryChain.number_of_used_pages++;
    
   
    // allocate a new block of 1MB if needed
    // either no block exists or all blocks are full
    if ((memoryChain.number_of_used_pages-1) % PAGES_PER_BLOCK == 0 && memoryChain.number_of_used_pages != 1) {
        cout << " ****************************** New memory bucket !!  \n";
        memoryChain.number_of_memory_buckets++;
        // create a new big block
        MemoryChainBucket * mcb = new MemoryChainBucket();
        mcb->memPointer = allocateAlignedBlock();
        mcb->nextBucket = memoryChain.memoryBucket;
        memoryChain.memoryBucket = mcb; 
        memoryChain.number_of_memory_buckets++;
        
        currentMemoryPage = mcb->memPointer;
    }

    cout << "Insertion on chain " << ich << endl;
    
    // insert new bucket
    cout << " ****************************** New bucket !!  \n";
    
    Bucket * newbucket = new Bucket(chains[ich].max);    
    newbucket->previousBucket = NULL;
    newbucket->nextBucket = chains[ich].bucket;
    if (chains[ich].bucket != NULL) {
        chains[ich].bucket->previousBucket = newbucket;
    }
    chains[ich].bucket = newbucket;
    chains[ich].number_of_buckets++;
    
    newbucket->memoryPointer = currentMemoryPage;
    newbucket->bitmap[0] = newbucket->bitmap[0] | (1 << 0);
    
    currentMemoryPage=currentMemoryPage+4096;
    
    
     // insert into address structure
    unsigned int addressCategory = findcategory(newbucket->memoryPointer);
    
    AddressBucket * ab = new AddressBucket();
    ab->bucketPointer = newbucket;
    ab->memoryPointer = newbucket->memoryPointer;
    
    ab->nextAddressBucket = addressChains[addressCategory].addressBucket;
    addressChains[addressCategory].addressBucket = ab;
                
    return newbucket->memoryPointer;
}

void Allocator::myfree(char * address) {
    unsigned long int address_value = (unsigned long int ) address;
    unsigned long int offset = address_value%4096;
    unsigned long int page_address_value = address_value - offset;
    char * page_address = (char*)page_address_value;
    
    unsigned int addressCategory = findcategory(page_address);
    
    AddressBucket * p = addressChains[addressCategory].addressBucket;
    
    while (p != NULL) {
        if (p->memoryPointer == page_address) {
            Bucket * b = p->bucketPointer;
            int ibitm = offset/(4096/b->number_of_bits);
            
            int oktada = ibitm / 8;
            int thesi = ibitm % 8;
            b->bitmap[oktada] = b->bitmap[oktada] & ~ (1 << thesi);
            
            return;
        }
        p=p->nextAddressBucket;
    }
    
    free(address);
}

char * Allocator::allocateAlignedBlock() {
    char * ptr = (char*) malloc(1024*1024);
    unsigned long int ptr_value = (unsigned long int ) ptr;
    
    while (ptr_value % 4096 > 0) {
        ptr_value++;
        ptr++;
    }
    
    return ptr;    
}