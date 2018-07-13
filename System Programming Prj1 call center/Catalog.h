
#ifndef CATALOG_H
#define CATALOG_H

#include "Entry.h"

#include <cstdio>

#define CATALOG_CAPACITY 10

class Catalog {
public:
    Entry entries[CATALOG_CAPACITY];
    int number_of_entries;
    
    Catalog * nextCatalog;
    Catalog * previousCatalog;
    
    Catalog();
};

#endif /* CATALOG_H */

