#include <iostream>
#include "Node.hpp"
#include "Kisi.hpp"
#include "Stack.hpp"
using namespace std;

Node::Node()
{
}

int Node::getLevelUtil(Node *node, int data, int level)
{
    if (node == NULL)
        return 0;

    if (node->id == data)
        return level;

    int downlevel = getLevelUtil(node->left,
                                 data, level + 1);
    if (downlevel != 0)
        return downlevel;

    downlevel = getLevelUtil(node->right,
                             data, level + 1);
    return downlevel;
}

Node::Node(int tarih, string a, int kilo, int idd)
{
    kisi = new Kisi(tarih, a, kilo);
    stack = new Stack();
    stack->push('O');
    id = idd;
}

Node *Node::newNode(int yas, string ad, int kilo, int idd)
{
    Node *node = new Node(yas, ad, kilo, idd);
    node->kisi = new Kisi(yas, ad, kilo);
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially
                      // added at leaf
    return (node);
}

Node *Node::rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left),
                    getHeight(y->right)) +
                1;
    x->height = max(getHeight(x->left),
                    getHeight(x->right)) +
                1;

    // Return new root
    return x;
}

Node *Node::leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left),
                    getHeight(x->right)) +
                1;
    y->height = max(getHeight(y->left),
                    getHeight(y->right)) +
                1;

    // Return new root
    return y;
}

int Node::getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return getHeight(N->left) - getHeight(N->right);
}

Node *Node::insert(Node *node, int key, string ad, int kilo, int idd)
{
    /* 1. Perform the normal BST insertion */
    if (node == NULL)
        return (newNode(key, ad, kilo, idd));

    if (key <= node->kisi->yas)
        node->left = insert(node->left, key, ad, kilo, idd);
    else if (key > node->kisi->yas)
        node->right = insert(node->right, key, ad, kilo, idd);

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(getHeight(node->left),
                           getHeight(node->right));

    /* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->kisi->yas)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->kisi->yas)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->kisi->yas)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->kisi->yas)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

void Node::Postorder(Node *root)
{
    if (root == NULL)
        return;

    // first recur on left subtree
    Postorder(root->left);

    // then recur on right subtree
    Postorder(root->right);

    // now deal with the node
    cout << root->kisi->ad << ", " << 2020 - root->kisi->yas << ", " << root->kisi->kilo << "  Yigit: ";
    while (root->stack->top != -1)
    {
        char a;
        a = root->stack->pop();
        cout << a << " ";
    }
    cout << endl;
    delete (root->stack);
    delete (root->kisi);
    if (root->left != NULL)
    {
        delete (root->left);
        root->left = NULL;
    }

    if (root->right != NULL)
    {
        delete (root->right);
        root->right = NULL;
    }
}

int Node::getHeight(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int Node::max(int a, int b)
{
    return (a > b) ? a : b;
}

void Node::pushLocation(Node *root, char move, int id)
{
    if (root != NULL)
    {
        if (id == root->id)
        {
            root->stack->push(move);
        }
        pushLocation(root->left, move, id);
        pushLocation(root->right, move, id);
    }
}

void Node::yukseklikAl(Node *root, int dizi[5])
{
    if (root != NULL)
    {
        dizi[root->id] = getLevelUtil(root, root->id, 1);
        yukseklikAl(root->left, dizi);
        yukseklikAl(root->right, dizi);
    }
}

Node::~Node()
{
}
