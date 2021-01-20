#include <iostream>
#include <vector>

using namespace std;

int firstEvenIndex(const vector<int>& arr) {
    for(int i = 0; i < arr.size(); ++i) {
        if(arr[i] % 2 == 0) {
            return i;
        }
    }

    return -1;
}

int firstDivisibleIndex(const vector<int>& arr, int k) {
    for(int i = 0; i < arr.size(); ++i) {
        if(arr[i] % k == 0) {
            return i;
        }
    }

    return -1;
}

/*
int firstEven(const vector<int>& arr) {
    return firstDivisible(arr, k);
}
*/

int firstIndex(const vector<int>& arr, int k) {
    for(int i = 0; i < arr.size(); ++i) {
        if(arr[i] == k) {
            return i;
        }
    }

    return -1;
}

bool isPrime(int n) {
    n = n<0 ? -n : n;

    for(int i = 2; i*i< n; ++i) {
        if(n % i == 0) {
            return false;
        }
    }

    return true;
}

int firstPrimeIndex(const vector<int>& arr) {
    for(int i = 0; i < arr.size(); ++i) {
        if(isPrime(arr[i])) {
            return i;
        }
    }

    return -1;
}


int main() {
    int n = [] (int x, int y) { return x + y; }(5, 4);
    cout << n << endl;
    cout<< endl<< endl;

    vector<int> arr {15, 17, -2, 2, 4, 64, 12, 3, 7, 2, 18, 21};
    cout<< "first even: "<< firstEvenIndex(arr)<< endl;
    cout<< "first divisible: "<< firstDivisibleIndex(arr, 3)<< endl;
    cout<< "first: "<< firstIndex(arr, 2)<< endl;
    cout<< "first prime: "<< firstPrimeIndex(arr)<< endl;

}
