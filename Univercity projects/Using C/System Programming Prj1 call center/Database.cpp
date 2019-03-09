#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Database.h"

void Database::make(int number_of_chains, int KEY) {
    this->number_of_chains = number_of_chains;
    this->KEY = KEY;

    chains = new Chain[number_of_chains];

    for (int i = 0; i < number_of_chains; i++) {
        chains[i].make();
    }
}

void Database::destroy() {
    for (int ich = 0; ich < number_of_chains; ich++) {
        Group * g = chains[ich].group;
        for (int igrp = 0; igrp < chains[ich].number_of_groups; igrp++) {
            for (int ippl = 0; ippl < g->number_of_people; ippl++) {
                Catalog * c = g->people[ippl].firstCatalog;
                for (int icat = 0; icat < g->people[ippl].number_of_catalogs; icat++) {
                    for (int ient = 0; ient < c->number_of_entries; ient++) {
                        for (int ifld = 0; ifld < FIELDS; ifld++) {
                            delete [] c->entries[ient].fields[ifld];
                        }
                    }
                    Catalog * t = c;
                    c = c->nextCatalog;
                    delete t;
                }
            }
            delete [] g->people;
            Group * t = g;
            g = g->nextGroup;
            delete t;
        }
    }

    delete [] chains;
}

void Database::ins(char * fields[]) {
    char * insertname = fields[KEY];
    int ich = findchain((unsigned char *) fields[KEY]) % number_of_chains;
    bool found = false;    

    // check if a person already exists (1)
    Group * g = chains[ich].group;
    int ippl;

    cout << "Insertion on chain " << ich << endl;

    for (int igrp = 0; igrp < chains[ich].number_of_groups; igrp++) {
        for (ippl = 0; ippl < g->number_of_people; ippl++) {
            if (strcmp(g->people[ippl].phone, insertname) == 0) {
                found = true;
                break;
            }
        }
        if (found != true) {
            g = g->nextGroup;
        } else {
            break;
        }
    }

    if (found == false) {

        bool need_for_new_group = (chains[ich].number_of_people % Group::GROUP_CAPACITY) == 0;

        // ---------------------- create group ----------------------
        if (need_for_new_group == true) { // (2)
            if (chains[ich].group == NULL) { // no group exists,   2.1a
                chains[ich].group = new Group(); //   2.1b
                chains[ich].lastGroup = chains[ich].group;
            } else {
                chains[ich].lastGroup->nextGroup = new Group(); // 2.2a
                chains[ich].lastGroup = chains[ich].lastGroup->nextGroup; // 2.2b
            }
            chains[ich].number_of_groups++;
        }

        // -----------------------  add person  ---------------------------
        int position_in_group = chains[ich].number_of_people % Group::GROUP_CAPACITY;
        chains[ich].lastGroup->people[position_in_group].number_of_catalogs = 0;
        chains[ich].lastGroup->people[position_in_group].number_of_entries = 0;
        chains[ich].lastGroup->people[position_in_group].phone = new char[strlen(fields[KEY]) + 1];
        strcpy(chains[ich].lastGroup->people[position_in_group].phone, fields[KEY]);
        chains[ich].lastGroup->people[position_in_group].firstCatalog = NULL;
        chains[ich].lastGroup->people[position_in_group].lastCatalog = NULL;

        ippl = position_in_group;
        g = chains[ich].lastGroup;
        g->number_of_people++;
        chains[ich].number_of_people++;
    }

    // here:
    // g is the group in which target person exists
    // ippl is the position within the group

    bool need_for_new_catalog = (g->people[ippl].number_of_entries % CATALOG_CAPACITY) == 0;

    if (need_for_new_catalog) {
        if (g->people[ippl].firstCatalog == NULL) {
            g->people[ippl].firstCatalog = new Catalog();
            g->people[ippl].lastCatalog = g->people[ippl].firstCatalog;
            g->people[ippl].number_of_catalogs = 1;
            g->people[ippl].number_of_entries = 0;
        } else {
            g->people[ippl].lastCatalog->nextCatalog = new Catalog();
            g->people[ippl].lastCatalog->nextCatalog->previousCatalog = g->people[ippl].lastCatalog;
            g->people[ippl].lastCatalog = g->people[ippl].lastCatalog->nextCatalog;
            g->people[ippl].number_of_catalogs++;
        }
    }

    // -----------------------  add entry  ---------------------------
    int position_in_catalog = g->people[ippl].number_of_entries % CATALOG_CAPACITY;
    for (int i = 0; i < FIELDS; i++) {
        g->people[ippl].lastCatalog->entries[position_in_catalog].fields[i] = new char[strlen(fields[KEY]) + 1];
        strcpy(g->people[ippl].lastCatalog->entries[position_in_catalog].fields[i], fields[i]);
    }
    g->people[ippl].lastCatalog->number_of_entries++;
    g->people[ippl].number_of_entries++;
}

void Database::del(char * fields[]) {
    char * personname = fields[0];
    char * ent_id = fields[1];

    int ich = findchain((unsigned char *) personname) % number_of_chains;

    cout << "Deleting ..." << ent_id << endl;
    Group * g = chains[ich].group;
    for (int igrp = 0; igrp < chains[ich].number_of_groups; igrp++) {
        for (int ippl = 0; ippl < g->number_of_people; ippl++) {
            if (strcmp(g->people[ippl].phone, personname) == 0) {
                cout << "Phone found: " << g->people[ippl].phone << endl;
                Catalog * c = g->people[ippl].firstCatalog;
                for (int icat = 0; icat < g->people[ippl].number_of_catalogs; icat++) {
                    for (int ient = 0; ient < c->number_of_entries; ient++) {
                        if (strcmp(c->entries[ient].fields[0], ent_id) == 0) { // to brikame ...
                            cout << "Entry found (delete): ";

                            int d = ient; // thesi diagrafis entos tou catalog pou brethike to thima                            
                            for (int i = 0; i < FIELDS; i++) { // diagrafi
                                delete c->entries[ient].fields[i];
                            }
                            g->people[ippl].number_of_entries--;

                            if (c == g->people[ippl].lastCatalog) { // 1b
                                if (c->number_of_entries == 1) { // 2a
                                    if (g->people[ippl].lastCatalog == g->people[ippl].firstCatalog) { // 3a
                                        delete g->people[ippl].lastCatalog;
                                        g->people[ippl].firstCatalog = NULL;
                                        g->people[ippl].lastCatalog = NULL;
                                        g->people[ippl].number_of_catalogs--;
                                        return;
                                    } else { // 3b
                                        g->people[ippl].lastCatalog = g->people[ippl].lastCatalog->previousCatalog;
                                        g->people[ippl].lastCatalog->nextCatalog = NULL;
                                        g->people[ippl].number_of_catalogs--;
                                        return;
                                    }
                                } else { // 2b
                                    int lst = g->people[ippl].lastCatalog->number_of_entries - 1;
                                    if (d == lst) { // 4b
                                        g->people[ippl].lastCatalog->number_of_entries--;
                                    } else { // 4a
                                        for (int i = 0; i < FIELDS; i++) {
                                            c->entries[d].fields[i] = c->entries[lst].fields[i];
                                        }
                                        g->people[ippl].lastCatalog->number_of_entries--;
                                    }
                                    return;
                                }
                            } else { // 1a
                                int lst = g->people[ippl].lastCatalog->number_of_entries - 1;
                                for (int i = 0; i < FIELDS; i++) {
                                    c->entries[d].fields[i] = g->people[ippl].lastCatalog->entries[lst].fields[i];
                                }
                                g->people[ippl].lastCatalog->number_of_entries--;

                                if (g->people[ippl].lastCatalog->number_of_entries == 0) { // 5a
                                    if (g->people[ippl].lastCatalog == g->people[ippl].firstCatalog) { // 3a
                                        delete g->people[ippl].lastCatalog;
                                        g->people[ippl].firstCatalog = NULL;
                                        g->people[ippl].lastCatalog = NULL;
                                        g->people[ippl].number_of_catalogs--;
                                    } else { // 3b
                                        g->people[ippl].lastCatalog = g->people[ippl].lastCatalog->previousCatalog;
                                        g->people[ippl].lastCatalog->nextCatalog = NULL;
                                        g->people[ippl].number_of_catalogs--;
                                    }
                                }
                                return;
                            }
                        }
                    }
                    c = c->nextCatalog;
                }
                return;
            }
        }
        g = g->nextGroup;
    }
}

void Database::indist(char * fields[]) {
    // ???
}

void Database::topdest(char * fields[]) {
    char * searchname = fields[0];
    int ich = findchain((unsigned char *) searchname) % number_of_chains;

    Group * g = chains[ich].group;
    for (int igrp = 0; igrp < chains[ich].number_of_groups; igrp++) {
        for (int ippl = 0; ippl < g->number_of_people; ippl++) {
            if (strcmp(g->people[ippl].phone, searchname) == 0) {
                cout << "Phone found for topdest: " << g->people[ippl].phone << endl;

                int counters[1000];
                for (int i = 0; i < 1000; i++) {
                    counters[i] = 0;
                }

                Catalog * c = g->people[ippl].firstCatalog;
                for (int icat = 0; icat < g->people[ippl].number_of_catalogs; icat++) {
                    for (int ient = 0; ient < c->number_of_entries; ient++) {
                        char * calledPhone = c->entries[ient].fields[ENT_RECEIVER];
                        int country = atoi(calledPhone);

                        counters[country]++;
                    }
                    c = c->nextCatalog;
                }

                int max = 0;
                for (int i = 0; i < 1000; i++) {
                    if (counters[i] > max) {
                        max = counters[i];
                    }
                }

                cout << "Max is " << max << endl;
                cout << "Countries with max are: \n";

                for (int i = 0; i < 1000; i++) {
                    if (counters[i] == max) {
                        cout << "\t" << i << endl;
                    }
                }
                return;
            }
        }
        g = g->nextGroup;
    }
}

void Database::top(char * fields[]) {
    cout << "no top available" << endl;
}

void Database::print() {
    for (int ich = 0; ich < number_of_chains; ich++) {
        Group * g = chains[ich].group;
        cout << "Chain " << ich << ", number of groups: " << chains[ich].number_of_groups << ", number of people " << chains[ich].number_of_people << endl;
        for (int igrp = 0; igrp < chains[ich].number_of_groups; igrp++) {
            if (g->number_of_people > 0) {
                cout << " Group " << igrp << " with people " << g->number_of_people << endl;
            }
            for (int ippl = 0; ippl < g->number_of_people; ippl++) {
                cout << " + Phone: " << g->people[ippl].phone << endl;
                Catalog * c = g->people[ippl].firstCatalog;
                for (int icat = 0; icat < g->people[ippl].number_of_catalogs; icat++) {
                    if (c->number_of_entries > 0) {
                        cout << " Catalog " << icat << " with people " << c->number_of_entries << endl;
                    }

                    for (int ient = 0; ient < c->number_of_entries; ient++) {
                        cout << "      Entry: ";

                        for (int ifld = 0; ifld < FIELDS; ifld++) {
                            cout << c->entries[ient].fields[ifld] << " ";
                        }
                        cout << endl;
                    }
                    c = c->nextCatalog;
                }
            }
            g = g->nextGroup;
        }
    }
}

void Database::dump(char * fields[]) {
    ofstream out(fields[1]);
    for (int ich = 0; ich < number_of_chains; ich++) {
        Group * g = chains[ich].group;
        out << "Chain " << ich << ", number of groups: " << chains[ich].number_of_groups << ", number of people " << chains[ich].number_of_people << endl;
        for (int igrp = 0; igrp < chains[ich].number_of_groups; igrp++) {
            if (g->number_of_people > 0) {
                out << " Group " << igrp << " with people " << g->number_of_people << endl;
            }
            for (int ippl = 0; ippl < g->number_of_people; ippl++)   {
                out << " + Phone: " << g->people[ippl].phone << endl;
                Catalog * c = g->people[ippl].firstCatalog;
                for (int icat = 0; icat < g->people[ippl].number_of_catalogs; icat++) {
                    if (c->number_of_entries > 0) {
                        out << " Catalog " << icat << " with people " << c->number_of_entries << endl;
                    }
                    for (int ient = 0; ient < c->number_of_entries; ient++) {
                         out << "      Entry: ";

                        for (int ifld = 0; ifld < FIELDS; ifld++) {
                            out << c->entries[ient].fields[ifld] << " ";
                        }
                        out << endl;
                    }
                    c = c->nextCatalog;
                }
            }
            g = g->nextGroup;
        }
    }
}

void Database::find(char * fields[]) {
    char * searchname = fields[0];
    int ich = findchain((unsigned char *) searchname) % number_of_chains;

    Group * g = chains[ich].group;

    for (int igrp = 0; igrp < chains[ich].number_of_groups; igrp++) {
        for (int ippl = 0; ippl < g->number_of_people; ippl++) {
            if (strcmp(g->people[ippl].phone, searchname) == 0) {
                cout << "Phone: " << g->people[ippl].phone << endl;
                Catalog * c = g->people[ippl].firstCatalog;
                for (int icat = 0; icat < g->people[ippl].number_of_catalogs; icat++) {
                    for (int ient = 0; ient < c->number_of_entries; ient++) {                        
                        if (space(fields, &(c->entries[ient]))) {
                            cout << "Entry: ";
                            for (int ifld = 0; ifld < FIELDS; ifld++) {
                                cout << c->entries[ient].fields[ifld] << " ";
                            }
                            cout << endl;
                        }
                    }
                    c = c->nextCatalog;
                }
                return;
            }
        }
        g = g->nextGroup;
    }
}

bool Database::space(char * fields[], Entry * e) {
    char * t_ent = e->fields[ENT_TIME];
    char * d_ent = e->fields[ENT_DATE];


    if (fields[3] != NULL && fields[4] != NULL) { //  t t y y
        char buffer_from[1000];
        char buffer_to[1000];
        char buffer_what[1000];

        struct tm mytm_from;
        struct tm mytm_to;
        struct tm mytm_what;

        time_t t_from;
        time_t t_to;
        time_t t_what;

        strcpy(buffer_from, fields[2]);
        strcat(buffer_from, " ");
        strcat(buffer_from, fields[1]);

        strcpy(buffer_to, fields[4]);
        strcat(buffer_to, " ");
        strcat(buffer_to, fields[3]);

        strcpy(buffer_what, d_ent);
        strcat(buffer_what, " ");
        strcat(buffer_what, t_ent);

        strptime(buffer_from, "%d%m%Y %H:%M", &mytm_from);
        strptime(buffer_to, "%d%m%Y %H:%M", &mytm_to);
        strptime(buffer_what, "%d%m%Y %H:%M", &mytm_what);

        t_from = mktime(&mytm_from);
        t_to = mktime(&mytm_to);
        t_what = mktime(&mytm_what);

        if (t_from <= t_what && t_what <= t_to) {
            return true;
        } else {
            return false;
        }
    }

    if (fields[3] == NULL && fields[4] == NULL && fields[1] != NULL && fields[2] != NULL) { //  t t   or  y y 
        if (strlen(fields[1]) == 5) { // t t
            char buffer_from[50];
            char buffer_to[50];
            char buffer_what[50];

            struct tm mytm_from;
            struct tm mytm_to;
            struct tm mytm_what;

            time_t t_from;
            time_t t_to;
            time_t t_what;

            strcpy(buffer_from, "01012001");
            strcat(buffer_from, " ");
            strcat(buffer_from, fields[1]);

            strcpy(buffer_to, "01012001");
            strcat(buffer_to, " ");
            strcat(buffer_to, fields[2]);

            strcpy(buffer_what, "01012001");
            strcat(buffer_what, " ");
            strcat(buffer_what, t_ent);

            strptime(buffer_from, "%d%m%Y %H:%M", &mytm_from);
            strptime(buffer_to, "%d%m%Y %H:%M", &mytm_to);
            strptime(buffer_what, "%d%m%Y %H:%M", &mytm_what);

            t_from = mktime(&mytm_from);
            t_to = mktime(&mytm_to);
            t_what = mktime(&mytm_what);

            if (t_from <= t_what && t_what <= t_to) {
                return true;
            } else {
                return false;
            }
        } else { // y y
            char buffer_from[1000];
            char buffer_to[1000];
            char buffer_what[1000];

            struct tm mytm_from;
            struct tm mytm_to;
            struct tm mytm_what;

            time_t t_from;
            time_t t_to;
            time_t t_what;

            strcpy(buffer_from, fields[1]);
            strcat(buffer_from, " ");
            strcat(buffer_from, "00:00");

            strcpy(buffer_to, fields[2]);
            strcat(buffer_to, " ");
            strcat(buffer_to, "23:59");

            strcpy(buffer_what, d_ent);
            strcat(buffer_what, " ");
            strcat(buffer_what, "23:59");

            strptime(buffer_from, "%d%m%Y %H:%M", &mytm_from);
            strptime(buffer_to, "%d%m%Y %H:%M", &mytm_to);
            strptime(buffer_what, "%d%m%Y %H:%M", &mytm_what);

            t_from = mktime(&mytm_from);
            t_to = mktime(&mytm_to);
            t_what = mktime(&mytm_what);

            if (t_from <= t_what && t_what <= t_to) {
                return true;
            } else {
                return false;
            }
        }
    } else {
        return true;
    }
    return false;
}