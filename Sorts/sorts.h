#ifndef S_H
#define S_H

#include <iostream>
#include <ctime>  // For timing
#include <cstdlib>
#include <cstring> // for memcpy

using namespace std;
 
void swap(int& a, int& b);


void bubbleSort(int arr[], int n);
void optimizedBubbleSort(int arr[], int n);

void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);

void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);

int partition(int arr[], int low, int high); 
void quickSort(int arr[], int low, int high); 

void shellSort(int arr[], int n);

void countingSort(int arr[], int n);

void printArray(int arr[], int size);

#endif