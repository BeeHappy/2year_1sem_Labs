#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <thread>

using namespace std;

struct node
{
    int frequency;
    char letter;
    node* left;
    node* right;
    bool isLeaf;
    bool isUsed;

    void setUsed(bool use) { isUsed = use;}
    node() {
        left = right = 0;
        frequency = 0;
        isUsed = false;
    }
    node(int freq,node* l, node* r) {
        frequency = freq;
        left = l;
        right = r;
        isUsed = false;
        isLeaf = false;
    }
    ~node() {}
    node(int freq, char ch, bool leaf) {
        letter = ch;
        frequency = freq;
        left = right = 0;
        isUsed = false;
        isLeaf = leaf;
    }
};

class huffman
{
private:
    void write(ifstream*,int);

public:
    huffman();
    ~huffman();
    void make();
};


#endif // HUFFMAN
