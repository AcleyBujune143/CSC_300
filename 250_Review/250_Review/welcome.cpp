// VS code snippet

#include <iostream>
#include <string>

using namespace std;

// This is a single line comment

/* This is a multi-line comment
line 1
line 2
line 3*/


int main()
{
    string name;

    cout << "Who are you? ";
    cin >> name;
    cout <<"Welcome to \"CSC 300\" " << name << "!" << endl;   // endl for new line or use \n
    cout <<" \t This is week 1."; // \t inserts tab

    return 0;
}
