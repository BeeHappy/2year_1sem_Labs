#ifndef mylist_H
#define mylist_H
#include <GL/glut.h>
#include <iostream>
#include <fstream>
using namespace std;

struct dot
{
    double x;
    double y;
    dot *next;
    dot(double xx, double yy) {
        x = xx;
        y = yy;
        next = 0;
    }
    dot(ifstream in) {
        in >> x;
        in >> y;
        next = 0;
    }
};

class mylist
{

private:
    dot *head;
    dot *tail;

public:

    mylist();
    ~mylist();

    dot *getHead();
    dot *getTail();
    void pushb(double x, double y);
    void pushb(dot a);
    void pushf(double x, double y);
    void push(int pos, double x, double y);
    void push(int pos, dot* newDot);
    void pop();
    void del(int pos);
    void show();
};

#endif // mylist_H
