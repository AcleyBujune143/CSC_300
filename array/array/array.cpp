/* This is a C++ file where we define the functions we declared in the header file.
*/

// Include our custom header file.
#include "array.h"

/*  For the methods below, we include the prefix ArrayList:: to let the 
    compiler know that the methods are from the class ArrayList     */

// Constructor definition
ArrayList::ArrayList(int cap) {
    capacity = cap;               // Initializing the capacity
    size = 0;                     // Initializing size to 0
    arr = new int[capacity];      // dynamic memory allocation with the new keyword of an array with a limit of capacity.
}

// Destructor definition
ArrayList::~ArrayList(){
    delete[] arr;             // Freeing the heap memory of arr that we initialized in our constructor
}

// Insert definition
void ArrayList::insert(int value){
    // Check it our array has reached its capacity
    if (size == capacity) {
        cout << "Sorry, list is full. Can't insert" << endl;
        return;
    }
    // Add value at the end of the array
    arr[size++] = value;

}

// Remove definition
void ArrayList::remove(int index) {
    // Check if the index is within bounds of array size
    if (index < 0 || index >= size) {
        cout << "Index is out of bounds" << endl;
        return;
    }
    // Go to index we want to remove, and move the values after that index one step back
    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    // Decrease size of array by 1
    size--;

}

// Search definition
int ArrayList::search(int value){
    // traverse through the array one by one
    for (int i = 0; i < size; i++) {
        // check if value at index i is equal to value we are searching for
        if (arr[i] == value) {
            return i;   // return index if found
        }
    }
    return -1; // return -1 if not found

}

// Display definition
void ArrayList::display() {
    // traverse through the array one by one and print
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

}