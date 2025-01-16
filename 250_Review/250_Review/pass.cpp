#include <iostream>

using namespace std;

void passbyVal(int x)
{
    x = x + 3;
    cout << "x is "<< x << endl;
}

void passbyRef(int &x)
{
    x = x + 3;
    cout << "x is "<< x << endl;
}

void passbyPtr(int *x)
{
    *x = *x + 3;
    cout << "x is "<< *x << endl;
}

int main()
{
    int val = 5;

    // passbyVal(val);
    // cout << "val is "<< val << endl;

    // passbyRef(val);
    // cout << "val is "<< val << endl;

    passbyPtr(&val);
    cout << "val is "<< val << endl;

    return 0;
}