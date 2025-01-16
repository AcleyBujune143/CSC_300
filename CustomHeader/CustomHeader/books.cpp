#include "books.h"

void addBook(){
    Book book;
    cin>>book.title;
    cin>>book.author;
    cin>>book.year;
    cin.ignore();
}