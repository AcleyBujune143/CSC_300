#include "reserve.h"

int main() {
    BST bst;
    int time;

    cout << "Augumented BST for the Single Runway Landing Reservation Problem" << endl;
    cout << "No two planes should land within 3 minutes of each other" << endl;

    while (true) {
        cout << "Enter landing time in minutes past midnight (or -1 to exit): ";
        cin >> time;
        
        if (time == -1) 
            break;

        if (bst.reserve(time)) {
            bst.insert(bst.root, time);
            cout << "Landing time " << time << " reserved successfully.\n";
        } else {
            cout << "Conflict! Cannot reserve landing time " << time << ".\n";
        }
    }
    cout << endl;
    // Print landing times
    cout << "Reserved landing times (in-order): ";
    bst.inorder(bst.root);
    cout << endl << endl;

    // Count how many planes are scheduled to land at times <= t
    cout << "\nEnter a time to check how many planes are scheduled to land at or before that time: ";
    cin >> time;
    int count = bst.countPlanes(bst.root, time);
    cout << "Number of planes scheduled to land at or before " << time << ": " << count << endl;


    return 0;
}
