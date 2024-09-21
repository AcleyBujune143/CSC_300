#include "sqdll.h"

int main()
{
    node *head = nullptr;
    node *tail = nullptr; // also keep track of the tail
    int choice, data;

    do {
        cout << endl;
        cout << "1) Deque - Enqueue Front" << endl;
        cout << "2) Deque - Enqueue Back" << endl;
        cout << "3) Deque - Dequeue Front" << endl;
        cout << "4) Deque - Dequeue Back" << endl;
        cout << "5) Exit" << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to add at the front:  ";
            cin >> data;
            enqueueFront(head, tail, data);
            break;
        case 2:
            cout << "Enter value to add at the back:  ";
            cin >> data;
            enqueueBack(head, tail, data);
            break;
        case 3:
            dequeueFront(head, tail);
            break;
        case 4:
            dequeueBack(head, tail);
            break;
        case 5:
            cout << "See you!" << endl;
            break;
        default:
            cout <<"Invalid choice" << endl;
            break;
        }
        displayList(head);

    }while(choice != 5);
    return 0;

}