#ifndef Node_hpp
#define Node_hpp

#include <iostream>
#include "Kisi.hpp"
#include "Stack.hpp"
using namespace std;
class Node
{

public:
    Node();
    Node(int y, string a, int t, int idd);

    Kisi *kisi;
    Stack *stack;
    Node *left;
    Node *right;
    int height;
    int id;

    int max(int a, int b);
    int getHeight(Node *N);
    Node *newNode(int yas, string ad, int kilo, int idd);
    Node *rightRotate(Node *y);
    Node *leftRotate(Node *x);
    int getBalance(Node *N);
    Node *insert(Node *node, int key, string ad, int tarih, int idd);
    void Postorder(Node *root);
    void yukseklikAl(Node *root, int dizi[5]);
    void pushLocation(Node *root, char move, int id);
    int getLevelUtil(Node *node, int data, int level);

    ~Node();
};

#endif