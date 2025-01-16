#ifndef BOOKS_H
#define BOOKS_H

#include <iostream>
#include <string>

using namespace std;

struct Book{
    string author;
    string title;
    int year;
};

void addBook();

#endif