// https://www.hackerrank.com/challenges/almost-sorted/problem

#include <iostream>
#include <vector>
using namespace std;

bool almostSortedSwap(vector<int>& A);
bool almostSortedReverseSubArray(vector<int>& A);

bool almostSorted(vector<int>& A) {
    return almostSortedReverseSubArray(A) || almostSortedSwap(A);
}

bool almostSortedSwap(vector<int>& A) {
    int index1 = -1;
    int index2 = -1;
    for(int i = 0; i< A.size()-1; ++i) {
        if(A[i] > A[i+1]) {
            for(; A[i-1] == A[i]; --i);
            index1 = i;
            break;
        }
    }

    for(int i = A.size()-1; i>0; --i) {
        if(A[i] < A[i-1]) {
            for(; A[i+1] == A[i]; ++i);
            index2 = i;
            break;
        }
    }

    if(index1 != -1 ^ index2 != -1) {
        return false;
    }

    if(index1 == -1 && index2 == -1) {
        return true;
    }

    return ((index1 == 0 || A[index1-1] <= A[index2]) && (index1 == A.size()-1 || A[index2] <= A[index1+1])
            && (index2 == 0 || A[index2-1] <= A[index1]) && (index2 == A.size()-1 || A[index1] <= A[index2+1]));
}

bool almostSortedReverseSubArray(vector<int>& A) {
    // TODO: fix missed case with unfitting middle array
    int i = 0;
    for(; i< A.size()-1 && A[i] <= A[i+1]; ++i);
    for(; i< A.size()-1 && A[i] >= A[i+1]; ++i);
    for(; i< A.size()-1 && A[i] <= A[i+1]; ++i);
    return i == A.size();
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

    cout<< (almostSorted(arrayWithNumbers) ? "yes" : "no");

    return 0;
}
