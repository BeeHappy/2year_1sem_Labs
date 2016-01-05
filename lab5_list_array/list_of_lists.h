#ifndef LIST_OF_LISTS_H
#define LIST_OF_LISTS_H

#include "list.h"

class list_of_lists {
   // list* head;
   // list* tail;
    list* row;
    list* next;
   // int len;
public:
    list_of_lists();
    void add(list l, int i);
    void del(int i);
    
};

#endif // LIST_OF_LISTS_H
