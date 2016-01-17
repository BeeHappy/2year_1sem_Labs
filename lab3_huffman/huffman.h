#ifndef HUFFMAN
#define HUFFMAN

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <thread>

using namespace std;

struct node {
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
};


class huffman
{
private:
    vector <node*> tree;
    node* head;
    int numberLetter;
    map <char, int> frequency;
    map <char, string> codes;
    map <string, char> backToChar;
    vector <char> letters;

    void printCodes();
    void createCode();
    void findFrequencies(ifstream*);
    void updateFile(ifstream*,int);
    void code(node*, string);

    void update();
    void insert(node);
    void printTree(node*);
    void buildVectorbyFreq();
    void createTree();
    string createFileName(int,bool);


public:
    huffman();
    ~huffman();
    void makeStreams();
};


#endif // HUFFMAN
