#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

void print(const vector<int>& arr) {
    for(int i = 0; i< arr.size(); ++i) {
        cout<< arr[i]<< " ";
    }
    cout<< endl;
}

int main() {
    vector<int> arr {15, 17, -2, 2, 4, 64, 12, 3, 7, 2, 18, 21};

    // map
    vector<int> temp(arr.size());
    std::transform(arr.begin(), arr.end(), temp.begin(), [](int x) { return x*x; });
    print(temp);

    // filter
    vector<int> temp2;
    std::copy_if(arr.begin(), arr.end(), back_inserter(temp2), [](int x) { return x % 2 == 0; });
    print(temp2);

    // reduce
    cout<< std::accumulate(arr.begin(), arr.end(), 0, [](int s, int x) { return s + x;} );
}

