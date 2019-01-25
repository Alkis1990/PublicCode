#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct PartList *CreatePartList() {
    /* List. */
    struct PartList *bl = NULL;
    if ((bl = (struct PartList *) calloc(1, sizeof (struct PartList))) == NULL) {
        perror("List Creation.");
        exit(0);
    } else {
        /* Init. */
        bl->head = NULL;
        bl->tail = NULL;
        bl->size = 0;

        return bl;
    }
}

void DestroyList(struct PartList * list) {
    free(list);
}

int getPartListSize(struct PartList *list) {
    return list->size;
}

int insertPartIntoPartList(struct PartList *list, struct Part *element) {
    /* Create the Book. */
    struct PartNode * newnode = (struct PartNode *) malloc(sizeof (PartNode));
    newnode->next = NULL;
    newnode->previous = NULL;
    newnode->part = *element;

    /* Case Empty List. */
    if (list->size == 0) {
        list->head = newnode;
        list->tail = newnode;
    } else {
        list->tail->next = newnode;
        newnode->previous = list->tail;

        list->tail = newnode;
    }

    list->size++;
    return 0;
}

void removeFromPartList(struct PartList *list, struct Part *element) {
    *element = list->head->part;

    struct PartNode * tempnode = list->head;
    list->head = list->head->next;

    free(tempnode);

    list->size--;
    
    if (list->size == 0) {
        list->head = NULL;
        list->tail = NULL;
    }
}