#include <iostream>
using namespace std;

void print(int* arr, int size) {
    for(int i = 0; i< size; ++i) {
        cout<< arr[i]<< " ";
    }
    cout<< endl;
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

    delete temp;

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

int binarySearch(int arr[], int p, int r, int num) {
   if (p <= r) {
      int mid = (p + r)/2;
    if (arr[mid] == num)
      return mid ;
    if (arr[mid] > num)
      return binarySearch(arr, p, mid-1, num);
    if (arr[mid] < num)
      return binarySearch(arr, mid+1, r, num);
   }
   return -1;
}

void leftDiff(int* arr1, int s1, int* arr2, int s2, int* result, int& resSize) {

    mergeSort(arr2, s2);

    resSize = 0;
    for(int i = 0; i< s1; ++i) {
        if(binarySearch(arr2, 0, s2-1, arr1[i]) == -1) {
            result[resSize++] = arr1[i];
        }
    }
}

void leftDiff2(int* arr1, int s1, int* arr2, int s2, int* result, int& resSize) {

    mergeSort(arr1, s1);
    mergeSort(arr2, s2);

    resSize = 0;
    for(int i1 = 0, i2 = 0; i1 < s1; ++i1) {
        for(; arr1[i1] > arr2[i2]; ++i2);
        if(arr1[i1] != arr2[i2++]) {
            result[resSize++] = arr1[i1];
        }
    }
}

int main() {

    const int s1 = 7;
    const int s2 = 8;

    int arr1[] = {1, 2, 3, 123, 43, 23, -23};
    int arr2[] = {14, 6, 17, 9, -12, 5, 2, 43};
    int res[s1];

    int resSize;
    leftDiff(arr1, s1, arr2, s2, res, resSize);
    print(res, resSize);

    return 0;
}
