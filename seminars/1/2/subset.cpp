#include <iostream>
#include "vector.h"
using namespace std;

template<typename T>
Vector< Vector<T> > subsets(Vector<T> arr) {
    Vector<bool> grayCode;
    for(int i = 0; i< arr.getSize(); ++i) {
        grayCode.push_back(false);
    }

    Vector< Vector<T> > result;
    while(true) {
        result.push_back(subsetWithCode(arr, grayCode));

        int i = grayCode.getSize()-1;
        for(; i >= 0 && grayCode[i] == true; --i) {
            grayCode[i] = false;
        }

        if(i < 0) {
            break;
        }

        grayCode[i] = true;
    }

    return result;
}

template<typename T>
Vector<T> subsetWithCode(Vector<T> arr, Vector<bool> grayCode) {
    Vector<T> result;
    int n = grayCode.getSize()-1;
    for(int i = 0; i< grayCode.getSize(); ++i) {
        if(grayCode[i]) {
            result.push_back(arr[n - i]);
        }
    }
    return result;
}

int main() {
    Vector<int> v;
    for(int i = 0; i< 3; ++i) {
        v.push_back(i);
    }

    Vector< Vector<int> > s = subsets(v);
    for(int i = 0; i< s.getSize(); ++i) {
        s[i].print();
    }
}
