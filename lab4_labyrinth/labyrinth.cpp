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
