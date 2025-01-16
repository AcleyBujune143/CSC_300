#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>

using namespace std;

struct reservation {
    int time; // assume time in minutes
    reservation* left;
    reservation* right;

    int subtreeSize; // keep track of subtree size for countPlanes

    reservation(int t);
};

class BST {
    private:
        void clearTree(reservation* node);

    public:
        BST();
        ~BST();    

        reservation* root;
        
        bool reserve(int time);

        // Complete these three function definitions
        bool checkConflict(reservation* node, int time);
        void insert(reservation*& root, int time);
        int countPlanes(reservation* node, int time);
        void inorder(reservation* root);

};

#endif
