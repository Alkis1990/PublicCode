
#include <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "Pool.h"

int Pool::POOL_CAPACITY = 10;

Pool::Pool(int poolid) {
    jobs = new Job[Pool::POOL_CAPACITY];
    nextPool = NULL;
    number_of_jobs = 0;
    current_state= true;
    sprintf(this->poolid, "%d", poolid);
}

void Pool::makepipes() {
    char buffer[1000];
    sprintf(buffer, "snd%s", poolid);
    mkfifo(buffer, 0666);
    sprintf(buffer, "rcv%s", poolid);
    mkfifo(buffer, 0666);
}

void Pool::openpipes() {
     char buffer[1000];
    sprintf(buffer, "snd%s", poolid);
    
    this->poolid_send = open(buffer, O_WRONLY);
    
    sprintf(buffer, "rcv%s", poolid);
    
    this->poolid_rcv = open(buffer, O_RDONLY);
    
}