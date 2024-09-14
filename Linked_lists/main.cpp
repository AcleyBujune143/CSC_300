#include "ll.h"

int main()
{
    node *head = nullptr;
    node *myNode = nullptr;

    int choice, data, index;
    
    do {
        cout << endl;
        cout << "1. Insert a new node" << endl;
        cout << "2. Remove a node" << endl;
        cout << "3. Search for and return a node" << endl;
        cout << "4. Reverse" << endl;
        cout << "5. Exit" << endl << endl;

        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "What value do you want to insert:  ";
                cin >> data;
                cout << "Which index do want to insert at:  ";
                cin >> index;
                insertNode(head, index, data);
                break;
            case 2:
                cout << "Which index do you want to remove:  ";
                cin >> index;
                deleteNode(head, index);
                break;
            case 3:
                cout << "Which value do you want to search:  ";
                cin >> data;
                myNode = searchNode(head, data);
                if(myNode != nullptr)
                {
                    cout << myNode->data << "was found at memory address:  "<< myNode << endl;
                }
                break;
            case 4:
                reverseList(head);
                cout << " The list is reversed"  << endl;
                break;
            case 5:
                cout << "See you" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
        displayList(head);
    } while (choice != 4);


    return 0;
}