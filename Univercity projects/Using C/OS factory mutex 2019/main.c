
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "structure.h"
#include "timespan.h"
#include "queue.h"

#define IDLENGTH 5

double my_min(double x, double y) {
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

void place(struct Part * part, char * pmem) {
    struct Slot slot;
    slot.part = *part;
    memcpy(pmem, &slot, sizeof (struct Slot));
}

void retrieve(struct Part * part, char * pmem) {
    struct Slot slot;
    memcpy(&slot, pmem, sizeof (struct Slot));
    *part = slot.part;
}

void workConstruction(int Y, char constructionID, char * pmem_out_1, int buffer_out_1, struct Statistics * pmem_out_4, int buffer_out_4, int mint, int maxt) {
    int i;
    double delay = 0.0;

    srand(getpid());

    printf("Construction has started %d as %c \n", getpid(), constructionID);

    for (i = 0; i < Y; i++) {
        int timespan = rand() % (maxt - mint) + mint;
        usleep(timespan);

        // production
        double t1 = ((double) clock()) / CLOCKS_PER_SEC;
        downEmpty(buffer_out_1);
        double t2 = ((double) clock()) / CLOCKS_PER_SEC;

        if (t2 > t1) {
            delay = delay + (t2 - t1);
        }

        struct Part p;
        p.type = constructionID;
        p.constructionTime = clock();
        p.id[0] = rand() % 10 + '0';
        p.id[1] = rand() % 10 + '0';
        p.id[2] = rand() % 10 + '0';
        p.id[3] = rand() % 10 + '0';
        p.id[4] = '\0';

        place(&p, pmem_out_1);

        printf("Construction %d has created part: %c%c%c%c%c \n", getpid(), p.id[0], p.id[1], p.id[2], p.id[3], p.type);

        upFull(buffer_out_1);
    }

    downStats(buffer_out_4);
    pmem_out_4->constructionDelay = pmem_out_4->constructionDelay + delay;
    upStats(buffer_out_4);

    printf("Construction has exited %d as %c \n", getpid(), constructionID);

    exit(0);
}

void workPaint(int Y, char *pmem_in_1, char *pmem_out_2a, char *pmem_out_2b, char *pmem_out_2c, int buffer_in_1, int buffer_out_2a, int buffer_out_2b, int buffer_out_2c, int time1, int time2, int time3) {
    int i;

    printf("Paint has started %d \n", getpid());

    for (i = 0; i < 3 * Y; i++) {
        // consume from Q1
        downFull(buffer_in_1);
        struct Part p;
        retrieve(&p, pmem_in_1);
        upEmpty(buffer_in_1);


        if (p.type == 'X') {
            usleep(time1);
        }

        if (p.type == 'Y') {
            usleep(time2);
        }

        if (p.type == 'Z') {
            usleep(time3);
        }

        printf("Painting %d has painted part: %c%c%c%c%c \n", getpid(), p.id[0], p.id[1], p.id[2], p.id[3], p.type);

        // production to Q2a or 

        if (p.type == 'X') {
            // production to 2a
            downEmpty(buffer_out_2a);

            place(&p, pmem_out_2a);

            upFull(buffer_out_2a);
        }

        if (p.type == 'Y') {
            // production to 2b
            downEmpty(buffer_out_2b);

            place(&p, pmem_out_2b);

            upFull(buffer_out_2b);
        }

        if (p.type == 'Z') {
            // production to 2c
            downEmpty(buffer_out_2c);

            place(&p, pmem_out_2c);

            upFull(buffer_out_2c);
        }
    }

    printf("Paint has exited %d \n", getpid());

    exit(0);
}

void workVerify(int Y, char verifyID, char *pmem_in_2, char * pmem_out_3, int buffer_in_2, int buffer_out_3, int time2) {
    int i;

    printf("Verification has started %d as %c \n", getpid(), verifyID);

    for (i = 0; i < Y; i++) {
        // consume
        downFull(buffer_in_2);
        struct Part p;
        retrieve(&p, pmem_in_2);
        upEmpty(buffer_in_2);

        usleep(time2);

        printf("Verify %d has verified part: %c%c%c%c%c \n", getpid(), p.id[0], p.id[1], p.id[2], p.id[3], p.type);

        // produce on Q3
        downEmpty(buffer_out_3);
        place(&p, pmem_out_3);
        upFull(buffer_out_3);
    }

    printf("Verification has exited %d as %c \n", getpid(), verifyID);
    exit(0);
}

void workAssembly(int Y, char *pmem_in_3, int buffer_in_3, int time) {
    int i;

    struct PartList * listX = CreatePartList();
    struct PartList * listY = CreatePartList();
    struct PartList * listZ = CreatePartList();

    double sumtime = 0.0;

    printf("Assembly has started %d \n", getpid());

    for (i = 0; i < 3 * Y; i++) {
        // consume from Q
        downFull(buffer_in_3);
        struct Part p;
        retrieve(&p, pmem_in_3);
        upEmpty(buffer_in_3);

        if (p.type == 'X') {
            insertPartIntoPartList(listX, &p);
        } else if (p.type == 'Y') {
            insertPartIntoPartList(listY, &p);
        } else if (p.type == 'Z') {
            insertPartIntoPartList(listZ, &p);
        } else {
            printf("???????????????????????????????????? %c%c%c%c%c \n", p.id[0], p.id[1], p.id[2], p.id[3], p.id[4]);
        }

        while (getPartListSize(listX) > 0 && getPartListSize(listY) > 0 && getPartListSize(listZ) > 0) {
            struct Part x, y, z;

            removeFromPartList(listX, &x);
            removeFromPartList(listY, &y);
            removeFromPartList(listZ, &z);

            usleep(time);

            double t1x = ((double) x.constructionTime) / CLOCKS_PER_SEC;
            double t1y = ((double) y.constructionTime) / CLOCKS_PER_SEC;
            double t1z = ((double) z.constructionTime) / CLOCKS_PER_SEC;
            double t2 = ((double) clock()) / CLOCKS_PER_SEC;


            double t_oldest = my_min(t1x, t1y);
            t_oldest = my_min(t_oldest, t1z);

            double constructTime = t2 - t_oldest;

            sumtime = sumtime + constructTime;
            
            printf(" ******** Assembly complete: %s%c + %s%c + %s%c \n", x.id, x.type, y.id, y.type, z.id, z.type);
        }
    }
    sumtime = sumtime;

    printf(" ******** Assembly delay time: %lf \n", sumtime);


    DestroyList(listX);
    DestroyList(listY);
    DestroyList(listZ);

    printf("Assembly has exited %d \n", getpid());
    exit(0);
}

int main(int argc, char** argv) {
    int i;
    if (argc != 2) {
        printf("error Y, #Y missing");
        return -1;
    }

    int P = 8;
    int Y = atoi(argv[1]);

    int NB_SIZE_QUEUE = sizeof (struct Slot);
    int NB_SIZE_STATS = sizeof (struct Statistics);

    int SEM_SIZE_QUEUE = 2;
    int SEM_SIZE_STATS = 1;

    // allocate memory
    int shmid_1 = shmget(IPC_PRIVATE, NB_SIZE_QUEUE, 0666 | IPC_CREAT);
    int shmid_2a = shmget(IPC_PRIVATE, NB_SIZE_QUEUE, 0666 | IPC_CREAT);
    int shmid_2b = shmget(IPC_PRIVATE, NB_SIZE_QUEUE, 0666 | IPC_CREAT);
    int shmid_2c = shmget(IPC_PRIVATE, NB_SIZE_QUEUE, 0666 | IPC_CREAT);
    int shmid_3 = shmget(IPC_PRIVATE, NB_SIZE_QUEUE, 0666 | IPC_CREAT);
    int shmid_4 = shmget(IPC_PRIVATE, NB_SIZE_STATS, 0666 | IPC_CREAT);

    if (shmid_1 == -1 || shmid_2a == -1 || shmid_2b == -1 || shmid_2c == -1 || shmid_3 == -1 || shmid_4 == -1) {
        printf("error: could not allocate memory");
        return -1;
    }

    // attach to memory
    char *pmem_1 = shmat(shmid_1, 0, 0);
    char *pmem_2a = shmat(shmid_2a, 0, 0);
    char *pmem_2b = shmat(shmid_2b, 0, 0);
    char *pmem_2c = shmat(shmid_2c, 0, 0);
    char *pmem_3 = shmat(shmid_3, 0, 0);
    struct Statistics *pmem_4 = (struct Statistics*) shmat(shmid_4, 0, 0);

    pmem_4->constructionDelay = 0.0;

    // create semaphores

    int semid_1 = semget(IPC_PRIVATE, SEM_SIZE_QUEUE, IPC_CREAT | 0660);
    int semid_2a = semget(IPC_PRIVATE, SEM_SIZE_QUEUE, IPC_CREAT | 0660);
    int semid_2b = semget(IPC_PRIVATE, SEM_SIZE_QUEUE, IPC_CREAT | 0660);
    int semid_2c = semget(IPC_PRIVATE, SEM_SIZE_QUEUE, IPC_CREAT | 0660);
    int semid_3 = semget(IPC_PRIVATE, SEM_SIZE_QUEUE, IPC_CREAT | 0660);
    int semid_4 = semget(IPC_PRIVATE, SEM_SIZE_STATS, IPC_CREAT | 0660);

    if (semid_1 == -1 || semid_2a == -1 || semid_2b == -1 || semid_2c == -1 || semid_3 == -1 || semid_4 == -1) {
        printf("error: could not create semaphores");
        return -1;
    }

    // initialize semaphores
    union senum arg;
    arg.val = 1;

    // initialize semaphores: empty 
    semctl(semid_1, SEM_EMPTY_POS, SETVAL, arg);
    semctl(semid_2a, SEM_EMPTY_POS, SETVAL, arg);
    semctl(semid_2b, SEM_EMPTY_POS, SETVAL, arg);
    semctl(semid_2c, SEM_EMPTY_POS, SETVAL, arg);
    semctl(semid_3, SEM_EMPTY_POS, SETVAL, arg);

    // stats semaphore
    semctl(semid_4, SEM_STATS, SETVAL, arg);

    // initialize semaphores: full
    arg.val = 0;
    semctl(semid_1, SEM_FULL_POS, SETVAL, arg);
    semctl(semid_2a, SEM_FULL_POS, SETVAL, arg);
    semctl(semid_2b, SEM_FULL_POS, SETVAL, arg);
    semctl(semid_2c, SEM_FULL_POS, SETVAL, arg);
    semctl(semid_3, SEM_FULL_POS, SETVAL, arg);

    // stats semaphores:

    printf("Factory has started %d \n", getpid());

    // -------------- work  -----------------
    for (i = 0; i < P; i++) {
        int childpid = fork();
        if (childpid == 0 && i == 0) {
            workConstruction(Y, 'X', pmem_1, semid_1, pmem_4, semid_4, X_CONSTRUCTION_MIN_T, X_CONSTRUCTION_MAX_T);
        }
        if (childpid == 0 && i == 1) {
            workConstruction(Y, 'Y', pmem_1, semid_1, pmem_4, semid_4, Y_CONSTRUCTION_MIN_T, Y_CONSTRUCTION_MAX_T);
        }
        if (childpid == 0 && i == 2) {
            workConstruction(Y, 'Z', pmem_1, semid_1, pmem_4, semid_4, Z_CONSTRUCTION_MIN_T, Z_CONSTRUCTION_MAX_T);
        }
        if (childpid == 0 && i == 3) {
            workPaint(Y, pmem_1, pmem_2a, pmem_2b, pmem_2c, semid_1, semid_2a, semid_2b, semid_2c, X_PAINT_T, Y_PAINT_T, Z_PAINT_T);
        }
        if (childpid == 0 && i == 4) {
            workVerify(Y, 'X', pmem_2a, pmem_3, semid_2a, semid_3, X_VERIFY_T);
        }
        if (childpid == 0 && i == 5) {
            workVerify(Y, 'Y', pmem_2b, pmem_3, semid_2b, semid_3, Y_VERIFY_T);
        }
        if (childpid == 0 && i == 6) {
            workVerify(Y, 'Z', pmem_2c, pmem_3, semid_2c, semid_3, Z_VERIFY_T);
        }
        if (childpid == 0 && i == 7) {
            workAssembly(Y, pmem_3, semid_3, _ASSEMBLE);
        }
    }

    int status = 0;
    for (i = 0; i < P; i++) {
        wait(&status);
    }

    double delay = pmem_4->constructionDelay / 3;

    printf("Building delay: %.2lf \n", delay);

    // destroy semaphores
    semctl(semid_1, 0, IPC_RMID, 0);
    semctl(semid_2a, 0, IPC_RMID, 0);
    semctl(semid_2b, 0, IPC_RMID, 0);
    semctl(semid_2c, 0, IPC_RMID, 0);
    semctl(semid_3, 0, IPC_RMID, 0);
    semctl(semid_4, 0, IPC_RMID, 0);

    // detach from memory
    shmdt(pmem_1);
    shmdt(pmem_2a);
    shmdt(pmem_2b);
    shmdt(pmem_2c);
    shmdt(pmem_3);
    shmdt(pmem_4);

    // deallocate memory
    shmctl(shmid_1, 0, IPC_RMID);
    shmctl(shmid_2a, 0, IPC_RMID);
    shmctl(shmid_2b, 0, IPC_RMID);
    shmctl(shmid_2c, 0, IPC_RMID);
    shmctl(shmid_3, 0, IPC_RMID);
    shmctl(shmid_4, 0, IPC_RMID);

    printf("Factory has exited %d \n", getpid());

    return 0;
}
