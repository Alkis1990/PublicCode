
#include "PoolWorld.h"
#include "Pool.h"
#include "pipesparams.h"
#include "main_pool.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

void PoolWorld::make(int pipeid_snd, int pipeid_rcv, int firstJobIDinThisPool, const char * directory) {
    this->pipeid_snd = pipeid_snd;
    this->pipeid_rcv = pipeid_rcv;
    this->firstJobIDinThisPool = firstJobIDinThisPool;
    this->directory = directory;

    pooldatabase.make();
}

void PoolWorld::destroy() {
    pooldatabase.destroy();
}

bool PoolWorld::process_coordinator_message() {
    PipeBuffer incomingBuffer;
    PipeBuffer buffer;
    printf("Pool %d : process_coordinator_message() \n", getpid() );
    
    if (read(pipeid_snd, (void*) &incomingBuffer, sizeof (PipeBuffer)) <0 ) {
        perror("pool read:");
        exit(0);
    };

    if (strncmp(incomingBuffer.data, "submit", 6) == 0) { // insert                                
        char * p = incomingBuffer.data;
        p += 7;

        char * fields[1] = {NULL};

        for (int i = 0; i < 1; i++) {
            int j = 0;

            while (*p != '\0') {
                buffer.data[j] = *p;
                p++;
                j++;
            }
            buffer.data[j] = '\0';
            p++;

            fields[i] = new char[j + 1];
            strcpy(fields[i], buffer.data);
        }

        cout << "POOL SUBMIT: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        submit(fields);
    }

    if (strncmp(incomingBuffer.data, "suspend", 7) == 0) { // insert                                
        char * p = incomingBuffer.data;
        p += 8;

        char * fields[1] = {NULL};

        for (int i = 0; i < 1; i++) {
            int j = 0;

            while (*p != ' ' && *p != '\n' && *p != '\0') {
                buffer.data[j] = *p;
                p++;
                j++;
            }
            buffer.data[j] = '\0';
            p++;

            fields[i] = new char[j + 1];
            strcpy(fields[i], buffer.data);
        }

        cout << "POOL SUSPEND: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        suspend(fields, pipeid_rcv);
    }


    if (strncmp(incomingBuffer.data, "resume", 6) == 0) { // insert                                
        char * p = incomingBuffer.data;
        p += 7;

        char * fields[1] = {NULL};

        for (int i = 0; i < 1; i++) {
            int j = 0;

            while (*p != ' ' && *p != '\n' && *p != '\0') {
                buffer.data[j] = *p;
                p++;
                j++;
            }
            buffer.data[j] = '\0';
            p++;

            fields[i] = new char[j + 1];
            strcpy(fields[i], buffer.data);
        }

        cout << "POOL RESUME: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        resume(fields, pipeid_rcv);
    }

    if (strncmp(buffer.data, "shutdown", 8) == 0) { // insert                                
        char * p = incomingBuffer.data;
        p += 9;

        char * fields[1] = {NULL};

        for (int i = 0; i < 1; i++) {
            int j = 0;

            while (*p != ' ' && *p != '\n' && *p != '\0') {
                buffer.data[j] = *p;
                p++;
                j++;
            }
            buffer.data[j] = '\0';
            p++;

            fields[i] = new char[j + 1];
            strcpy(fields[i], buffer.data);
        }

        cout << "POOL SHUTDOWN: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        shutdown(fields, pipeid_rcv);
        return true;
    }

    return false;
}

void PoolWorld::submit(char * fields[]) {
    int jobid = firstJobIDinThisPool + pooldatabase.poolchain.number_of_jobs;
    char outpath[1000];
    char outputpath1[1000];
    char outputpath2[1000];
    char temp[10];

    mkdir(directory, 0755);

    if (pooldatabase.poolchain.pooljob == NULL) {
        pooldatabase.poolchain.pooljob = new PoolJob();
        pooldatabase.poolchain.lastPooljob = pooldatabase.poolchain.pooljob;
    } else {
        pooldatabase.poolchain.lastPooljob->nextPoolJob = new PoolJob();
        pooldatabase.poolchain.lastPooljob = pooldatabase.poolchain.lastPooljob->nextPoolJob;
    }
    pooldatabase.poolchain.number_of_jobs++;

    if ((pooldatabase.poolchain.lastPooljob->pid = fork()) > 0) { // POOL
        pooldatabase.poolchain.lastPooljob->created_time = time(0);
        sprintf(pooldatabase.poolchain.lastPooljob->jobid, "%d", jobid);
        sprintf(pooldatabase.poolchain.lastPooljob->jobstatus, "%s", "active");

        PipeBuffer buffer3;
        PipeBuffer buffer4;
        strcpy(buffer3.data, "submit");
        sprintf(buffer4.data,"%s %d", pooldatabase.poolchain.lastPooljob->jobid, pooldatabase.poolchain.lastPooljob->pid);
        
        printf("Sending to coord submit result:  %s %s \n", bufferdata(&buffer3), bufferdata(&buffer4));
        write(pipeid_rcv, (void*) &buffer3, sizeof (PipeBuffer));
        write(pipeid_rcv, (void*) &buffer4, sizeof (PipeBuffer));
    } else { // JOB
        strcpy(outpath, directory);
        strcat(outpath, "/std0900000072_");
        sprintf(temp, "%d", jobid);

        strcat(outpath, temp);
        strcat(outpath, "_");

        sprintf(temp, "%d", getpid());
        strcat(outpath, temp);
        strcat(outpath, "_");

        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, sizeof (buffer), "%d-%m-%Y %I:%M:%S", timeinfo);

        strcat(outpath, buffer);

        mkdir(outpath, 0755);

        strcpy(outputpath1, outpath);
        strcat(outputpath1, "/stdout");

        strcpy(outputpath2, outpath);
        strcat(outputpath2, "/stderr");

        int t1 = open(outputpath1, O_CREAT | O_TRUNC | O_WRONLY,0666);
        int t2 = open(outputpath2, O_CREAT | O_TRUNC | O_WRONLY,0666);

          
        for (int i=0;i<5;i++) {
            printf("fields[%d] %s \n", i, fields[i]);
        }
        
        dup2(t1, 1);
        dup2(t2, 2);
      
        
        execlp("/bin/bash", "/bin/bash", "-c", fields[0], NULL);
        exit(0);
    }
}

void PoolWorld::suspend(char * fields[], int fd) {
    pooldatabase.suspend(fields, fd);
}

void PoolWorld::resume(char * fields[], int fd) {
    pooldatabase.resume(fields, fd);
}

void PoolWorld::shutdown(char * fields[], int fd) {
    exit(0);
}
