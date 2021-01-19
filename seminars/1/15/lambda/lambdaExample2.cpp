#include <iostream>
#include <vector>
#include <functional>

using namespace std;

bool isPrime(int n) {
    n = n<0 ? -n : n;

    for(int i = 2; i*i< n; ++i) {
        if(n % i == 0) {
            return false;
        }
    }

    return true;
}

int firstIndex(const vector<int>& arr, std::function<bool(int)> predicate) {
    for(int i = 0; i < arr.size(); ++i) {
        if(predicate(arr[i])) {
            return i;
        }
    }

    return -1;
}

int main() {
    vector<int> arr {15, 17, -2, 2, 4, 64, 12, 3, 7, 2, 18, 21};
    auto even = [] (int n) { return n % 2 == 0; };
    cout<< "first even: "<< firstIndex(arr, even)<< endl;
    cout<< "first divisible: "<< firstIndex(arr, [] (int n) { return n % 3 == 0; })<< endl;
    cout<< "first: "<< firstIndex(arr, [] (int n) { return n == 2; })<< endl;
    cout<< "first prime: "<< firstIndex(arr, isPrime)<< endl;

}

