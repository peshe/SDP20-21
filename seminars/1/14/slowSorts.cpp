#include <iostream>
using namespace std;

void print(int* arr, int size) {
    for(int i = 0; i< size; ++i) {
        cout<< arr[i]<< " ";
    }
    cout<< endl;
}

void selectionSort(int* arr, int size) {
    for(int i = 0; i< size; ++i) {
        int minIndex = i;
        for(int j = i; j< size; ++j) {
            if(arr[minIndex] > arr[j]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(int* arr, int size) {
    int* temp = new int[size];

    for(int i = 0; i< size; ++i) {
        int j = i;
        for(; j>0 && arr[i] < temp[j-1]; --j) {
            temp[j] = temp[j-1];
        }
        temp[j] = arr[i];
    }

    for(int i = 0; i< size; ++i) {
        arr[i] = temp[i];
    }

    delete [] temp;
}

int main() {

    const int size = 11;
    int arr[] = {34, -23, 56, 18, -23, 1, 3, 4, 55, -1239, 18};

    insertionSort(arr, size);
    print(arr, 11);


    return 0;
}
