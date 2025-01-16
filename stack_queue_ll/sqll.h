#ifndef SQLL_H
#define SQLL_H

#include <iostream>
using namespace std;

struct node{
    int data;
    struct node* next;
};

void push(node *&head, int value);
void pop(node *&head);

void enqueue(node *&head, int value);
void dequeue(node *&head);

void displayList(node *&head);

#endif