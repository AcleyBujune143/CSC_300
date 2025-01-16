#include <iostream>
#include <string>

using namespace std;

// Declare a structure
struct Book {
    string title;
    string author;
    int year;
};

int main ()
{
    // Create a book structure called novel1
    Book novel1;
    novel1.title = "title1";
    novel1.author = "author1";
    novel1.year = 2024;

    // Print structure members
    cout << novel1.title << " " << novel1.author << " " << novel1.year << endl;

    return 0;
}