#include "huffman.h"
#include <iostream>
using namespace std;

huffman::huffman() {
    numberLetter = 0;
    makeStreams(); // inside this we also find all frequencies by func findFrequencies(ifstream* in)
    buildVectorbyFreq();
    createTree();
    head = tree[tree.size() - 1];
    createCode();
}

// making a vector of letters, sorted by frequencies
void huffman::buildVectorbyFreq() {
    node* cur;
    for (int i = 0; i < numberLetter; i++)     {
        //creates node
        cur = new node();
        cur->frequency = frequency[letters[i]];
        cur->isLeaf = true;
        cur->letter = letters[i];

        //inserts it to appropriate position in vector (sorted by frequency)
        int j = 0;
        int size = tree.size();
        while(j < size && (tree[j]->frequency < cur->frequency)) j++;
        tree.insert(tree.begin() + j,cur);
    }
}

//counts the frequency of all symbols
void huffman::findFrequencies(ifstream* in) {
    char letter;
    while (in->get(letter)) {
        if (frequency[letter] && frequency[letter] > 0) frequency[letter]++;
        else {
            numberLetter++;
            letters.push_back(letter);
            frequency[letter] = 1;
        }
    }
}

void huffman::makeStreams() {
    ifstream in1("in1.txt");
    ifstream in2("in2.txt");
    ifstream in3("in3.txt");
    thread firstThread(&huffman::findFrequencies, this, &in1);
    thread secondThread(&huffman::findFrequencies, this, &in2);
    thread thirdhread(&huffman::findFrequencies, this, &in3);
    firstThread.join();
    secondThread.join();
    thirdhread.join();
}

// making a unique code recursively (adds '0' if we go to the left son, and '1' else)
void huffman::createCode() {
    code(head, "");
}
void huffman::code(node* cur, string nodeData) {
    if (cur) {
        if (cur->isLeaf) {
            codes[cur->letter] = nodeData;
            backToChar[nodeData] = cur->letter;
        }
        else {
            string codeName = nodeData;

            nodeData = nodeData + "0";
            code(cur->left, nodeData);

            nodeData = codeName + "1";
            code(cur->right, nodeData);
        }
    }
}

//create binary tree with leafs-nodes
void huffman::createTree() {
    int size = tree.size();
    for (int i = 0; i < size - 1; i++) {
        // merges two first nodes (as they have the smallest frequency) to a newNode
        node* newNode = new node();
        newNode->frequency = tree[0]->frequency + tree[1]->frequency;
        newNode->left = tree[0];
        newNode->right = tree[1];

        //delete both tree[0] and tree[1]
        tree.erase(tree.begin());
        tree.erase(tree.begin());
        newNode->isLeaf = false;
        int j = 0;
        while(tree[j]->frequency < newNode->frequency) j++; // find an appropriate position(sorted by frequency)
        // inserts newNode to the position j
        tree.insert(tree.begin() + j,newNode);
    }
    head = tree[0];
}

huffman::~huffman() {
    frequency.clear();
    letters.clear();
}

//prints sybmbol and its code
void huffman::printCodes() {
    for (int i = 0; i < numberLetter; i++)     {
        cout << letters[i] << "  " << codes[letters[i]] << " \n";
    }
    cout << "\n";
}

//create some threads to write to many files in the same time
void huffman::update() {
    ifstream in1("in1.txt");
    ifstream in2("in2.txt");
    ifstream in3("in3.txt");
    thread firstThread(&huffman::updateFile, this, &in1,1);
    thread secondThread(&huffman::updateFile, this, &in2,2);
    thread thirdhread(&huffman::updateFile, this, &in3,3);
    firstThread.join();
    secondThread.join();
    thirdhread.join();
}

string huffman::createFileName(int numberFile,bool in) {
    string fileName = "";
    if (!in) fileName ="out";
    else fileName = "in";
    char numberOfFile = char(numberFile + int('0'));
    fileName += numberOfFile;
    fileName += ".txt";
    return fileName;
}

//creates file that contains codes instead of sybmols
void huffman::updateFile(ifstream* in,int numberFile) {
    char letter;
    string fileName = createFileName(numberFile, false);
    ofstream output(fileName, std::ios::binary);
    numberLetter = 0;
    while (in->get(letter))   
        output << codes[letter] << " ";
    output.close();
}
