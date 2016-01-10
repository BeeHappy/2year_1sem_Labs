#include "stdafx.h"
#include "labyrinth.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Labyrinth::Labyrinth(int w, int h) {
    width = w;
    height = h;

    cells = new char* [height];
    for(int i = 0; i < height; i++)
        cells[i] = new char[width];

    rightWalls = new bool* [height];
    for(int i = 0; i < height; i++)
        rightWalls[i] = new bool[width];

    bottomWalls = new bool* [height];
    for(int i = 0; i < height; i++)
        bottomWalls[i] = new bool[width];

    srand(static_cast<unsigned>(time(NULL)));

    //generate();
}
void Labyrinth::generate() {
    //we're going to save right and bottom walls for each cell

    //--------------- right walls ---------------
    static char id = 'a';
    static bool first = true;
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
        if(!first) {
            if(!cells[i][j]) {
                if(!bottomWalls[i-1][j])
                    cells[i][j] = cells[i-1][j];
                else {
                    cells[i][j] = id;
                    if(id >= 'z') id = 'a';
                    else id++;
                }
            }
            first = false;
        }

        if(!cells[i][j]){
            cells[i][j]=id;
            if(id >= 'z') id = 'a';
            else id++;
        }         //unique number for each group of cells

        //if((j+1 < width) && (cells[i][j] == cells[i][j+1]))
        //    rightWalls[i][j] = 1;
        //else{
            int random = rand() % 2; // = to make or not to make a right wall
            if(random) {
                rightWalls[i][j] = 1;
                // cout << "0, " << j << " = 1;";
            }
            else {
                rightWalls[i][j] = 0;
                if(j+1)
                    cells[i][j+1]=cells[i][j];
                // cout << "0, " << j << " = 0;";
            }
        //}
        //cout << endl;
    }
    rightWalls[i][width - 1] = 1;

// ---------------bottom walls---------------
    //this->print();
    int j = 0;
    if(rightWalls[i][0]){

        if(cells[i][0] == cells[i][1])
            bottomWalls[i][0] = 1;
        else
            bottomWalls[i][0] = 0;
        j++;
    }
   // this->print();
    //if(!rightWalls[i][0]) bottomWalls[i][0] = 1;
    //else bottomWalls[i][0] = 0;
    for(; j < width; j++) {
        if (!(rightWalls[i][j] && rightWalls[i][j-1]))
        bottomWalls[i][j] = 1;
        else bottomWalls[i][j] = 0;
    }
    //this->print();

    j = 0;
    char curGroup = cells[i][j];
    bool isClosed = true;
    while (j < width) {

        while(j < width && bottomWalls[i][j] == 0) { // for one-member cells
            j++;
            curGroup = cells[i][j];
            //isClosed = false;
            //while(cells[i][j] == curGroup) j++;
            //isClosed = true;
        }
        //---
        if(cells[i][j] != curGroup) {
            //if j-1 and isClosed
            bottomWalls[i][j-1] = 0;
            curGroup = bottomWalls[i][j];
            //isClosed = true;
        }
        //---
        //curGroup == cells[i][j], isClosed = true
        int random = rand() % 2; // = to delete or not to delete a bottom wall
        if(random) {
            bottomWalls[i][j] = 0;
            while(cells[i][j] == curGroup && j < width) j++;
            if(j < width) curGroup = cells[i][j];
            continue;
        }
        j++;
    }
/*
    char curGroup = cells[i][0];
    for(int j = 0; j < width; j++) {
        //static char curGroup = cells[i][j];

        if(!bottomWalls[i][j]) {    // skipping already open group (for one-member groups)
            curGroup = cells[i][j];
        //    while(cells[i][j] == curGroup && j < width) j++;
        //    if(j < width) curGroup = cells[i][j];
        //    j--;
            if(j+1 < width) curGroup = cells[i][j+1];
            continue;
        }

        if (cells[i][j] != curGroup) {
           // if(isBlocked) bottomWalls[0][j-1] = 0;
            if(j-1 < width) bottomWalls[i][j-1] = 0;
            curGroup = cells[i][j];
            j--;//stay at the same position
            continue;
        }
        int random = rand() % 2; // = to delete or not to delete a bottom wall
        if(random) {
            bottomWalls[i][j] = 0;
            //cout << "0, " << j << " = 0;";
            while(cells[i][j] == curGroup && j < width) j++;
            if(j < width) curGroup = cells[i][j];
            j--;
        }

       // cout << endl;
    }*/
    first = false;
  }
  //--------------last row----------------
  for(int j = 0; j < width; j++) {
      int i = height - 1;
      bottomWalls[i][j] = 1; // has all bottom walls

     /* if(!bottomWalls[i-1][j])
          cells[i][j] = cells[i-1][j];
      else {
          cells[i][j] = id;
          if(id >= 'z') id = 'a';
          else id++;
      }*/
      if(cells[i][j] != cells[i][j+1]) {
          cells[i][j+1] = cells[i][j];
          rightWalls[i][j] = 0;
      }
      rightWalls[i][width - 1] = 1;
  }
}
void Labyrinth::print() {
    for(int j = 0; j < width; j++) cout << " _";// top line
    cout << endl;
    for(int i = 0; i < height; i++){
        cout <<"|";                             //left side of each row
        for (int j = 0; j < width; j++){
            if(bottomWalls[i][j]) cout << "_";
            else cout << " ";//cells[i][j];
            if(rightWalls[i][j]) cout << "|";
            else cout << " ";
        }
        cout << endl;
    }
}

bool Labyrinth::getRightWalls(int i, int j) {
    if(rightWalls[i][j]) return 1;
    return 0;
}

bool Labyrinth::getBottomWalls(int i, int j) {
    if(bottomWalls[i][j]) return 1;
    return 0;
}

/*
void Labyrinth::generate() {
    int index = 0;
    generate(index, 1, 1, 1);
}

void Labyrinth::generate(int index, int x , int y, int visited) {
    if (visited < size * size) {
        int neighbour_valid = -1;
        int neighbour_x[4];
        int neighbour_y[4];
        int step[4];

        int x_next;
        int y_next;

        if (x - 2 > 0 && isClosed(x - 2, y)) {      // upside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x - 2;;
            neighbour_y[neighbour_valid] = y;
            step[neighbour_valid] = 1;
        }

        if (y - 2 > 0 && isClosed(x, y - 2)) {  // leftside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x;
            neighbour_y[neighbour_valid] = y - 2;
            step[neighbour_valid] = 2;
        }

        if (y + 2 < real_size && isClosed(x, y + 2)) {  // rightside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x;
            neighbour_y[neighbour_valid] = y + 2;
            step[neighbour_valid] = 3;
        }

        if (x + 2 < real_size && isClosed(x + 2, y)) { // downside
            neighbour_valid++;
            neighbour_x[neighbour_valid] = x + 2;
            neighbour_y[neighbour_valid] = y;
            step[neighbour_valid] = 4;
        }

        if (neighbour_valid == -1) {
            // backtrack
            x_next = backtrack_x[index];
            y_next = backtrack_y[index];
            index--;
        }

        if (neighbour_valid != -1) {
            int randomization = neighbour_valid + 1;
            int random = rand() % randomization;
            x_next = neighbour_x[random];
            y_next = neighbour_y[random];
            index++;
            backtrack_x[index] = x_next;
            backtrack_y[index] = y_next;

            int rstep = step[random];

            if (rstep == 1)
                labyrinth[x_next + 1][y_next] = false; // false = no wall
            else if (rstep == 2)
                labyrinth[x_next][y_next + 1] = false;
            else if (rstep == 3)
                labyrinth[x_next][y_next - 1] = false;
            else if (rstep == 4)
                labyrinth[x_next - 1][y_next] = false;
            visited++;
        }
        generate(index, x_next, y_next, visited);
    }
}

bool Labyrinth::isClosed(int x, int y) const {
    if (labyrinth[x - 1][y] == true && // true = wall
        labyrinth[x][y - 1] == true &&
        labyrinth[x][y + 1] == true &&
        labyrinth[x + 1][y] == true)
        return true;

    return false;
}

Labyrinth::Labyrinth() {}

Labyrinth::Labyrinth(int size) : size(size) {
    srand(static_cast<unsigned>(time(NULL)));
    real_size = size * 2 + 1;

    backtrack_x = new int[size * size];
    backtrack_y = new int[size * size];
    backtrack_x[0] = 1;
    backtrack_y[0] = 1;

    labyrinth = new bool*[real_size];

    for (int i = 0; i < real_size; ++i)
        labyrinth[i] = new bool[real_size];

    for (int i = 0; i < real_size; ++i) {
        for (int j = 0; j < real_size; ++j) {
            if (i % 2 == 0 || j % 2 == 0)
                labyrinth[i][j] = true;
            else
                labyrinth[i][j] = false;
        }
    }
}

bool** Labyrinth::get() const {
    return labyrinth;
}

int Labyrinth::getSize() const {
    return real_size;
}

void Labyrinth::print() const {
    for (int i = 0; i < real_size; ++i) {
        for (int j = 0; j < real_size; ++j) {
            if (labyrinth[i][j] == true)
                std::cout << "#";
            else
                std::cout << " ";
        }
        std::cout << "\n";
    }
}

Labyrinth::~Labyrinth() {
}
*/
