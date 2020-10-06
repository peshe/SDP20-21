
#include <iostream>
#include "vector.h"
using namespace std;

template<typename T>
Vector< Vector<T> > combinations(Vector<T> arr, int k) {
    int n = arr.getSize();

    Vector<int> indexArr;
    for(int i = 0; i< k; ++i) {
        indexArr.push_back(i);
    }

    Vector< Vector<T> > result;
    result.push_back(combinationWithIndices(arr, indexArr));
    while(true) {
        int i = k-1;
        for(; i> 0 && indexArr[i] >= n - k + i; --i);
        if(i == 0 && indexArr[0] >= n - k) { break; }
        ++indexArr[i];
        for(int j = i+1; j< k; ++j) {
            indexArr[j] = indexArr[j-1] + 1;
        }
        result.push_back(combinationWithIndices(arr, indexArr));
    }

    return result;
}

template<typename T>
Vector<T> combinationWithIndices(Vector<T> arr, Vector<int> indices) {
    Vector<T> result;
    for(int i = 0; i< indices.getSize(); ++i) {
        result.push_back(arr[indices[i]]);
    }
    return result;
}

int main() {
    Vector<int> v;
    for(int i = 0; i< 5; ++i) {
        v.push_back(i);
    }

    Vector< Vector<int> > c = combinations(v, 3);
    for(int i = 0; i< c.getSize(); ++i) {
        c[i].print();
    }
}
