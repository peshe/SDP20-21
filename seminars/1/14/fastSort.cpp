#include <iostream>
#include "minHeap.h"

using namespace std;

void print(int* arr, int size) {
    for(int i = 0; i< size; ++i) {
        cout<< arr[i]<< " ";
    }
    cout<< endl;
}

void heapSort(int* arr, int size) {
    MinHeap<int> sortHeap;
    for(int i = 0; i< size; ++i) {
        sortHeap.push(arr[i]);
    }

    for(int i = 0; i< size; ++i) {
        arr[i] = sortHeap.top();
        sortHeap.pop();
    }
}

int* merge(int* arr1, int s1, int* arr2, int s2, int* result) {
    int* temp = new int[s1 + s2];

    for(int i1 = 0, i2 = 0; i1+i2 < s1+s2;) {
        if(i1 == s1 || i2 == s2) {
            temp[i1+i2] = (i2 == s2) ? arr1[i1++] : arr2[i2++];
            continue;
        }
        temp[i1+i2] = (arr1[i1] < arr2[i2]) ? arr1[i1++] : arr2[i2++];
    }

    for(int i = 0; i< s1+s2; ++i) {
        result[i] = temp[i];
    }

    delete [] temp;

    return result;
}

int* mergeSort(int* arr, int size) {
    if(size == 1) {
        return arr;
    }

    int midIndex = size/2;
    return merge(mergeSort(arr, midIndex), midIndex,
                 mergeSort(arr + midIndex, size - midIndex), size - midIndex,
                 arr);
}

int main() {

    const int size = 11;
    int arr[] = {34, -23, 56, 18, -23, 1, 3, 4, 55, -1239, 18};

    mergeSort(arr, size);
    print(arr, 11);


    return 0;
}
