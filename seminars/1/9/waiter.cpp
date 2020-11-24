// https://www.hackerrank.com/challenges/waiter/problem

#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
using namespace std;

vector<int> firstPrimes(int N) {
    vector<bool> primes;
    int maxNumber = ((N> 5) ? round(N*log(N) + N*log(log(N))) : 12);
    primes.reserve(maxNumber);
    for(int i = 0; i< maxNumber; ++i) {
        primes[i] = true;
    }
    primes[0] = primes[1] = false;

    for(int i = 2; i*i < maxNumber; ++i) {
        for(int j = i*i; j < maxNumber; j+=i) {
            primes[j] = false;
        }
    }

    vector<int> firstPrimes;
    firstPrimes.reserve(N);
    for(int i = 0; i< maxNumber && firstPrimes.size()< N; ++i) {
        if(primes[i]) {
            firstPrimes.push_back(i);
        }
    }

    return firstPrimes;
}

void waiter(vector<int>& A0, int N, int Q) {
    stack<int> A;
    stack<int> A2;
    vector<stack<int>> B;
    B.reserve(Q);
    vector<int> primes = firstPrimes(Q);

    for(int i = 0; i< A0.size(); ++i) {
        A.push(A0[i]);
    }

    for(int i = 0; i< Q; ++i) {
        B.push_back(stack<int>());
        for(int plateNumber = A.top(); !A.empty(); A.pop()) {
            plateNumber = A.top();
            if(plateNumber % primes[i] == 0) {
                B[i].push(plateNumber);
            } else {
                A2.push(plateNumber);
            }
        }
        A.swap(A2);
    }

    for(int i = 0; i< Q; ++i) {
        cout<< endl<< i+1<< ": ";
        if(B[i].empty()) {
            continue;
        }
        for(int plateNumber = B[i].top(); !B[i].empty(); B[i].pop()) {
            plateNumber = B[i].top();
            cout<< plateNumber<< " ";
        }
    }

    if(A.empty()) {
        return;
    }
    cout<< endl<< "A: ";
    for(int plateNumber = A.top(); !A.empty(); A.pop()) {
        plateNumber = A.top();
        cout<< plateNumber<< " ";
    }
}

int main () {
    int N;
    int Q;
    vector<int> A0;

    cin>> N>> Q;
    A0.reserve(N);
    int plateNumber;
    for(int i = 0; i< N; ++i) {
        cin>> plateNumber;
        A0.push_back(plateNumber);
    }
    waiter(A0, N, Q);

    return 0;
}
