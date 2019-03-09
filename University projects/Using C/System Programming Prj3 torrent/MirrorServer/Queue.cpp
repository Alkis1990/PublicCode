
#include <stddef.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <pthread.h>

#include "Queue.h"

int Queue::CAPACITY = 10;

void Queue::make() {
    pthread_mutex_init(&mtx, 0);
    pthread_cond_init(&cond_nonempty, 0);
    pthread_cond_init(&cond_nonfull, 0);

    start = 0;
    end = -1;
    count = 0;
    
    data = new char*[CAPACITY];
}

void Queue::destroy() {
    pthread_cond_destroy(&cond_nonempty);
    pthread_cond_destroy(&cond_nonfull);
    pthread_mutex_destroy(&mtx);
    
    delete [] data;
}

void Queue::place(char * newdata) {
    pthread_mutex_lock(&mtx);
    while (count >= CAPACITY) {
        pthread_cond_wait(&cond_nonfull, &mtx);
    }
    end = (end + 1) % CAPACITY;
    data[end] = newdata;
    count++;
    pthread_cond_signal(&cond_nonempty);
    pthread_mutex_unlock(&mtx);
}

char * Queue::obtain() {
    char * olddata = NULL;
    pthread_mutex_lock(&mtx);
    while (count <= 0) {
        pthread_cond_wait(&cond_nonempty, &mtx);
    }
    olddata = data[start];
    start = (start + 1) % CAPACITY;
    count--;
    pthread_cond_signal(&cond_nonfull);
    pthread_mutex_unlock(&mtx);
    return olddata;
}
