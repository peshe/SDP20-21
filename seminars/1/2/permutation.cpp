
#include <iostream>
#include "vector.h"
using namespace std;

template<typename T>
Vector< Vector<T> > permutations(Vector<T> arr) {
    Vector<int> indexArr;
    for(int i = 0; i< arr.getSize(); ++i) {
        indexArr.push_back(i);
    }

    Vector< Vector<T> > result;
    int i1, i2;
    result.push_back(permutationWithIndices(arr, indexArr));
    while(true) {
        for(i1 = indexArr.getSize() - 2; i1 >= 0 && indexArr[i1] > indexArr[i1+1]; --i1);
        if(i1 < 0) { break; }
        for(i2 = indexArr.getSize() - 1;           indexArr[i1] > indexArr[i2]; --i2);
        indexArr.swap(i1, i2);
        indexArr.reverse(i1 + 1, indexArr.getSize()-1);
        result.push_back(permutationWithIndices(arr, indexArr));
    }

    return result;
}

template<typename T>
Vector<T> permutationWithIndices(Vector<T> arr, Vector<int> indices) {
    Vector<T> result;
    int n = indices.getSize()-1;
    for(int i = 0; i< indices.getSize(); ++i) {
        result.push_back(arr[indices[i]]);
    }
    return result;
}

int main() {
    Vector<int> v;
    for(int i = 0; i< 3; ++i) {
        v.push_back(i*5);
    }

    Vector< Vector<int> > p = permutations(v);
    for(int i = 0; i< p.getSize(); ++i) {
        p[i].print();
    }
}
