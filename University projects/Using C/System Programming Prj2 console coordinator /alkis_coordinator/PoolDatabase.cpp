#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include "PoolDatabase.h"
#include "pipesparams.h"

void PoolDatabase::make() {
    poolchain.make();
}

void PoolDatabase::destroy() {
    PoolJob * g = poolchain.pooljob;
    for (int ijob = 0; ijob < poolchain.number_of_jobs; ijob++) {
        PoolJob * t = g;
        g = g->nextPoolJob;
        delete t;
    }
}

void PoolDatabase::status(char * fields[], int fd) {
    char * searchjobid = fields[0];

    PoolJob * p = poolchain.pooljob;

    for (int ijob = 0; ijob < poolchain.number_of_jobs; ijob++) {
        //        if (strcmp(p->jobs[ijob].jobid, searchjobid) == 0) {
        //            PipeBuffer buffer1;
        //            strcpy(buffer1.data, searchjobid);
        //            write(fd, (void*) &buffer1, sizeof (PipeBuffer));
        //            PipeBuffer buffer2;
        //            strcpy(buffer2.data, p->jobs[ijob].jobstatus);
        //            write(fd, (void*) &buffer2, sizeof (PipeBuffer));
        //            return;
        //        }
        p = p->nextPoolJob;
    }

    PipeBuffer buffer1;
    strcpy(buffer1.data, searchjobid);
    write(fd, (void*) &buffer1, sizeof (PipeBuffer));
    PipeBuffer buffer2;
    strcpy(buffer2.data, "job not found");
    write(fd, (void*) &buffer2, sizeof (PipeBuffer));
    return;
}

void PoolDatabase::suspend(char * fields[], int fd) {
    char * searchjobid = fields[0];

    PoolJob * p = poolchain.pooljob;

    for (int ijob = 0; ijob < poolchain.number_of_jobs; ijob++) {
        if (strcmp(p->jobstatus, "active") == 0) {
            kill(p->pid, SIGSTOP);
            strcpy(p->jobstatus, "inactive");
            PipeBuffer buffer1;
            sprintf(buffer1.data, "suspend %s success", searchjobid);
            write(fd, (void*) &buffer1, sizeof (PipeBuffer));
        } else if (strcmp(p->jobstatus, "inactive") == 0) {
            PipeBuffer buffer1;
            sprintf(buffer1.data, "suspend %s fail 1", searchjobid);
            write(fd, (void*) &buffer1, sizeof (PipeBuffer));
        } else if (strcmp(p->jobstatus, "terminated") == 0) {
            PipeBuffer buffer1;
            sprintf(buffer1.data, "suspend %s fail 2", searchjobid);
            write(fd, (void*) &buffer1, sizeof (PipeBuffer));
        }

        p = p->nextPoolJob;
    }
}

void PoolDatabase::resume(char * fields[], int fd) {
    char * searchjobid = fields[0];

//    PoolJob * p = poolchain.pooljob;
//
//    for (int ijob = 0; ijob < poolchain.number_of_jobs; ijob++) {
//        if (strcmp(p->jobstatus, "inactive") == 0) {
//            kill(p->pid, SIGONT);
//            strcpy(p->jobstatus, "active");
//            PipeBuffer buffer1;
//            sprintf(buffer1.data, "resume %s success", searchjobid);
//            write(fd, (void*) &buffer1, sizeof (PipeBuffer));
//        } else if (strcmp(p->jobstatus, "active") == 0) {
//            PipeBuffer buffer1;
//            sprintf(buffer1.data, "resume %s fail 1", searchjobid);
//            write(fd, (void*) &buffer1, sizeof (PipeBuffer));
//        } else if (strcmp(p->jobstatus, "terminated") == 0) {
//            PipeBuffer buffer1;
//            sprintf(buffer1.data, "resume %s fail 2", searchjobid);
//            write(fd, (void*) &buffer1, sizeof (PipeBuffer));
//        }
//
//        p = p->nextPoolJob;
//    }
}