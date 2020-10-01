#include <iostream>
using namespace std;

/*int sumTo(int n) {
    return (n > 0) ? (n + sumTo(n-1)) : 0;
}*/

int main() {
    int n;
    cin>> n;

    int accum = 0;
    int res = 0;
    for(int i = 0; i< n; ++i) {
        accum += i;
        res += accum;
        //cout<< sumTo(i)<< " ";
    }
    cout<< res;
    cout<< endl;

    return 0;
}
