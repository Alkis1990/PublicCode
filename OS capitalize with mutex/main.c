
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

#define MAXLINELENGTH 500
#define SEM_EMPTY_POS   0
#define SEM_FULL_POS    1

union senum {
    int val;
    struct semid_ds * buff;
    unsigned short *array;
};

struct MessageBuf {
    pid_t pid;
    char data[MAXLINELENGTH];
} msgbuf;

void downFull(int semid) {
    struct sembuf semopr;
    semopr.sem_num = SEM_FULL_POS;
    semopr.sem_op = -1;
    semopr.sem_flg = 0;
    semop(semid, &semopr, 1);
}

void downEmpty(int semid) {
    struct sembuf semopr;
    semopr.sem_num = SEM_EMPTY_POS;
    semopr.sem_op = -1;
    semopr.sem_flg = 0;
    semop(semid, &semopr, 1);
}

void upFull(int semid) {
    struct sembuf semopr;
    semopr.sem_num = SEM_FULL_POS;
    semopr.sem_op = +1;
    semopr.sem_flg = 0;
    semop(semid, &semopr, 1);
}

void upEmpty(int semid) {
    struct sembuf semopr;
    semopr.sem_num = SEM_EMPTY_POS;
    semopr.sem_op = +1;
    semopr.sem_flg = 0;
    semop(semid, &semopr, 1);
}

void workP(char *pmem_in, char * pmem_out, int buffer_in, int buffer_out) {
    int pid_match = 0;    
    int dice;
    printf("Producer has started %d \n", getpid());
    FILE * fp = fopen("build_an_h_bomb.txt", "r");
    
    int lines = 0;
    while (fgets(msgbuf.data, sizeof(msgbuf.data), fp) > 0) {
        lines++;
    }
    
    while (1) {       
        rewind(fp);
        dice = rand()%lines;
        
        msgbuf.pid = getpid();
        while (dice > 0) {
            fgets(msgbuf.data, sizeof(msgbuf.data), fp);
            dice--;
        }
        
        // produce to buf in
        downEmpty(buffer_in);
        memcpy(pmem_in, &msgbuf, sizeof (struct MessageBuf));
        upFull(buffer_in);

        // consume from buf out
        downFull(buffer_out);
        memcpy(&msgbuf, pmem_out, sizeof (struct MessageBuf));
        if (msgbuf.pid > 0) {
            printf("Prod pid:%5d  msgpid:5%d   \n%s \n", getpid(), msgbuf.pid, msgbuf.data);
        }
        upEmpty(buffer_out);

        if (msgbuf.pid == 0) {
            break;
        }
        if (msgbuf.pid == getpid()) {
            pid_match++;
        }
    }
    fclose(fp);
    printf("Producer has finished %d (match %d) \n", getpid(), pid_match);
    exit(pid_match);
}

void workC(char *pmem_in, char * pmem_out, int buffer_in, int buffer_out, int K, int P) {
    int i, j;
    for (i = 0; i < K; i++) {
        // consume from buf in
        downFull(buffer_in);
        memcpy(&msgbuf, pmem_in, sizeof (struct MessageBuf));
        upEmpty(buffer_in);
        // capitalize
        for (j = 0; j < strlen(msgbuf.data); j++) {
            msgbuf.data[j] = toupper(msgbuf.data[j]);
        }
        // produce to buf out
        downEmpty(buffer_out);
        memcpy(pmem_out, &msgbuf, sizeof (struct MessageBuf));
        upFull(buffer_out);
    }
    
    while (P > 0) {
        downFull(buffer_in);
        upEmpty(buffer_in);
        // set PID to 0 (finish signal)
        msgbuf.pid = 0;
        msgbuf.data[0] ='\0';
        // produce to buf out
        downEmpty(buffer_out);
        memcpy(pmem_out, &msgbuf, sizeof (struct MessageBuf));
        upFull(buffer_out);

        P--;
    }

}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("error K or #P missing");
        return -1;
    }

    int K = atoi(argv[1]);
    int P = atoi(argv[2]);
    int i;

    int NB = sizeof(struct MessageBuf);

    // allocate memory
    int shmid_in = shmget(8888, NB, 0666 | IPC_CREAT);
    int shmid_out = shmget(9999, NB, 0666 | IPC_CREAT);

    if (shmid_in == -1 || shmid_out == -1) {
        printf("error: could not allocate memory");
        return -1;
    }

    // attach to memory
    char *pmem_in = shmat(shmid_in, 0, 0);
    char *pmem_out = shmat(shmid_out, 0, 0);

    // create semaphores

    int semid_in = semget(7777, 2, IPC_CREAT | 0660);
    int semid_out = semget(6666, 2, IPC_CREAT | 0660);

    if (semid_in == -1 || semid_out == -1) {
        printf("error: could not create semaphores");
        return -1;
    }

    // initialize semaphores
    union senum arg;
    arg.val = 1;
    semctl(semid_in, SEM_EMPTY_POS, SETVAL, arg);
    semctl(semid_out, SEM_EMPTY_POS, SETVAL, arg);

    arg.val = 0;
    semctl(semid_in, SEM_FULL_POS, SETVAL, arg);
    semctl(semid_out, SEM_FULL_POS, SETVAL, arg);

    // -------------- work  -----------------
    for (i = 0; i < P; i++) {
        int childpid = fork();
        if (childpid == 0) {
            workP(pmem_in, pmem_out, semid_in, semid_out);
        }
    }
    printf("Consumer has started %d \n", getpid());
    workC(pmem_in, pmem_out, semid_in, semid_out, K, P);
    printf("Consumer has finished %d \n", getpid());
    // -------------- work  -----------------

    int status = 0;
    int pid_match = 0;
    for (i = 0; i < P; i++) {
        wait(&status);
        
        pid_match = pid_match + WEXITSTATUS(status);        
    }

    printf("\nResults: \n");
    printf("K=%d\n", K);
    printf("P=%d\n", P);
    printf("pid_match=%d\n", pid_match);

    // destroy semaphores
    semctl(semid_in, 0, IPC_RMID, 0);
    semctl(semid_out, 0, IPC_RMID, 0);

    // detach from memory
    shmdt(pmem_in);
    shmdt(pmem_out);

    // deallocate memory
    shmctl(shmid_in, 0, IPC_RMID);
    shmctl(shmid_out, 0, IPC_RMID);

    return 0;
}

