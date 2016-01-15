#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include "mylist.h"
#include <stack>
#include <vector>

using namespace std;


vector <vector <dot> > convexes;
mylist list;
mylist *l = & list;
int N;
bool first = true;
int red = 0;

// true <=> show
bool lines = false;
bool edges = true;
bool conv = false; // convex hull

void reshape(int w, int h);
void display();
void KeyboardEvent(unsigned char key, int x, int y);

void showLines ();          // drawing lines between every vertex and head
void showEdgesQueue();      // drawing edges in order from head to tail (order is showing by color: from blue to black)
void showDots ();           // drawing dots (head and current dots are red)
void showConvex(int time);
void showAllConvexes();
void demo();                // shows all one by one

bool ok (dot *d0, dot *d1, dot *d2);        // true, if vector d0d1 is left for d0d2
bool okConvex (dot *d0, dot *d1, dot *d2);  // true, if vector d1d2 is left for d0d1
void swap (dot* d1, dot* d2);

void convexHull(int);
void leftTopDot ();         // left top dot become head
void sort (int time);       // sorting by angle with head
vector<dot> findConvex();  // returns stack with a convex hull
//stack <dot*>
void showConvex(int time) {
    conv = true;
    lines = true;
    edges = true;
    glutPostRedisplay();
    glutTimerFunc(100, showConvex,100 );
}

void demo() {
    convexHull(1);
    glutTimerFunc(glutGet(GLUT_ELAPSED_TIME), sort, 200 );
    showConvex(1);
}

void KeyboardEvent(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 's' :  sort(1);
                    break;
        case 'c' :  conv = true;
                    break;
        case 'd' :  demo();
                    break;
    }
}

void showEdgesQueue() {
    glBegin(GL_LINES);
    dot* cur = l->getHead();
    while(cur->next) {
        glColor3f(0,0,0);
        glVertex2d(cur->x,cur->y);
        glColor3f(0,0,1);
        glVertex2d(cur->next->x,cur->next->y);
        cur = cur->next;
    }
    glEnd();
}

void showLines() {
    glBegin(GL_LINES);
    dot* cur = l->getHead()->next;
    glColor3f(0.6,0.6,0.6);
    while(cur) {
        glVertex2d(l->getHead()->x,l->getHead()->y);
        glVertex2d(cur->x,cur->y);
        cur = cur->next;
    }
    glEnd();
}

void showDots() {
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glEnable(GL_PROGRAM_POINT_SIZE);
    dot* cur = l->getHead();
    glColor3f(1,0,0);
    glVertex2d(cur->x,cur->y);
    cur = cur->next;
    glColor3f(0,0,0);
    int i = 2;
    while(cur) {
        if(red == i) {
            i++;
            glVertex2d(cur->x,cur->y);
            cur = cur->next;
            break;
        }
        i++;
        glVertex2d(cur->x,cur->y);
        cur = cur->next;
    }

    glEnd();
}

bool ok(dot *d0, dot *d1, dot *d2) {
    double ax = d1->x - d0->x;
    double ay = d1->y - d0->y;
    double bx = d2->x - d0->x;
    double by = d2->y - d0->y;
    if((ax*by-ay*bx) > 0) return true;
    else if(((ax*by-ay*bx) == 0) && (d2->x > d1->x)) return true;
    else return false;
}

bool okConvex(dot *d0, dot *d1, dot *d2) {
    double ax = d1->x - d0->x;
    double ay = d1->y - d0->y;
    double bx = d2->x - d1->x;
    double by = d2->y - d1->y;
    if((ax*by-ay*bx) >= 0) return true;
    //else if(((ax*by-ay*bx) == 0) && (d2->x > d1->x)) return true;
    else return false;
}

void swap(dot* d1, dot* d2) {
    double tx, ty;
    tx = d1->x;    d1->x = d2->x;    d2->x = tx;
    ty = d1->y;    d1->y = d2->y;    d2->y = ty;
}

void leftTopDot() {
    for(dot* cur = l->getHead(); cur != 0; cur = cur->next) { //head->next?
        if((l->getHead()->x > cur->x) ||
           ((cur->x == l->getHead()->x)&&(l->getHead()->y < cur->y)))
                swap(cur, l->getHead());
    }
}

void sort(int time) {
    if(N == 0) return;
    static int end = 0;
    if(end>N)
        end = 0;
    dot* cur = l->getHead()->next;
    int idNewDot = 2;
    while(cur->next && ok(l->getHead(),cur, cur->next)) {
        cur = cur->next;
        idNewDot++;
    }
    if(l->getHead()->next == cur) {
        double x = cur->x;
        double y = cur->y;
        cur->x = cur->next->x;
        cur->y = cur->next->y;
        cur->next->x = x;
        cur->next->y = y;
    }
    else  {
        if(cur->next) {
            cur = cur->next;
        dot* newDot = new dot(cur->x, cur->y);
        int i = 2;
        for(dot* pos = l->getHead()->next; pos != cur; pos = pos->next) {
            if(ok(l->getHead(), newDot, pos))
                break;
            i++;
        }
        l->push(i,newDot);
        l->del(idNewDot+2);
        red = i;
        }
    }
    if(end < N) // N-3
    glutTimerFunc(150,sort,100);
    end++;
}

void convexHull(int) {
    if(first) {
        first = false;
        ifstream in("in.txt");
        in >> N;

        for(int i = 0; i < N; i++) {
            double x, y;
            in >> x >> y;
            l->pushb(x,y);
        }
    }
    if(N == 0) showAllConvexes();
    else
    if(N<=3) {
        showAllConvexes();
        glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0);
        for(dot* cur = l->getHead(); cur != 0; cur = cur->next)
            glVertex2d(cur->x, cur->y);
        glVertex2d(l->getHead()->x, l->getHead()->y);
        glEnd();
    }
    else {
        leftTopDot();
        showDots();        
        if(lines) showLines();
        if(edges) showEdgesQueue();
        if(conv) {
            vector<dot> dots = findConvex();
            convexes.push_back(dots);
            conv = false;
        }
        showAllConvexes();
    };
    glutPostRedisplay();
};

dot copyDot(dot* original) {
    dot d(original->x,original->y);
    return d;
}

vector <dot> findConvex() {
    vector <dot> dots;
    dot* one = l->getHead();
    dot* two = one->next;
    dot* three = two->next;
    dots.insert(dots.begin(),1,copyDot(one));
    dots.insert(dots.begin(),1,copyDot(two));
    for(int i = 2; i < N; i++) {

        while(!okConvex(one,two,three)) {
            dots.erase(dots.begin(),dots.begin()+1);//.pop(); // pop two
            //three = two;
            two = one;
            one = l->getHead();
            while(one->next != two)
                one = one->next;
            // one = two->prev
        }
        dots.insert(dots.begin(),1,copyDot(three));

        one = two;
        two = three;
        three = three->next;
    };

    for(int j = dots.size(); j > 0; j--) {
        dot* cur = l->getHead();
        int k = 0;
        dot curDotInConvex = dots.at(j-1);
        while((curDotInConvex.x != cur->x) || (curDotInConvex.y != cur->y)) {
            cur = cur->next;
            k++;
        }
        l->del(k+1);
        N--;
    }

    return dots;
};

void showAllConvexes()
{
    for(int i = 0; i < convexes.size(); i++) {
        vector<dot> convex = convexes.at(i);

        glBegin(GL_LINE_STRIP);
        glColor3f(1.0, 0.0, 0.0);

        dot cur = convex.at(0);
        for(int j = 0; j < convex.size(); j++) {
            cur = convex.at(j);
            glVertex2d(cur.x,cur.y);
        }
        cur = convex.at(0);
        glVertex2d(cur.x, cur.y);
        glEnd();
    }
};

