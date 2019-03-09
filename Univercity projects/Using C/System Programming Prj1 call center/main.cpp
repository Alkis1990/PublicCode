
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include "readparams.h"
#include "World.h"

using namespace std;


// ./w  [-o input.txt] -h1 10 -h2 10 -s 100

int main(int argc, char** argv) {
    int number_of_chains1 = -1;
    int number_of_chains2 = -1;
    int groupbytes = -1;
    const char * command_file = 0;

    bool read_from_keyboard = true;

    switch (argc) {
        case 7: // ./w -h1 10 -h2 10 -s 100
            if (strcmp(argv[1], "-h1") == 0) {
                number_of_chains1 = atoi(argv[2]);
            }
            if (strcmp(argv[1], "-h2") == 0) {
                number_of_chains2 = atoi(argv[2]);
            }
            if (strcmp(argv[1], "-s") == 0) {
                groupbytes = atoi(argv[2]);
            }

            if (strcmp(argv[3], "-h1") == 0) {
                number_of_chains1 = atoi(argv[4]);
            }
            if (strcmp(argv[3], "-h2") == 0) {
                number_of_chains2 = atoi(argv[4]);
            }
            if (strcmp(argv[3], "-s") == 0) {
                groupbytes = atoi(argv[4]);
            }

            if (strcmp(argv[5], "-h1") == 0) {
                number_of_chains1 = atoi(argv[6]);
            }
            if (strcmp(argv[5], "-h2") == 0) {
                number_of_chains2 = atoi(argv[6]);
            }
            if (strcmp(argv[5], "-s") == 0) {
                groupbytes = atoi(argv[6]);
            }
            if (number_of_chains1 == -1 || number_of_chains2 == -1 || groupbytes == -1) {
                printf("Missing argument from argc/argv \n");
                return 0;
            }
            break;
        case 9:
            if (strcmp(argv[1], "-h1") == 0) {
                number_of_chains1 = atoi(argv[2]);
            }
            if (strcmp(argv[1], "-h2") == 0) {
                number_of_chains2 = atoi(argv[2]);
            }
            if (strcmp(argv[1], "-s") == 0) {
                groupbytes = atoi(argv[2]);
            }
            if (strcmp(argv[1], "-o") == 0) {
                command_file = argv[2];
            }

            if (strcmp(argv[3], "-h1") == 0) {
                number_of_chains1 = atoi(argv[4]);
            }
            if (strcmp(argv[3], "-h2") == 0) {
                number_of_chains2 = atoi(argv[4]);
            }
            if (strcmp(argv[3], "-s") == 0) {
                groupbytes = atoi(argv[4]);
            }
            if (strcmp(argv[3], "-o") == 0) {
                command_file = argv[4];
            }

            if (strcmp(argv[5], "-h1") == 0) {
                number_of_chains1 = atoi(argv[6]);
            }
            if (strcmp(argv[5], "-h2") == 0) {
                number_of_chains2 = atoi(argv[6]);
            }
            if (strcmp(argv[5], "-s") == 0) {
                groupbytes = atoi(argv[6]);
            }
            if (strcmp(argv[5], "-o") == 0) {
                command_file = argv[6];
            }

            if (strcmp(argv[7], "-h1") == 0) {
                number_of_chains1 = atoi(argv[8]);
            }
            if (strcmp(argv[7], "-h2") == 0) {
                number_of_chains2 = atoi(argv[8]);
            }
            if (strcmp(argv[7], "-s") == 0) {
                groupbytes = atoi(argv[8]);
            }
            if (strcmp(argv[7], "-o") == 0) {
                command_file = argv[8];
            }

            if (number_of_chains1 == -1 || number_of_chains2 == -1 || groupbytes == -1 || command_file == 0) {
                printf("Missing argument from argc/argv \n");
                return 0;
            }
            break;
        default:
            printf("Error with argc/argv \n");
            return 0;
    }

    cout << "Number of chains for 1st database : " << number_of_chains1 << endl;
    cout << "Number of chains for 2nd database : " << number_of_chains2 << endl;
    cout << "Group bytes for both databases    : " << groupbytes << endl;
    cout << "Command file                      : " << command_file << endl;

    FILE * fp = NULL;

    if (command_file != NULL) {
        read_from_keyboard = false;
        fp = fopen(command_file, "r");
        if (fp == NULL) {
            read_from_keyboard = true;
        }
    }

    LineBuffer buffer;
    LineBuffer buffer2;
    World world;

    world.make(number_of_chains1, number_of_chains2, groupbytes);

    while (1) {
        if (read_from_keyboard == true) {
            cout << " ? ";
        }
        if (fgets(buffer.data, sizeof (buffer.data), fp) <= 0) {
            if (read_from_keyboard == true) {
                break;
            } else if (read_from_keyboard == false) {
                fp = stdin;
                read_from_keyboard = true;
                continue;
//                break;
            }
        }

        // insert BD0D7075BC;053-2041182470;030-4595559805;09112016;04:25;2;0;0;200                        
        if (strncmp(buffer.data, "insert", 6) == 0) { // insert                                
            char * p = buffer.data;
            Entry e;
            p += 7;

            for (int i = 0; i < FIELDS; i++) {
                int j = 0;

                while (*p != ';' && *p != '\n') {
                    buffer2.data[j] = *p;
                    p++;
                    j++;
                }
                buffer2.data[j] = '\0';
                p++;

                e.fields[i] = new char[j + 1];
                strcpy(e.fields[i], buffer2.data);
            }

            cout << "INSERT: " << endl;
            for (int i = 0; i < FIELDS; i++) {
                cout << "\t" << i << " " << e.fields[i];
            }
            cout << endl;

            world.ins(e.fields);
        }
        if (strncmp(buffer.data, "delete", 6) == 0) { // insert
            char * p = buffer.data;
            p += 7;

            char * fields[2] = {NULL};

            for (int i = 0; i < 2; i++) {
                int j = 0;

                while (*p != ' ' && *p != '\n') {
                    buffer2.data[j] = *p;
                    p++;
                    j++;
                }
                buffer2.data[j] = '\0';
                p++;

                fields[i] = new char[j + 1];
                strcpy(fields[i], buffer2.data);
            }

            cout << "delete: " << endl;
            for (int i = 0; i < 2; i++) {
                if (fields[i] != NULL) {
                    cout << "\t" << i << " " << fields[i] << endl;
                } else {
                    cout << "\t" << i << " " << "NULL" << endl;
                }
            }

            world.del(fields);
        }

        // find caller 030-4595559805
        if (strncmp(buffer.data, "find", 4) == 0) { // insert
            char * p = buffer.data;
            p += 5;

            int i = 0;

            char * fields[5] = {NULL, NULL, NULL, NULL, NULL};

            while (*p != '\n') {
                int j = 0;

                while (*p != ' ' && *p != '\n') {
                    buffer2.data[j] = *p;
                    p++;
                    j++;
                }
                buffer2.data[j] = '\0';

                fields[i] = new char[j + 1];
                strcpy(fields[i], buffer2.data);
                i++;

                if (*p != '\n') {
                    p++;
                }
            }

            cout << "FIND: " << endl;
            for (int i = 0; i < 5; i++) {
                if (fields[i] != NULL) {
                    cout << "\t" << i << " " << fields[i] << endl;
                } else {
                    cout << "\t" << i << " " << "NULL" << endl;
                }
            }
            world.find(fields);
        }
        if (strncmp(buffer.data, "lookup", 6) == 0) { // insert
            char * p = buffer.data;
            p += 7;

            int i = 0;

            char * fields[5] = {NULL, NULL, NULL, NULL, NULL};

            while (*p != '\n') {
                int j = 0;

                while (*p != ' ' && *p != '\n') {
                    buffer2.data[j] = *p;
                    p++;
                    j++;
                }
                buffer2.data[j] = '\0';

                fields[i] = new char[j + 1];
                strcpy(fields[i], buffer2.data);
                i++;

                if (*p != '\n') {
                    p++;
                }
            }

            cout << "LOOKUP: " << endl;
            for (int i = 0; i < 5; i++) {
                if (fields[i] != NULL) {
                    cout << "\t" << i << " " << fields[i] << endl;
                } else {
                    cout << "\t" << i << " " << "NULL" << endl;
                }
            }

            world.lookup(fields);
        }
        if (strncmp(buffer.data, "indist", 7) == 0) { // insert
            char * p = buffer.data;
            p += 8;

            char * fields[2] = {NULL};

            for (int i = 0; i < 2; i++) {
                int j = 0;

                while (*p != ' ' && *p != '\n') {
                    buffer2.data[j] = *p;
                    p++;
                    j++;
                }
                buffer2.data[j] = '\0';
                p++;

                fields[i] = new char[j + 1];
                strcpy(fields[i], buffer2.data);
            }

            cout << "delete: " << endl;
            for (int i = 0; i < 2; i++) {
                if (fields[i] != NULL) {
                    cout << "\t" << i << " " << fields[i] << endl;
                } else {
                    cout << "\t" << i << " " << "NULL" << endl;
                }
            }

            world.indist(fields);
        }
        if (strncmp(buffer.data, "topdest", 7) == 0) { // insert
            char * p = buffer.data;
            p += 8;

            char * fields[1] = {NULL};

            for (int i = 0; i < 1; i++) {
                int j = 0;

                while (*p != ' ' && *p != '\n') {
                    buffer2.data[j] = *p;
                    p++;
                    j++;
                }
                buffer2.data[j] = '\0';
                p++;

                fields[i] = new char[j + 1];
                strcpy(fields[i], buffer2.data);
            }

            cout << "TOPDEST: " << endl;
            for (int i = 0; i < 1; i++) {
                if (fields[i] != NULL) {
                    cout << "\t" << i << " " << fields[i] << endl;
                } else {
                    cout << "\t" << i << " " << "NULL" << endl;
                }
            }
            world.topdest(fields);
        } else if (strncmp(buffer.data, "top", 3) == 0) { // insert
            char * p = buffer.data;
            p += 4;

            char * fields[1] = {NULL};

            for (int i = 0; i < 1; i++) {
                int j = 0;

                while (*p != ' ' && *p != '\n') {
                    buffer2.data[j] = *p;
                    p++;
                    j++;
                }
                buffer2.data[j] = '\0';
                p++;

                fields[i] = new char[j + 1];
                strcpy(fields[i], buffer2.data);
            }

            cout << "TOP: " << endl;
            for (int i = 0; i < 1; i++) {
                if (fields[i] != NULL) {
                    cout << "\t" << i << " " << fields[i] << endl;
                } else {
                    cout << "\t" << i << " " << "NULL" << endl;
                }
            }
            world.top(fields);
        }
        if (strncmp(buffer.data, "bye", 3) == 0) { // insert                
            world.bye();
            world.remake();
        }
        if (strncmp(buffer.data, "print", 5) == 0) { // insert
            char * p = buffer.data;
            p += 6;

            char * fields[1] = {NULL};

            for (int i = 0; i < 1; i++) {
                int j = 0;

                while (*p != ' ' && *p != '\n') {
                    buffer2.data[j] = *p;
                    p++;
                    j++;
                }
                buffer2.data[j] = '\0';
                p++;

                fields[i] = new char[j + 1];
                strcpy(fields[i], buffer2.data);
            }

            cout << "PRINT: " << endl;
            for (int i = 0; i < 1; i++) {
                if (fields[i] != NULL) {
                    cout << "\t" << i << " " << fields[i] << endl;
                } else {
                    cout << "\t" << i << " " << "NULL" << endl;
                }
            }
            world.print(fields);
        }
        if (strncmp(buffer.data, "dump", 4) == 0) { // insert
            char * p = buffer.data;
            p += 5;

            char * fields[2] = {NULL};

            for (int i = 0; i < 2; i++) {
                int j = 0;

                while (*p != ' ' && *p != '\n') {
                    buffer2.data[j] = *p;
                    p++;
                    j++;
                }
                buffer2.data[j] = '\0';
                p++;

                fields[i] = new char[j + 1];
                strcpy(fields[i], buffer2.data);
            }

            cout << "DUMP: " << endl;
            for (int i = 0; i < 2; i++) {
                if (fields[i] != NULL) {
                    cout << "\t" << i << " " << fields[i] << endl;
                } else {
                    cout << "\t" << i << " " << "NULL" << endl;
                }
            }
            world.dump(fields);
        }
        if (strncmp(buffer.data, "shutdown", 8) == 0) { // insert
            break;

        }
    }

    if (fp != NULL) {
        fclose(fp);
    }

    world.destroy();

    return 0;
}

