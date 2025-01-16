#include "sqll.h"

void push(node *&head, int value)
{
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;

    // INSERT AT INDEX 0
    newNode->next = head;
    head = newNode;
}

void pop(node *&head)
{
    if(head == nullptr){
        cout << "Stack is empty, nothing to pop" << endl;
        return;
    }

    // remove the head
    node *dltTemp = head;
    head = head->next;

    delete dltTemp;

}

void enqueue(node *&head, int value) // add at the end
{
    // create new node to insert
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;
    // check it queue is empty -> new node becomes the head
    if (head == nullptr) 
    {
        head = newNode;
    }
    // walker to walk to the end -> add my new node
    else
    {
        node *walker = head;
        while (walker->next != nullptr)
        {
            walker = walker->next;
            
        }
        walker->next = newNode; //new node
    }
        
}
void dequeue(node *&head) 
{
    // check if empty -> can't dequeue
    if (head == nullptr) 
    {
        cout << "Queue is empty, nothing to dequeue" << endl;
    }
    // dltTemp, make the 2nd element the new head
    else
    {    
        node *dltTemp = head;
        head = head->next;
        delete dltTemp; // delete head
    }
}

void displayList(node *&head)
{
    node *walker = head;

    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker->next;
    }
    cout << endl;
}