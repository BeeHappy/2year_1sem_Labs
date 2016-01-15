#ifndef LIST_H
#define LIST_H

struct node {
    node();
    node(int d, int jd);
    int data;
    int j;
    node *next;
};

class list {
    node *head;
    int len;

public:
    list();
    ~list();
    node* getHead() { return head; }
    int getLen()    { return len; }
    void push(int d, int j);
    //void del(int pos);
    void show();

    int& operator[](int j){
        node* cur = head;
        while(cur && (cur->j < j)) {
            cur = cur->next;
        }
        if(cur && (cur->j == j))
            return cur->data;

        else {
            node* err = new node();
            err->data = 0;
            return err->data;
        }
    }
};

#endif // LIST_H
