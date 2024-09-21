#include "sqll.h"

int main()
{
    node *head = nullptr;
    int choice, data;

    do {
        cout << endl;
        cout << "1) Stack - Push" << endl;
        cout << "2) Stack - Pop" << endl;
        cout << "3) Queue - Enqueue" << endl;
        cout << "4) Queue - Dequeue" << endl;
        cout << "5) Exit" << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to push:  ";
            cin >> data;
            push(head, data);
            break;
        case 2:
            pop(head);
            break;
        case 3:
            cout << "Enter value to enqueue:  ";
            cin >> data;
            enqueue(head, data);
            break;
        case 4:
            dequeue(head);
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