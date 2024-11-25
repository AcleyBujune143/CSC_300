#include "sorts.h"

using namespace std;

int main() {
    const int n = 100000; 
    int* originalArr = new int[n]; // Dynamically allocate array on the heap
    
    // Create a random list
    for (int i = 0; i < n; i++) {
        originalArr[i] = rand() % 100000;
    }

    // Dynamically allocate arrays for each sort
    int* arrBubble = new int[n];
    int* arrSelection = new int[n];
    int* arrInsertion = new int[n];
    int* arrMerge = new int[n];
    int* arrQuick = new int[n];
    int* arrShell = new int[n];
    int* arrCounting = new int[n];

    // Copy the original array to each one before sorting
    memcpy(arrBubble, originalArr, n * sizeof(int));
    memcpy(arrSelection, originalArr, n * sizeof(int));
    memcpy(arrInsertion, originalArr, n * sizeof(int));
    memcpy(arrMerge, originalArr, n * sizeof(int));
    memcpy(arrQuick, originalArr, n * sizeof(int));
    memcpy(arrShell, originalArr, n * sizeof(int));
    memcpy(arrCounting, originalArr, n * sizeof(int));

    // Time Bubble Sort
    clock_t start = clock();
    bubbleSort(arrBubble, n);
    clock_t end = clock();
    double timeBubble = double(end - start) / CLOCKS_PER_SEC;

    // Time Selection Sort
    start = clock();
    selectionSort(arrSelection, n);
    end = clock();
    double timeSelection = double(end - start) / CLOCKS_PER_SEC;

    // Time Insertion Sort
    start = clock();
    insertionSort(arrInsertion, n);
    end = clock();
    double timeInsertion = double(end - start) / CLOCKS_PER_SEC;

    // Time Merge Sort
    start = clock();
    mergeSort(arrMerge, 0, n - 1);
    end = clock();
    double timeMerge = double(end - start) / CLOCKS_PER_SEC;

    // Time Quick Sort
    start = clock();
    quickSort(arrQuick, 0, n - 1);
    end = clock();
    double timeQuick = double(end - start) / CLOCKS_PER_SEC;

    // Time Shell Sort
    start = clock();
    shellSort(arrShell, n);
    end = clock();
    double timeShell = double(end - start) / CLOCKS_PER_SEC;

    //Time Counting Sort
    start = clock();
    countingSort(arrCounting, n);
    end = clock();
    double timeCounting = double(end - start) / CLOCKS_PER_SEC;


    // Output the time taken by each sort
    cout << "Time taken by Bubble Sort: " << timeBubble << " seconds" << endl;
    cout << "Time taken by Selection Sort: " << timeSelection << " seconds" << endl;
    cout << "Time taken by Insertion Sort: " << timeInsertion << " seconds" << endl;
    cout << "Time taken by Merge Sort: " << timeMerge << " seconds" << endl;
    cout << "Time taken by Quick Sort: " << timeQuick << " seconds" << endl;
    cout << "Time taken by Shell Sort: " << timeShell << " seconds" << endl;
    cout << "Time taken by Counting Sort: " << timeCounting << " seconds"<< endl;



    // After sorting is done, don't forget to free the allocated memory
    delete[] originalArr;
    delete[] arrBubble;
    delete[] arrSelection;
    delete[] arrInsertion;
    delete[] arrMerge;
    delete[] arrQuick;
    delete[] arrShell;
    delete[] arrCounting;


    return 0;
}
