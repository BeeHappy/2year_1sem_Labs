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

/*
class Labyrinth
{
    bool** labyrinth;
    int size;
    int real_size;
    int* backtrack_x;
    int* backtrack_y;
    void generate(int, int, int, int);
    bool isClosed(int, int) const;

public:
    Labyrinth();
    ~Labyrinth();
    explicit Labyrinth(int);
    bool** get() const;
    int getSize() const;
    void generate();
    void print() const;
};
*/
#endif // LABYRINTH_H
