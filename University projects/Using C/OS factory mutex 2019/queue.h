
#ifndef QUEUE_H
#define QUEUE_H

#include "structure.h"

typedef struct PartNode {
    struct Part part;

    struct PartNode *next;
    struct PartNode *previous;
} PartNode;

typedef struct PartList {
    PartNode *head;
    PartNode *tail;
    int size;
} PartList;

struct PartList *CreatePartList();

void DestroyList(struct PartList * p);

int getPartListSize(struct PartList *list);

int insertPartIntoPartList(struct PartList *list, struct Part *element);

void removeFromPartList(struct PartList *list, struct Part *element);

#endif /* QUEUE_H */
