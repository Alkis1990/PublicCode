
#include "World.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "Database.h"

using namespace std;

void World::make(int number_of_chains1, int number_of_chains2, int groupbytes) {
    this->number_of_chains1 = number_of_chains1;
    this->number_of_chains2 = number_of_chains2;

    Group::GROUP_CAPACITY = groupbytes / sizeof (Person);

    if (Group::GROUP_CAPACITY == 0) {
        cout << "GROUP CAPACITY = 0 error " << endl;
        exit(0);
    } else {
        cout << "GROUP CAPACITY = " << Group::GROUP_CAPACITY << endl;
    }

    database1.make(number_of_chains1, ENT_CALLER);
    database2.make(number_of_chains2, ENT_RECEIVER);
    //    tree.make()
}

void World::destroy() {
    database1.destroy();
    database2.destroy();
    //    tree.destroy();
}

void World::ins(char * fields[]) {
    database1.ins(fields);
    database2.ins(fields);
    // tree,ins(fields);
    for (int i=0;i<FIELDS;i++) {
        delete [] fields[i];
    }
}

void World::del(char * fields[]) {
    database1.del(fields);
}

void World::find(char * fields[]) {
    database1.find(fields);
}

void World::lookup(char * fields[]) {
    database2.find(fields);
}

void World::indist(char * fields[]) {

}

void World::topdest(char * fields[]) {
    database1.topdest(fields);
}

void World::top(char * fields[]) {

}

void World::print(char * fields[]) {
    if (strcmp(fields[0], "hashtable1") == 0) {
        cout << "---------------------------------------" << endl;
        cout << "            Print hashtable 1 " << endl;
        cout << "---------------------------------------" << endl;
        database1.print();
    } else if (strcmp(fields[0], "hashtable2") == 0) {
        cout << "---------------------------------------" << endl;
        cout << "            Print hashtable 2 " << endl;
        cout << "---------------------------------------" << endl;
        database2.print();
    } else {
        cout << "Print failed." << endl;
    }
}

void World::dump(char * fields[]) {
    if (strcmp(fields[0], "hashtable1") == 0) {
        database1.dump(fields);
    } else if (strcmp(fields[0], "hashtable2") == 0) {
        database2.dump(fields);
    } else {
        cout << "Print failed." << endl;
    }
}

void World::bye() {
    destroy();
    remake();
}

void World::remake() {
    cout << "GROUP CAPACITY = " << Group::GROUP_CAPACITY << endl;

    database1.make(number_of_chains1, ENT_CALLER);
    database2.make(number_of_chains2, ENT_RECEIVER);
}