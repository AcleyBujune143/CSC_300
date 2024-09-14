#include "ll.h"

// void insertNode(node *&head, int index, int data) //I converted this insertNode function into a doubly linked list function
// {
//     //creating a new node and initializing its before and after pointers to null
//     node* newNode = new node;
//     newNode->data = data;
//     newNode->before = nullptr;
//     newNode->after = nullptr;

//     //if we are inserting at the beginning (index 0), the after pointer of the new node will point to the current head
//     if(index == 0){
//         newNode->after = head;
//         // if the current head is not null, the before  pointer of the current head will point to the new node
//         if(head != nullptr){
//             head->before = newNode;
//            }
//         // then the head is made to point to the new node
//         head = newNode;
//     } else {
//         node* walker = head;
//         int wIndex = 0;
//         while(walker != nullptr && wIndex < index-1)
//         {
//             walker = walker->after;
//             wIndex++;
//         }
//         if(walker == nullptr)
//         {
//             cout << "Index is too large, can't insert" << endl;
//             delete  newNode;
//             return;
//         } else {
//             newNode->after = walker->after;
//             if (walker->after != nullptr){
//                 walker->after->before = newNode;
//             }
//             walker->after = newNode;
//             newNode->before = walker;
            
//         }

//     }
// }

void insertNode(node *&head, int index, int data)
{
    node* newNode = new node;
    newNode->data = data;
    newNode->next = nullptr;

    if(index == 0){
        newNode->next = head;
        head = newNode;
    } else {
        node* walker = head;
        int wIndex = 0;
        while(walker != nullptr && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }
        if(walker == nullptr)
        {
            cout << "Index is too large, can't insert" << endl;
            return;
        } else {
            newNode->next = walker->next;
            walker->next = newNode;
        }
    }
}


void deleteNode(node *&head, int index) 
{
    //checking if the list is empty
    if  (head == nullptr) {
        cout << "List is empty, can't delete" << endl;
    }
    //checking if we are deleting at index 0
    else if(index == 0)
    {
        node *temp = head;
        head = head->next;
        delete temp;
    }
    else
    { //habdling other index deletions
        node *walker = head;
        for (int i = 0; i < index - 1; i++)
        {
            walker = walker->next;
            if (walker == nullptr)
            {
                cout << "Index out of bounds" << endl;
                return;
            }
        }
        node *temp =  walker->next;
        walker->next = walker->next->next;
        delete temp;
    }
}

void reverseList (node *&head) {
    //initializing the three pointers to null
    node* prev = nullptr;
    node* current = head;
    node* next = nullptr;
// looping until current becomes nullptr
    while ( current  != nullptr) {
        next = current->next;
        current->next = prev;
        prev  = current;
        current = next;
    }
    head = prev;   //updating the head of the list to point to the new first node stored in  prev


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