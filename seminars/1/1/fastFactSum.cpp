#include <iostream>
using namespace std;

int main() {
    int n;
    int sum = 0;
    int accum = 1;
    cin>> n;
    for(int i = 1; i< n+1; ++i) {
        accum *= i;
        sum += accum;
    }
    cout<< sum<< endl;

    return 0;
}

