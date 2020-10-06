#include <iostream>
#include "vector.h"
using namespace std;

int main () {
    Vector<int> v;
    for(int i = 0; i< 15; ++i) {
        v.push_back(i);
    }
    Vector<int> v2(v);
    for(int i = 0; i< 5; ++i) {
        v2.pop_back();
    }
    v2.insert(15, 3);
    v2.insert(25, 3);
    v2.insert(35, 3);
    v2.delete_at(2);
    v2.print();

    int v2Index = v2.findElement(25);
    if(v2Index != -1) {
        cout<< v2Index<< " "<< v2[v2Index]<< endl;
    }
    v2Index = v2.findElement(24);
    cout<< v2Index<< endl;

    v2.reverse(0, v2.getSize()-1);
    v2.print();

    return 0;
}
