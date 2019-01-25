#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>

#include "structure.h"

void downFull(int semid) {
    struct sembuf semopr = { 0 };
    semopr.sem_num = SEM_FULL_POS;
    semopr.sem_op = -1;
    semop(semid, &semopr, 1);
}

void downEmpty(int semid) {
    struct sembuf semopr = { 0 };
    semopr.sem_num = SEM_EMPTY_POS;
    semopr.sem_op = -1;
    semop(semid, &semopr, 1);
}

void downStats(int semid) {
    struct sembuf semopr = { 0 };
    semopr.sem_num = SEM_STATS;
    semopr.sem_op = -1;
    semop(semid, &semopr, 1);
}

void upFull(int semid) {
    struct sembuf semopr = { 0 };
    semopr.sem_num = SEM_FULL_POS;
    semopr.sem_op = +1;
    semop(semid, &semopr, 1);
}

void upEmpty(int semid) {
    struct sembuf semopr = { 0 };
    semopr.sem_num = SEM_EMPTY_POS;
    semopr.sem_op = +1;
    semop(semid, &semopr, 1);
}

void upStats(int semid) {
    struct sembuf semopr = { 0 };
    semopr.sem_num = SEM_STATS;
    semopr.sem_op = +1;
    semop(semid, &semopr, 1);
}