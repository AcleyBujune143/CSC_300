#ifndef SQ_H
#define SQ_H

#include <iostream>
using namespace std;

class Stack {
    private:
        int* arr;
        int capacity;
        int top;

    public:
        Stack(int cap);
        ~Stack();

        void push(int value);
        int pop();
        
        int peek();
        bool isEmpty();
        int size();
        void display();

};

class Queue {
    private:
        int* arr;
        int capacity;
        int front;
        int rear;
        int queue_size;

    public:
        Queue(int cap);
        ~Queue();

        void enqueue(int value);
        int dequeue();

        int peek();
        bool isEmpty();
        int size();
        void display();

};

#endif