#include "list.h"
#include <iostream>
using namespace std;
node::node() {
    next = 0;
}

node::node(int d, int jd) {
    data = d;
    next = 0;
    j = jd;
}

list::list() {
    head = new node();
    len = 0;
}

list::~list() {
    while(head) {
        node *del = head;
        if(del){
            head = head->next;
            delete del;
        }
    }
}

void list::push(int d, int j) {
    node* cur = head;
    while(cur->next && cur->next->j < j)
        cur = cur->next;
    if(!cur->next) {
        cur->next = new node(d,j);
    }
    else {
        if(cur->next->j == j) //update
            cur->next->data = d;
        else {                          // cur->next->j > j
            node* newnod = new node(d,j);
            newnod->next = cur->next;
            cur->next = newnod;
        }
    }
    len++;
}
/*
void list::del(int pos) { // remake it (fiction head)
    if (pos-1 > len)
        cout << "Error. You're trying to delete non-existing node."
                << "The last node's position is "<< len + 1 << endl;
    else {
        if(pos == 1) {
            node* del = head;
            head = head->next;
            delete del;
        }
        else {
            node* nod = head;
            for(int i = 0; i<pos-2; i++)
                nod=nod->next;
            node* del = nod->next;
            nod->next = nod->next->next;
            delete del;
        }
        len--;
    }
}
*/
void list::show() {
    node* nod = head->next;
    if(!nod) {
        cout << "The list is empty!\n";
        return;
    }
    for(; nod; nod = nod->next)
        cout << nod->data << " ";
    cout << endl;
}
