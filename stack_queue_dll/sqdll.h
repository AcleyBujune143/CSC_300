#ifndef SQDLL_H
#define SQDLL_H

#include <iostream>
using namespace std;

struct node{
    int data;
    struct node* next;
    struct node* prev;  // doubly linked list
};


void enqueueFront(node *&head, node *&tail, int value);
void enqueueBack(node *&head, node *&tail, int value);
void dequeueFront(node *&head, node *&tail);
void dequeueBack(node *&head, node *&tail);

void displayList(node *&head);

#endif