#include <iostream>
using namespace std;

int maxNumber(int* arr, int size) {
    int maxIndex = 0;
    for(int i = 0; i< size; ++i) {
        maxIndex = (arr[i] > arr[maxIndex]) ? i : maxIndex;
    }
    return arr[maxIndex];
}

void countingSort(int* arr, int size) {
    int maxElement = maxNumber(arr, size);
    int* countingArray = new int[maxElement]();

    for(int i = 0; i< size; ++i) {
        ++countingArray[arr[i]];
    }

    int countingIndex = 0;
    for(int i = 0; i< size; ++i) {
        for(; countingArray[countingIndex] == 0 && countingIndex < maxElement; ++countingIndex);
        arr[i] = countingIndex;
        --countingArray[countingIndex];
    }

    delete [] countingArray;
}

void printArray(int* arr, int size) {
    for(int i = 0; i< size; ++i) {
        cout<< arr[i]<< " ";
    }
    cout<< endl;
}

int main() {
    const int size = 6;
    int arr[] = {13, 34, 1, 12, 837, 23};
    countingSort(arr, size);
    printArray(arr, size);

    return 0;
}
