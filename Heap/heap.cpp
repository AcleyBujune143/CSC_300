#include "heap.h"

HEAP::HEAP(int size) {
    capacity = size;
    heapSize = 0;
    array = new int[capacity];
}

HEAP::~HEAP() {
    delete[] array;
}

int HEAP::leftChild(int index) {
    return 2*index + 1;
}
int HEAP::rightChild(int index) {
    return 2*index + 2;
}
int HEAP::parent(int index) {
    return (index - 1) / 2;
}

void HEAP::insertH(int data) {
    if (heapSize == capacity) {
        cout << "Heap overflow - can't insert"<< endl;
        return;
    }

    array[heapSize] = data;
    heapifyUp(heapSize);
    heapSize++;
}

void HEAP::heapifyUp(int index) {
    while(index != 0 && array[parent(index)] < array[index]) {
        swap(array[parent(index)], array[index]);
        index = parent(index);
    }
}

int HEAP::peek() {
    if (heapSize <= 0) {
        cout << "Heap is empty" << endl;
        return -1;
    }

    return array[0];
}

void HEAP::deleteMax() {
    if (heapSize <= 0) {
        cout << "Heap is empty - nothing to delete" << endl;
        return;
    }

    if (heapSize == 1) {
        heapSize--;
        return;
    }

    array[0] = array[heapSize - 1];
    heapSize--;

    heapifyDown(0);
}

void HEAP::deleteH(int data) {
    int index = -1;

    // search for data - linear search :( O(n)
    for (int i = 0; i < heapSize; i++) {
        if (array[i] == data) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element not found - can't delete"  << endl;
        return;
    }

    array[index] = array[heapSize - 1];
    heapSize--;

    heapifyDown(index);
}


void HEAP::heapifyDown(int index) 
{
    // complete this
    while (index < heapSize) {
        int largest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < heapSize && array[left] > array[largest]) {
            largest = left;
        }
        if (right < heapSize && array[right] > array[largest]) {
            largest = right;
        }
        if (largest != index) {
            swap(array[index], array[largest]);
            index = largest;
        } else {
            break;
        }
    }

}

 
void HEAP::buildH(int arr[], int n) 
{
    // complete this
    for (int i = 0; i < n; i++) {
        array[i] = arr[i];
    }
    heapSize = n;

    //starting from the last non-leaf node and heapifying down
    for ( int i = (heapSize / 2) - 1; i >= 0; i-- ) {
        heapifyDown(i);
    }
}

void HEAP::replace(int oldData, int newData)
{
    // complete this
    int index = -1;
    //finding the index of oldData in the array
    for (int i = 0; i < heapSize; i++) {
        if (array[i] == oldData) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "oldData not found - can't replace!!" << endl;
        return;
    }

    array[index] = newData;

    //deciding whether to heapify up or down
    if (newData > oldData) {
        heapifyUp(index);
    } else {
        heapifyDown(index);
    }
}

void HEAP::heapSort(int arr[], int n)
{
    // complete this
    cout <<"Original array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    //building a heap from the array
    buildH(arr, n);

    cout <<"After building the max heap: ";
    for (int i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    //extracting elements from the heap one by one
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = array[0];  //max element at the root
        array[0] = array[heapSize - 1];  //moving the last element to the root
        heapSize--;
        heapifyDown(0); //heapifying the reduced heap
    }
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void HEAP::printHeap(int index, int depth) {
    if (index >= heapSize)
        return;

    printHeap(rightChild(index), depth + 1);

    for (int i = 0; i < depth; i++) {
        cout << "  "; // indentation based on depth
    }

    cout << abs(array[index]) << endl;

    printHeap(leftChild(index), depth + 1);
}

void HEAP::switchMinMax() {
    //rebuilding the heap using min heap property
    for (int i = (heapSize / 2) - 1; i >= 0; i--) {
        heapifyDownMin(i);
    }
}

void HEAP::heapifyDownMin(int index) {
    while (index < heapSize) {
        int smallest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        //finding the smallest among root, left child and right child
        if (left < heapSize && array[left] < array[smallest]) {
            smallest = left;
        }
        if (right < heapSize && array[right] < array[smallest]) {
            smallest = right;
        }
        if (smallest != index) {
            swap(array[index], array[smallest]);  //swapping the elements
            index = smallest;
        } else {
            break; //if the smallest is the root, the heap is already valid
        }
    }
}
