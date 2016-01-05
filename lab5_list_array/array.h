#ifndef ARRAY_H
#define ARRAY_H

#include "list.h"
#include "iostream"

using namespace std;

class listOfLists {

public:
    list* row;
    int i;
    listOfLists* next;
    listOfLists(int i) {
        this->i = i;
        row = new list();
        next = 0;
    }
};

class array {
    listOfLists* head;
public:
    array();
    void push(int i, int j, int val);
    int get(int i, int j);      // returns the value of array[i,j]
    int getNumOfCol(int i);     // returns the number of columns (=j)
    int getMaxNumOfCol();
    int getNumOfRows();
    listOfLists* getHead() {
        return head;
    }

    void show();

    list& operator[](int i) {
        listOfLists *cur = head;
        while(cur && (cur->i < i)) {
            cur = cur->next;
        }
        if(cur && (cur->i == i)) {
            return *cur->row;
        }
        list* err = new list();
        return *err;
    }
    /*int operator()(int i, int j) {
        listOfLists* rows = head;
        while((rows != 0) && (rows->i < i))
            rows = rows->next;
        if(rows && rows->i == i) {
            node* cur = rows->row->getHead();
            while((cur != 0)&&(cur->j < j))
                cur = cur->next;
            if(cur)
                return cur->data;
    }*/

};

#endif // ARRAY_H
