#include "sq.h"

/* 
=================================> STACK <=============================================================
*/ 

Stack::Stack(int cap){
    capacity = cap;
    arr = new int[capacity];
    top = -1;
}

Stack::~Stack()
{
    delete[] arr;
}

void Stack::push(int value) {
    if (top >= capacity){
        cout << "Stack overflow" << endl;
        return;
    }
    top++;
    arr[top] = value;

}

int Stack::pop() {
    if (isEmpty()){
        cout << "Stack underflow" << endl;
        return -1;
    }
    int popped = arr[top--];

    return popped;

}

int Stack::peek() {
    if(isEmpty()){
        cout << " Stack is empty" << endl;
        return -1;
    }

    return arr[top];
}


bool Stack::isEmpty() {
    return top == -1;

}

int Stack::size() {
    return top + 1;
}

void Stack::display() {
    if(isEmpty()){
        cout<< "Stack is empty" << endl;
        return;
    }
    cout << "Stack elements" << endl;
    for(int i = top; i >= 0; i--){
        cout << arr[i] << endl;
    }
    cout << endl;
}

/* 
=================================> QUEUE <=============================================================
*/ 

Queue::Queue(int cap) {
    capacity = cap;
    arr = new int[capacity];
    front = 0;
    rear = -1;
    queue_size = 0;
}

Queue::~Queue() {
    delete[] arr;
}


void Queue::enqueue(int value) {
    if (queue_size >= capacity){
        cout << "Queue overflow" << endl;
        return;
    }
    arr[++rear] = value;
    queue_size++;

}

int Queue::dequeue() {
    if(isEmpty()){
        cout << "Queue underflow" << endl;
        return -1;
    }
    int dequeued = arr[front];
    front++;
    queue_size--;

    return dequeued;
}

int Queue::peek() {
    if(isEmpty()){
        cout << "Queue is empty" << endl;
        return -1;
    }
    return arr[front];
}


bool Queue::isEmpty() {
    return queue_size == 0;
}

int Queue::size() {
    return queue_size;
}

void Queue::display() {
    if(isEmpty()){
        cout << "Queue is empty" << endl;
        return;
    }
    cout << "Queue elememts" << endl;
    for (int i = front; i <= rear; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}