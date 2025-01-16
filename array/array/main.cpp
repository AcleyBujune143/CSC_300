/* This is our main C++ file */

// include our custom header
#include "array.h"

int main(){
    int choice, data, index;
    int found;

    // Create an instance of the class ArrayList (aka object) called array.
    // Initialize array capacity to 10 (Remember our constructor!)
    ArrayList array(10);

    // Use a do-while loop to print out the choice menu
    do {
        cout << endl;
        cout << "Array Implementation of Lists :)" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Remove" << endl;
        cout << "3. Search" << endl;
        cout << "4. Display" << endl;
        cout << "5. Exit" << endl;
        cout << endl;

        // Get the choice from the user
        cin >> choice;

        // Use a switch statement to select which one to execute based on user choice
        switch(choice)
        {
            case 1:
                cout << "What value do you want to insert:  ";
                cin >> data;
                array.insert(data);
                break;
            case 2:
                cout << "Which index do you want to remove:  ";
                cin >> index;
                array.remove(index);
                break;
            case 3:
                cout << "Which value do you want to search:  ";
                cin >> data;
                found = array.search(data);
                cout << "Found at:  " << found;
                break;
            case 4:
                array.display();
                break;
            case 5:
                cout << "See you" << endl;
                break;
            // default executes if a user enters a choice other that 1-5
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 5); // continues to loop until the user chooses 5

    return 0;
}