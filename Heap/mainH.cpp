#include "heap.h"

int main (int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Usage: ./a <filename>" << endl;
        return 1;
    }

    int size = 50;
    string filename = argv[1];

    HEAP heap(size);
    int arr[10] = {2, 5, 9, 3, 7, 6, 11, 8, 10, 1};
    heap.buildH(arr, 10);

    for(int i = 0; i < 10; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file.\n";
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        int command, data, oldD, newD;
        iss >> command;

        switch (command) {
            case 0:
                cout << "Exiting...!\n";
                return 0;
            case 1:
                iss >> data;
                heap.insertH(data);
                cout << "Inserted " << data << endl;
                break;
            case 2:
                heap.deleteMax();
                cout << "Deleted Max"<< endl;
                break;
            case 3:
                iss >> data;
                heap.deleteH(data);
                cout << "Deleted " << data << endl;
                break;
            case 4:
                int max;
                max = heap.peek();
                cout << "Max is " << max << endl;
                break;
            case 5:
                iss >> oldD;
                iss >> newD;
                heap.replace(oldD, newD);
                cout << "Replaced " << oldD << " with " << newD << endl;
                break;
            case 6:
                cout << "Converting Heap" << endl;
                heap.switchMinMax();
                cout << endl;
                break;
            case 7:
                cout << "Heap Sort" << endl;
                heap.heapSort(arr, 10);
                cout << endl;
                break;
            case 8:
                cout << "The Heap looks like:" << endl;
                heap.printHeap(0, 0);
                cout << endl;
                break;

            default:
                cout << "Invalid command." << endl;
        }
    }



    return 0;
}