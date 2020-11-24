#include <iostream>
#include <vector>
using namespace std;

bool almostSorted(vector<int>& A) {
    return almostSortedSwap(A) || almostSortedReverseSubArray(A);
}

bool almostSortedSwap(vector<int>& A) {
    int index1 = -1;
    int index2 = -1;
    for(int i = 0; i< A.size()-1; ++i) {
        if(!(A[i] < A[i+1])) {
            if(index1 == -1) {
                index1 = i;
                continue;
            }

            if(index2 == -1) {
                index2 == i;
                continue;
            }

            return false;
        }
    }

    if(index1 != -1 && index2 == -1) {
        return false;
    }

    if(index1 != -1 && index2 != -1) {
        return true;
    }

    if(A[i1-1] <= A[i2] && A[i2] <= A[i1+1] && A[i2-1] <= A[i1] && A[i1] <= A[i2+1]) {
        return true;
    }
}

bool almostSortedReverseSubArray(vector<int>& A) {
    return false;
}

int main() {
    int n;
    int newElement;
    vector<int> arrayWithNumbers;
    cin>> n;
    for(int i = 0; i< n; ++i) {
        cin>> newElement;
        arrayWithNumbers.push_back(newElement);
    }

    cout<< almostSorted(arrayWithNumbers) ? "yes" : "no";

    return 0;
}
