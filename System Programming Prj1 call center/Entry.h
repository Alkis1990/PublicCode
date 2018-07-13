#ifndef ENTRY_H
#define ENTRY_H

#define FIELDS 9

#define ENT_ID 0
#define ENT_CALLER 1
#define ENT_RECEIVER 2
#define ENT_DATE 3   // DDMMYY
#define ENT_TIME 4
#define ENT_LENGTH 5
#define ENT_TYPE 6
#define ENT_TARIFF 7
#define ENT_ERROR 8

class Entry {
public:
    char * fields[FIELDS];
};

#endif /* ENTRY_H */

