#include "ll.h"

void insertNode(node *&head, int index, int data)
{
    node* newNode = new node;
    newNode->data = data;
    newNode->next = nullptr;

    if(index == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        node* walker = head;
        int wIndex = 0;
        while(walker != NULL && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }
        if(walker == nullptr)
        {
            cout << "Index is too large, can't insert" << endl;
            return;
        }
        else
        {
            newNode->next = walker->next;
            walker->next = newNode;
        }

    }
}

void deleteNode(node *&head, int index) 
{
    // Check if the list is empty and there's nothing to delete

        // Write your code here!

    // Check if were are deleting at index 0 and handle accordingly
    if(index == 0)
    {
        // Write your code here!
    }
    // Handle other index deletions
    else
    {
        // Write your code here!
    }
}

void displayList(node *&head) 
{
    node* walker = head;

    while(walker != nullptr)
    {
        cout << walker->data<<" ";
        walker = walker->next;
    }
    cout<<endl;

}

node* searchNode(node *&head, int key) 
{
    node* walker = head;
    while(walker != nullptr && walker->data != key)
    {
        walker = walker->next;
    }
    if(walker == nullptr)
    {
        cout << key << "Not found" << endl;
        return nullptr;
    }
    else
    {
        return walker;
    }

}