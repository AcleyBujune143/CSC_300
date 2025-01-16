#ifndef BSTP_H
#define BSTP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct node
{
    int data;
    struct node* leftChild;
    struct node* rightChild;

    node(int value);
};

class BST {
    public:
        node* root;

        BST();
        ~BST();
        void clearTree(node* node);

        void insertNode(node*& root, int data);     // pass by reference
        node* searchNode(node*& root, int data);
        void deleteNode(node*& root, int data);

        int smallNode(node* root);  // pass by value
        int largeNode(node* root);

        void preorder(node* root);
        void inorder(node* root);
        void postorder(node* root);

        void printTree(node* root, int space);

};

#endif