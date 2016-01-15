#include "huffman.h"
#include <iostream>
using namespace std;

huffman::huffman() {

}
huffman::~huffman() {

}

void huffman::make() {
    ifstream input1("input1.txt");
    thread firstThread(&huffman::write, this, &input1,1);
    firstThread.join();

    ifstream input2("input2.txt");
    thread secondThread(&huffman::write, this, &input2,2);
    secondThread.join();

    ifstream input3("input3.txt");
    thread thirdhread(&huffman::write, this, &input3,3);
    thirdhread.join();
}

void huffman::write(ifstream*,int) {

}
