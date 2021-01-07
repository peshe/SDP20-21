#include <iostream>
#include <vector>
#include <list>
using namespace std;

struct Hash {
    static const int volume = 10000;
    vector<list<int>> chains;

    Hash() {
        chains.reserve(volume);
        for(int i = 0; i< volume; ++i) {
            chains.push_back(list<int>());
        }
    }

    void add(int number) {
        chains[number % volume].push_back(number);
    }

    bool has(int number) {
        for(list<int>::iterator it = chains[number % volume].begin(); it != chains[number % volume].end(); ++it) {
            if(*it == number) {
                return true;
            }
        }

        return false;
    }
};

void leftDiff(const vector<int>& v1, const vector<int>& v2, vector<int>& result) {
    result.clear();

    Hash h;
    for(vector<int>::const_iterator it = v2.begin(); it != v2.end(); ++it) {
        h.add(*it);
    }

    result.reserve(v1.size());
    for(vector<int>::const_iterator it = v1.begin(); it != v1.end(); ++it) {
        if(!h.has(*it)) {
            result.push_back(*it);
        }
    }
}

bool hasPairWithSum(const vector<int>& v1, const int sum) {

    Hash h;
    for(vector<int>::const_iterator it = v1.begin(); it != v1.end(); ++it) {
        h.add(*it);
    }

    for(vector<int>::const_iterator it = v1.begin(); it != v1.end(); ++it) {
        if((*it)*2 != sum && h.has(sum - *it)) {
            cout<< *it<< " "<< sum - *it<< endl;
            return true;
        }
    }

    return false;
}

int main() {

    Hash h;

    vector<int> v1;
    vector<int> v2;
    vector<int> r;

    for(int i = 0; i< 10; ++i) {
        v1.push_back(i);
        v2.push_back(2*i);
    }

    leftDiff(v1, v2, r);

    for(vector<int>::const_iterator it = r.begin(); it != r.end(); ++it) {
        cout<< *it<< " ";
    }
    cout<< endl;

    cout<< hasPairWithSum(v1, 15);

    return 0;
}
