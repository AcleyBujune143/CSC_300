#include <iostream>
#include <fstream>  // Include this to handle file input/output

using namespace std;


int main() {
    // Create and open a text file
    ofstream myFile("filename.txt");  

    // Write to the file
    if (myFile.is_open()) {
        myFile << "Hello, this is a test file.\n";
        myFile << "It contains two lines of text.\n";
       
    } else { myFile.close();  // Close the file when done
        cout << "File written successfully.\n";
        cout << "Unable to open the file for writing.\n";
    }

    // 2. Reading from the file
    ifstream inFile("filename.txt");  // Open the file for reading
    string line;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {  // Read the file line by line
            cout << line << '\n';  // Print each line to the console
        }
        inFile.close();  // Close the file when done
    } else {
        cout << "Unable to open the file for reading.\n";
    }

    return 0;
}
