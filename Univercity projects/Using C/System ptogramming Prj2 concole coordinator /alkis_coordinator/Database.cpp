#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include "Database.h"
#include "pipesparams.h"
#include "sys/wait.h"

void Database::make() {
    chain.make();
}

void Database::destroy() {
    Pool * g = chain.pool;
    for (int ipool = 0; ipool < chain.number_of_pools; ipool++) {
        delete [] (g->jobs);

        Pool * t = g;
        g = g->nextPool;
        delete t;
    }
}

void Database::status(char * fields[], int fd) {
    char * searchjobid = fields[0];

    Pool * p = chain.pool;

    for (int ipool = 0; ipool < chain.number_of_pools; ipool++) {
        for (int ijob = 0; ijob < p->number_of_jobs; ijob++) {
            if (strcmp(p->jobs[ijob].jobid, searchjobid) == 0) {
                PipeBuffer buffer1;
                strcpy(buffer1.data, searchjobid);
                write(fd, (void*) &buffer1, sizeof (PipeBuffer));
                PipeBuffer buffer2;
                strcpy(buffer2.data, p->jobs[ijob].jobstatus);
                write(fd, (void*) &buffer2, sizeof (PipeBuffer));
                return;
            }
        }
        p = p->nextPool;
    }

    PipeBuffer buffer1;
    strcpy(buffer1.data, searchjobid);
    write(fd, (void*) &buffer1, sizeof (PipeBuffer));
    PipeBuffer buffer2;
    strcpy(buffer2.data, "job not found");
    write(fd, (void*) &buffer2, sizeof (PipeBuffer));
    return;
}

void Database::status_all(char * fields[], int fd) {
    Pool * p = chain.pool;

    char * searchtd = fields[1];
    int td = 0;

    if (searchtd != NULL) {
        td = atoi(searchtd);
    }

    for (int ipool = 0; ipool < chain.number_of_pools; ipool++) {
        for (int ijob = 0; ijob < p->number_of_jobs; ijob++) {
            if (fields[1] == NULL || space(p->jobs[ijob].created_time, td)) {
                PipeBuffer buffer1;
                strcpy(buffer1.data, p->jobs[ijob].jobid);
                write(fd, (void*) &buffer1, sizeof (PipeBuffer));
                PipeBuffer buffer2;
                strcpy(buffer2.data, p->jobs[ijob].jobstatus);
                write(fd, (void*) &buffer2, sizeof (PipeBuffer));
            }
        }
        p = p->nextPool;
    }

    PipeBuffer buffer1;
    strcpy(buffer1.data, "finish");
    write(fd, (void*) &buffer1, sizeof (PipeBuffer));
    return;
}

void Database::show_active(char * fields[], int fd) {
    char * searchjobid = fields[0];

    Pool * p = chain.pool;

    for (int ipool = 0; ipool < chain.number_of_pools; ipool++) {
        for (int ijob = 0; ijob < p->number_of_jobs; ijob++) {
            if (strcmp(p->jobs[ijob].jobstatus, "active") == 0) {
                PipeBuffer buffer1;
                strcpy(buffer1.data, searchjobid);
                write(fd, (void*) &buffer1, sizeof (PipeBuffer));
                PipeBuffer buffer2;
                strcpy(buffer2.data, p->jobs[ijob].jobstatus);
                write(fd, (void*) &buffer2, sizeof (PipeBuffer));
            }
        }
        p = p->nextPool;
    }

    PipeBuffer buffer1;
    strcpy(buffer1.data, searchjobid);
    write(fd, (void*) &buffer1, sizeof (PipeBuffer));
    PipeBuffer buffer2;
    strcpy(buffer2.data, "job not found");
    write(fd, (void*) &buffer2, sizeof (PipeBuffer));
    return;
}

void Database::show_pools(char * fields[], int fd) {
    char * searchjobid = fields[0];

    Pool * p = chain.pool;

    for (int ipool = 0; ipool < chain.number_of_pools; ipool++) {
        int metriti = 0;
        for (int ijob = 0; ijob < p->number_of_jobs; ijob++) {
            if (strcmp(p->jobs[ijob].jobstatus, "active") == 0) {
                metriti++;
            }
        }

        PipeBuffer buffer1;
        strcpy(buffer1.data, p->poolid);
        write(fd, (void*) &buffer1, sizeof (PipeBuffer));
        PipeBuffer buffer2;
        sprintf(buffer2.data, "%d", metriti);
        write(fd, (void*) &buffer2, sizeof (PipeBuffer));

        p = p->nextPool;
    }

    PipeBuffer buffer1;
    strcpy(buffer1.data, searchjobid);
    write(fd, (void*) &buffer1, sizeof (PipeBuffer));
    PipeBuffer buffer2;
    strcpy(buffer2.data, "job not found");
    write(fd, (void*) &buffer2, sizeof (PipeBuffer));
    return;
}

void Database::show_finished(char * fields[], int fd) {
    char * searchjobid = fields[0];

    Pool * p = chain.pool;

    for (int ipool = 0; ipool < chain.number_of_pools; ipool++) {
        for (int ijob = 0; ijob < p->number_of_jobs; ijob++) {
            if (strcmp(p->jobs[ijob].jobstatus, "finished") == 0) {
                PipeBuffer buffer1;
                strcpy(buffer1.data, searchjobid);
                write(fd, (void*) &buffer1, sizeof (PipeBuffer));
                PipeBuffer buffer2;
                strcpy(buffer2.data, p->jobs[ijob].jobstatus);
                write(fd, (void*) &buffer2, sizeof (PipeBuffer));
            }
        }
        p = p->nextPool;
    }

    PipeBuffer buffer1;
    strcpy(buffer1.data, searchjobid);
    write(fd, (void*) &buffer1, sizeof (PipeBuffer));
    PipeBuffer buffer2;
    strcpy(buffer2.data, "job not found");
    write(fd, (void*) &buffer2, sizeof (PipeBuffer));
    return;
}

bool Database::space(time_t created_time, int td) {
    //    time_t now = time(0);
    // todo:

    // return true if created_time is within td seconds from now, false otherwize

    return false;
}

void Database::suspend(char * fields[]) {
    char * searchjobid = fields[0];
    int skip = atoi(searchjobid) / Pool::POOL_CAPACITY;

    Pool * p = chain.pool;

    for (int ipool = 0; ipool < skip; ipool++) {
        p = p->nextPool;
    }

    if (p->current_state == true) {
        PipeBuffer buffer1;
        sprintf(buffer1.data, "suspend %s", searchjobid);
        write(p->poolid_send, (void*) &buffer1, sizeof (PipeBuffer));
    } else {
        PipeBuffer buffer1;
        sprintf(buffer1.data, "suspend failed: %s", searchjobid);
        write(p->poolid_send, (void*) &buffer1, sizeof (PipeBuffer));
    }
}

void Database::resume(char * fields[]) {
    char * searchjobid = fields[0];
    int skip = atoi(searchjobid) / Pool::POOL_CAPACITY;

    Pool * p = chain.pool;

    for (int ipool = 0; ipool < skip; ipool++) {
        p = p->nextPool;
    }

    if (p->current_state == false) {
        PipeBuffer buffer1;
        sprintf(buffer1.data, "resume %s", searchjobid);
        write(p->poolid_send, (void*) &buffer1, sizeof (PipeBuffer));
    } else {
        PipeBuffer buffer1;
        sprintf(buffer1.data, "resume failed: %s", searchjobid);
        write(p->poolid_send, (void*) &buffer1, sizeof (PipeBuffer));
    }
}

void Database::shutdown() {
    Pool * p = chain.pool;

    for (int ipool = 0; ipool < chain.number_of_pools; ipool++) {
        if (p->current_state == true) {
            kill(p->pid, SIGTERM);
        }
        p = p->nextPool;
    }

    for (int ipool = 0; ipool < chain.number_of_pools; ipool++) {
        wait(NULL);
    }

    int number_of_running_jobs = 0;
    for (int ipool = 0; ipool < chain.number_of_pools; ipool++) {
        for (int ijob = 0; ijob < p->number_of_jobs; ijob++) {
            if (strcmp(p->jobs[ijob].jobstatus, "active") == 0) {
                number_of_running_jobs++;
            }
        }
        p = p->nextPool;
    }


    PipeBuffer buffer1;
    sprintf(buffer1.data, "%d %d", chain.number_of_jobs, number_of_running_jobs);
    write(p->poolid_send, (void*) &buffer1, sizeof (PipeBuffer));
}

// ++++++++++++++++++++++++++++++++++++++++

void Database::suspend_pool(char * fields[]) {
    char * searchjobid = fields[0];
    char * result = fields[0];

    if (strcmp(result, "fail") == 0) {
        return;
    }

    int skip = atoi(searchjobid) / Pool::POOL_CAPACITY;

    Pool * p = chain.pool;

    for (int ipool = 0; ipool < skip; ipool++) {
        p = p->nextPool;
    }

    for (int ijob = 0; ijob < p->number_of_jobs; ijob++) {
        if (strcmp(p->jobs[ijob].jobid, searchjobid) == 0) {
            strcpy(p->jobs[ijob].jobstatus, "inactive");
        }
    }
}