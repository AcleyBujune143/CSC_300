#include <iostream>

using namespace std;

int main()
{
    int matrix[2][3] = {  // 2 rows, 3 columns
        {2, 4, 7},
        {3, 9, 0}
    };

    cout << matrix[0][2] << endl; // outputs 7 

    // loop and read the matrix
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }



return 0;
}