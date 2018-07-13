
#ifndef PERSON_H
#define PERSON_H

#include "Catalog.h"

class Person {
public:
    char * phone;
    Catalog * firstCatalog;
    Catalog * lastCatalog;
    
    int number_of_entries;
    int number_of_catalogs;
};

#endif /* PERSON_H */

