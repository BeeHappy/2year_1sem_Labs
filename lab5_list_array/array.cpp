#include "array.h"

array::array() {
    head = 0;
}

void array::show() {
    for(listOfLists* rows = head; rows != 0; rows = rows->next) {
        for(node* cur = rows->row->getHead()->next; cur != 0; cur = cur->next)
            cout << "arr[" << rows->i << "]["<< cur->j << "] = "<< cur->data << endl;
    }
}
int array::getNumOfCol(int i) {
    listOfLists* rows = head;
    while((rows != 0) && (rows->i < i))
        rows = rows->next;
    if(rows && rows->i == i) {
        node* cur = rows->row->getHead();
        while(cur->next)
            cur = cur->next;
        return cur->j;
    }
    return 0;
}
int array::getMaxNumOfCol() {
    int i = 0;
    int max = 0;
    listOfLists* rows = head;
    while((rows != 0)) {
        int cur = this->getNumOfCol(i);
        if(cur > max)
            max = cur;
        i++;
        rows = rows->next;
    }
    return max;
}

int array::getNumOfRows() {
    listOfLists* rows = head;
    int i = 0;
    while((rows != 0)){
        i++;
        rows = rows->next;
    }
    return i-1;
}

int array::get(int i, int j) {
    listOfLists* rows = head;
    while((rows != 0) && (rows->i < i))
        rows = rows->next;
    if(rows && rows->i == i) {
        node* cur = rows->row->getHead();
        while((cur != 0)&&(cur->j < j))
            cur = cur->next;
        if(cur)
            return cur->data;
    }
    return 0; // not exist;
}

void array::push(int i, int j, int val) {
    listOfLists* cur = head;
    if(cur == 0) {              // head == 0
        cur = new listOfLists(i);
        cur->i = i;
        cur->row = new list();
        cur->row->push(val, j);
        head = cur;
    }
    else {
        while((cur->next)&&(cur->next->i < i)) {
            cur = cur->next;
        }
        if(!cur->next) {
            if(cur->i == i)
                cur->row->push(val, j);
            else if(cur->i < i) {
                listOfLists* newrow = new listOfLists(i);
                newrow->row->push(val, j);
                cur->next = newrow;
            }
            else { // cur->i > i
                listOfLists* newrow = new listOfLists(i);
                newrow->row->push(val, j);
                newrow->next = cur;
                cur->next = newrow;
                head = newrow;
            }
            return;
        }
        // cur->next != 0

        if(cur->next->i == i) {
            cur->next->row->push(val, j);
        }
        else { // cur->next->i > i
            listOfLists* newrow = new listOfLists(i);
            newrow->row->push(val, j);
            newrow->next = cur->next;
            cur->next = newrow;
        }
    }
}
