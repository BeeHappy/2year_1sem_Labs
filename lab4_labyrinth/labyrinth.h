#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <iostream>
using namespace std;

class Labyrinth {
    char** cells;
    bool** rightWalls;
    bool** bottomWalls;
    int width;
    int height;

    //void generate();

public:
    Labyrinth(int w, int h);
    //~Labyrinth();
    void generate();
    void print();
    bool getRightWalls(int i, int j);
    bool getBottomWalls(int i, int j);
};

#endif // LABYRINTH_H
