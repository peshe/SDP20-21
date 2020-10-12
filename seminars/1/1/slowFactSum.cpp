#include <iostream>
using namespace std;

int fact(int n) {
    return (n < 1) ? 1 : n*fact(n-1);
}

int main() {
    int n;
    int sum = 0;
    cin>> n;
    for(int i = 1; i< n+1; ++i) {
        sum += fact(i);
    }
    cout<< sum<< endl;

    return 0;
}
