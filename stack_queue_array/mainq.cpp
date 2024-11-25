#include "sq.h"

int main(){
    int choice, data, size, top;
    bool empty;

    Queue queue(5);

    do {
        cout << endl;
        cout << "Queue Implementation using arrays :)" << endl;
        cout << "1. Enqueue" << endl;
        cout << "2. Dequeue" << endl;
        cout << "3. Peek" << endl;
        cout << "4. IsEmpty" << endl;
        cout << "5. Size" << endl;
        cout << "6. Exit" << endl;
        cout << endl;

        // Get the choice from the user
        cin >> choice;

        // Use a switch statement to select which one to execute based on user choice
        switch(choice)
        {
            case 1:
                cout << "What value do you want to enqueue:  ";
                cin >> data;
                queue.enqueue(data);
                break;
            case 2:
                queue.dequeue();
                break;
            case 3:
                top = queue.peek();
                cout << "First of queue is: "<< top << endl;
            case 4:
                empty = queue.isEmpty();
                cout << "Is Empty:  " << (empty ? "Yes" : "No") << endl;
                break;
            case 5:
                size = queue.size();
                cout << "Queue size is: "<< size << endl;
                break;
            case 6:
                cout << "See you" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
        queue.display();
    } while (choice != 6);

    return 0;
}