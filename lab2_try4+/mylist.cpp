#include "mylist.h"
#include <iostream>
using namespace std;

mylist::mylist()
{
    head = tail = 0;
}

mylist::~mylist()
{
    dot *del = this->head;
    if(del)
    {
        if(del->next)
        {
            this->head = this->head->next;
            delete del;
        }
        else
        {
            //delete this->head; // del?
            this->head= NULL;
        }
    }
}

dot* mylist::getHead() {return head;}
dot* mylist::getTail() {return tail;}
void mylist::pushb(dot a) {
    if(head == 0)
    {
        head = new dot(a.x,a.y);
        tail = head;
    }
    else
    {
        tail->next = new dot(a.x,a.y);
        tail = tail->next;
    }
}

void mylist::pushb(double x, double y)
{
    if(head == 0)
    {
        head = new dot(x,y);
        tail = head;
    }
    else
    {
        tail->next = new dot(x,y);
        tail = tail->next;
    }
}

void mylist::pushf(double x, double y)
{
    if(head == 0)
    {
        head = new dot(x,y);
        tail = head;
    }
    else
    {
        dot* nod = head;
        head = new dot(x,y);
        head->next = nod;
    }
}

void mylist::push(int pos, double x, double y) // inserts d on position pos (pushing all next to 1 pos more)
{
    //here should be checking of correct data pos
    dot* nod = head;
    for(int i = 0; i < pos - 2; i++)
        nod = nod->next;
    dot* newnod = new dot(x,y);
    newnod->next = nod->next;
    nod->next = newnod;
}

void mylist::push(int pos, dot* newDot) // inserts d on position pos (pushing all next to 1 pos more)
{
    //here should be checking of correct data pos
    dot* nod = head;
    for(int i = 0; i < pos - 2; i++)
        nod = nod->next;
    newDot->next = nod->next;
    nod->next = newDot;
}

void mylist::pop()
{
    dot* nod = head;
    if(!nod)
        cout<< "The mylist is empty!\n";
    else
        if(!nod->next)
        {
            delete nod;
            head = tail = 0;
        }
        else
        {
            for(; nod->next != tail; nod = nod->next);
            delete tail;
            nod->next = 0;
            tail = nod;
        }
}

void mylist::del(int pos)
{
    //here should be checking of correct data pos


    dot* nod = head;
    if(pos == 1) {
        if(nod->next) {
            head = head->next;
            delete nod;
        }
        else
            delete head;
        return;
    }
    for(int i = 0; i < pos-2; i++)
        nod=nod->next;
    if(nod->next) {
    dot* delDot = nod->next;
    nod->next = nod->next->next;
    delete delDot;
    }

}

void mylist::show()
{
    dot* nod = head;
    if(!nod)
    {
        cout << "The mylist is empty!\n";
        return;
    }
    for(; nod; nod = nod->next)
        cout << "("<< nod->x << " " << nod->y << ") ";
    cout << endl;
}
