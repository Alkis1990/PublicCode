
#include "World.h"
#include "Pool.h"
#include "pipesparams.h"
#include "main_pool.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

#include <sys/select.h>
#include <unistd.h>

using namespace std;

void World::make(int pipeid_snd, int pipeid_rcv, char * directory) {
    this->console_pipeid_snd = pipeid_snd;
    this->console_pipeid_rcv = pipeid_rcv;
    this->directory = directory;

    database.make();
}

void World::destroy() {
    database.destroy();
}

bool World::select_wait() {
    int max_fd = 0;
    fd_set input;

    /* Initialize the input set */
    FD_ZERO(&input);

    printf("select_wait()\n");

    Pool * pool = database.chain.pool;
    for (int ipool = 0; ipool < database.chain.number_of_pools; ipool++) {
        if (pool->current_state == true) {
            int socket = pool->poolid_rcv;
            FD_SET(socket, &input);
            if (socket > max_fd) {
                max_fd = socket;
            }
        }
        pool = pool->nextPool;
    }

    FD_SET(console_pipeid_rcv, &input);

    if (console_pipeid_rcv > max_fd) {
        max_fd = console_pipeid_rcv;
    }

    max_fd++;

    int n = select(max_fd, &input, NULL, NULL, NULL);

    if (n < 0) {
        perror("select failed");
        exit(0);
    } else if (n == 0) {
        puts("TIMEOUT");
    } else {
        /* We have input */

        // check if we have input from pools
        Pool * pool = database.chain.pool;
        for (int ipool = 0; ipool < database.chain.number_of_pools; ipool++) {
            if (pool->current_state == true) {
                int socket = pool->poolid_rcv;
                if (FD_ISSET(socket, &input)) {
                    process_pool_message(socket);
                }
            }
            pool = pool->nextPool;
        }

        // check if we have input from console
        if (FD_ISSET(console_pipeid_rcv, &input)) { // data from console
            if (process_console_message()) {
                return true;
            }
        }
    }
    return false;

}

bool World::process_console_message() {
    PipeBuffer incomingbuffer;
    PipeBuffer buffer;
    read(console_pipeid_rcv, (void*) &incomingbuffer, sizeof (PipeBuffer));

    if (strncmp(incomingbuffer.data, "submit", 6) == 0) { // insert                                
        printf("o coordinator elave submit me buffer: %s \n", bufferdata(&incomingbuffer));
        char * p = incomingbuffer.data;
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

        cout << "SUBMIT: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        int pipesnd = submit(fields);
        write(pipesnd, (void*) &incomingbuffer, sizeof (PipeBuffer));
    }

    if (strncmp(buffer.data, "status-all", 10) == 0) {
        printf("o coordinator elave status-all me buffer: %s \n", bufferdata(&incomingbuffer)); // insert                                
        char * p = incomingbuffer.data;
        p += 11;

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

        cout << "STATUS-ALL: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        database.status_all(fields, console_pipeid_snd);
    } else if (strncmp(incomingbuffer.data, "status", 6) == 0) {
        printf("o coordinator elave status me buffer: %s \n", bufferdata(&incomingbuffer));
        char * p = incomingbuffer.data;
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

        cout << "STATUS: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }

        database.status(fields, console_pipeid_snd);
    }


    if (strncmp(buffer.data, "show-active", 11) == 0) {
        printf("o coordinator elave show-all me buffer: %s \n", bufferdata(&incomingbuffer)); // insert                                
        char * p = incomingbuffer.data;
        p += 12;

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

        cout << "SHOW-ACTIVE: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        database.show_active(fields, console_pipeid_snd);
    }


    if (strncmp(buffer.data, "show-pools", 10) == 0) {
        printf("o coordinator elave show-pools me buffer: %s \n", bufferdata(&incomingbuffer)); // insert                                
        char * p = incomingbuffer.data;
        p += 11;

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

        cout << "SHOW-POOLS: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        database.show_pools(fields, console_pipeid_snd);
    }

    if (strncmp(buffer.data, "show-finished", 13) == 0) {
        printf("o coordinator elave show-finished me buffer: %s \n", bufferdata(&incomingbuffer)); // insert                                
        char * p = incomingbuffer.data;
        p += 14;

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

        cout << "SHOW-FINISHED: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        database.show_finished(fields, console_pipeid_snd);
    }


    if (strncmp(buffer.data, "suspend", 7) == 0) {
        printf("o coordinator elave suspend me buffer: %s \n", bufferdata(&incomingbuffer)); // insert                                
        char * p = incomingbuffer.data;
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

        cout << "SUSPEND: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        database.suspend(fields);
    }


    if (strncmp(buffer.data, "resume", 6) == 0) {
        printf("o coordinator elave resume me buffer: %s \n", bufferdata(&incomingbuffer)); // insert                                
        char * p = incomingbuffer.data;
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

        cout << "RESUME: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        //        database.resume(fields);
    }



    if (strncmp(buffer.data, "shutdown", 8) == 0) {
        printf("o coordinator elave shutdown me buffer: %s \n", bufferdata(&incomingbuffer)); // insert                                
        char * p = incomingbuffer.data;
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

        cout << "SHUTDOWN: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        //        database.shutdown(fields);
        return true;
    }

    return false;
}

void World::process_pool_message(int fd) {
    PipeBuffer incomingbuffer;
    PipeBuffer buffer;

    if (read(fd, (void*) &incomingbuffer, sizeof (PipeBuffer)) < 0) {
        perror("read");
        exit(0);
    };

    if (strncmp(incomingbuffer.data, "submit", 6) == 0) {
        if (read(fd, (void*) &incomingbuffer, sizeof (PipeBuffer)) < 0) {
            perror("read");
            exit(0);
        };

        printf("o coordinator elave submit apo pool me buffer: %s \n", bufferdata(&incomingbuffer)); // insert                                
        char * p = incomingbuffer.data;

        char * fields[2] = {NULL};

        for (int i = 0; i < 2; i++) {
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

        cout << "COORD RECEIVED FROM POOL : SUBMIT: " << endl;
        for (int i = 0; i < 2; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }

        submitfrompool(fields);
    }

    if (strncmp(incomingbuffer.data, "suspend", 7) == 0) {
        printf("o coordinator elave submit apo pool me buffer: %s \n", bufferdata(&incomingbuffer));
        char * p = incomingbuffer.data;
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

        cout << "COORD RECEIVED FROM POOL : SUSPEND: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        database.suspend_pool(fields);
        write(console_pipeid_snd, (void*) &buffer, sizeof (PipeBuffer));
    }


    if (strncmp(incomingbuffer.data, "resume", 6) == 0) {
        printf("o coordinator elave resume apo pool me buffer: %s \n", bufferdata(&incomingbuffer)); // insert        
        // insert                                
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

        cout << "COORD RECEIVED FROM POOL : RESUME: " << endl;
        for (int i = 0; i < 1; i++) {
            if (fields[i] != NULL) {
                cout << "\t" << i << " " << fields[i] << endl;
            } else {
                cout << "\t" << i << " " << "NULL" << endl;
            }
        }
        database.resume(fields);
    }



    if (strncmp(incomingbuffer.data, "shutdown", 8) == 0) {
        printf("o coordinator elave shutdown apo pool me buffer: %s \n", bufferdata(&incomingbuffer)); // insert        
        // insert                                
        //        char * p = buffer.data;
        //        p += 9;
        //
        //        char * fields[1] = {NULL};
        //
        //        for (int i = 0; i < 1; i++) {
        //            int j = 0;
        //
        //            while (*p != ' ' && *p != '\n' && *p != '\0') {
        //                buffer.data[j] = *p;
        //                p++;
        //                j++;
        //            }
        //            buffer.data[j] = '\0';
        //            p++;
        //
        //            fields[i] = new char[j + 1];
        //            strcpy(fields[i], buffer.data);
        //        }
        //
        //        cout << "COORD RECEIVED FROM POOL : SHUTDOWN: " << endl;
        //        for (int i = 0; i < 1; i++) {
        //            if (fields[i] != NULL) {
        //                cout << "\t" << i << " " << fields[i] << endl;
        //            } else {
        //                cout << "\t" << i << " " << "NULL" << endl;
        //            }
        //        }
    }
}

// creates a new pool if needed to the database
// adds the new job to the database
// returns the outgoing descriptor (snd) of that pool

int World::submit(char * fields[]) {
    bool need_for_new_pool = (database.chain.number_of_jobs % Pool::POOL_CAPACITY == 0);

    printf("O coordinator ektelei submit,  need_for_new_pool = %d \n", need_for_new_pool);
    // ---------------------- create pool ----------------------
    if (need_for_new_pool == true) {
        if (database.chain.pool == NULL) {
            database.chain.pool = new Pool(database.chain.number_of_pools);
            database.chain.lastPool = database.chain.pool;
            database.chain.pool->makepipes();
        } else {
            database.chain.lastPool->nextPool = new Pool(database.chain.number_of_pools);
            database.chain.lastPool = database.chain.lastPool->nextPool;
            database.chain.lastPool->makepipes();
        }
        database.chain.number_of_pools++;

        database.chain.lastPool->pid = fork();

        if (database.chain.lastPool->pid == 0) { // pool
            char buffersnd[1000];
            char bufferrcv[1000];
            sprintf(buffersnd, "snd%s", database.chain.lastPool->poolid);
            sprintf(bufferrcv, "rcv%s", database.chain.lastPool->poolid);

            main_pool(database.chain.number_of_jobs, directory, buffersnd, bufferrcv);
        } else { // coordinator
            database.chain.lastPool->openpipes();
        }
    }

    // -----------------------  add job  ---------------------------
    int position_in_pool = database.chain.number_of_jobs % Pool::POOL_CAPACITY;
    database.chain.lastPool->jobs[position_in_pool].created_time = time(0);
    sprintf(database.chain.lastPool->jobs[position_in_pool].jobid, "%d", database.chain.number_of_jobs);
    strcpy(database.chain.lastPool->jobs[position_in_pool].jobstatus, "active");

    database.chain.number_of_jobs++;
    database.chain.lastPool->number_of_jobs++;

    return database.chain.lastPool->poolid_send;
}

void World::submitfrompool(char * fields[]) {
    PipeBuffer buffer3;
    PipeBuffer buffer4;
    sprintf(buffer3.data, "%s", fields[0]);
    sprintf(buffer4.data, "%s", fields[1]);
    write(console_pipeid_snd, (void*) &buffer3, sizeof (PipeBuffer));
    write(console_pipeid_snd, (void*) &buffer4, sizeof (PipeBuffer));
}