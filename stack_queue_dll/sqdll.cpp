#include "sqdll.h"

void enqueueFront(node *&head, node *&tail, int value)
{
    // Create the node to be inserted at the front
    node *newNode = new node;
    newNode->data = value;
    newNode->next = head;     // newNode points to first element in the list
    newNode->prev = nullptr;  // no prior elements befor newNode

    // If the dequeue is emtpty, then newNode also becomes both the head and the tail
    if (head == nullptr){
        head = tail = newNode;
    }
    else { // If not empty, just make newNode the head
        head->prev = newNode;
        head = newNode;
    }
}

void enqueueBack(node *&head, node *&tail, int value)
{
    // Create the node to be inserted at the back [modigy next and prev pointer accordingly]
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;  // newNode points to no next element
    newNode->prev = tail;     // newNode points to last element in the list

    // Check if dequeue is empty, then newNode is both the head and the tail.
    if (head == nullptr){
        head = tail = newNode;
    }
    // Else insert at the end
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

void dequeueFront(node *&head, node *&tail)
{
    // Check if deque is empty - nothing to dequeue
    if (head == nullptr){
        cout << "Dequeue is empty - nothing to dequeue" << endl;
    }
    // Ajust the pointers for the new head and delete original head
    else {
        node *dltTemp = head;
        head = head->next;

        if  (head == nullptr){ // If head is now nullptr, then tail is also nullptr
            tail = nullptr;
        }
        else {
            head->prev = nullptr; // No prior element before head
        }
        delete  dltTemp; // Delete the original head
    }
}

void dequeueBack(node *&head, node *&tail)
{
    // Check if deque is empty - nothing to dequeue
    if (head == nullptr){
        cout << "Dequeue is empty - nothing to dequeue" << endl;
    }
    // Adjust the pointers for the new tail delete the original tail
    else {
        node *dltTemp = tail;
        tail = tail->prev;

        if (tail ==  nullptr){ // If tail is now nullptr, then head is also nullptr
            head = nullptr;
        }
        else {
            tail->next = nullptr; // No next element after tail
        }
        delete dltTemp; // Delete the original tail
    }
}

void displayList(node *&head)
{
    node *walker = head;

    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker -> next;
    }
    cout << endl;
}
