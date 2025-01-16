/*  This is a custom header file that we created ourselves. 
    For a header file we use the extension .h
    What is a header file? 
        - We declare each element we use here so that we don't have to declare it on every .cpp file.
        - Useful for having a clean and organized code :)
*/

/* These are called preprocessor directives.
    They ensure that a header file is not inserted multiple times */
#ifndef ARRAY_H  // #ifndef checks whether the header file we called ARRAY_H is defined
#define ARRAY_H  // #define defines ARRAY_H, if it is not defined

#include <iostream>  // A C++ header file in standard library that lets us use cin and cout
using namespace std; // A C++ standard namespace that contains the C++ methods

class ArrayList {  // Creating a class called ArrayList.
    // Below are private variables that the user can not access from main().
    // Can only be accessed via public methods/functions
    private:
        int* arr;     // A pointer to our array
        int capacity;  // The max capacity our array can hold
        int size;      // The current size of our array

    // Below are public methods
    public:
        ArrayList(int cap);  // A constructor that initializes the array with capacity of cap.
        ~ArrayList();  // A destructor 

        // below are methods to perform operations on our array
        void insert(int value);  
        void remove(int index);
        int search(int value);
        void display();
};

#endif  // make sure to close the preprocessor directive #ifndef