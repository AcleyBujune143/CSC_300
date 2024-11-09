#include "reserve.h"

reservation::reservation(int t) {
    time = t;
    left = nullptr;
    right = nullptr; 
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(reservation* node)
{
    if (root == nullptr)
        return;

    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// reserve new landing time
bool BST::reserve(int time) 
{
    if (checkConflict(root, time)) {
        return false; // conflict - reservation fails
    }
 
    insert(root, time); 
    return true; // no conflict - reservation successful
}

// check for landing time conflicts within 3 minutes (Use recursion)
bool BST::checkConflict(reservation* node, int time) 
{
    if (node == nullptr) {
        return false; // no conflict
    }
    //chacking if the current node is within the 3-minute range
    if ((node->time <= time + 3) &&  (node->time >= time - 3)) {
        return true; // conflict
    }

    //recurring on left or right subtree depending on time
    if (time < node->time) {
        return checkConflict(node->left, time);
    } else {
        return checkConflict(node->right, time);
    }
 
}

// insert new reservation and update subtree size (make sure to avoid inserting duplicates)
void BST::insert(reservation*& node, int time) 
{
    // same as before - just make sure to update subtree size for inserted node
    if (node == nullptr) {
        node = new reservation(time);
        node->subtreeSize = 1;
        return;
    }
    if (time == node->time) {
        return; // duplicate - do nothing
    }

    if (time < node->time) {
        insert(node->left, time);
    } else {
        insert(node->right, time);
    }
    node->subtreeSize = 1;
    if (node->left) node->subtreeSize += node->left->subtreeSize;
    if  (node->right) node->subtreeSize += node->right->subtreeSize;
}

// Count nodes with times <= t
int BST::countPlanes(reservation* node, int t) 
{
    if (node == nullptr) {
        return 0;
    }
    if (t == node->time) {
        //left subtree + current node
        return (node->left ? node->left->subtreeSize : 0) + 1;
    } else if  (t < node->time) {
        //only left subtree
        return countPlanes(node->left, t);
    } else {
        //count left subtree + current node +  right subtree

        return (node->left ? node->left->subtreeSize : 0) + 1
        + countPlanes(node->right, t);
    }
}

void BST::inorder(reservation* root)
{
    if (root == nullptr)
        return;
    
    inorder(root->left);
    cout << root->time << " ";
    inorder(root->right);
}