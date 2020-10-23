#include <iostream>
#include "vector.h"
using namespace std;

int main () {
    Vector<int> v;
    for(int i = 0; i< 15; ++i) {
        v.push_back(i);
    }

    for(Vector<int>::Iterator it = v.begin(); it != v.end(); ++it) {
        cout<< *it<< endl;
    }
    cout<< endl;

    return 0;
}
