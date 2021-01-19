#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Person {
    string name;
    int age;

    Person(string name, int age) : name(name), age(age) {}
    void print(ostream& out) const {
        out<< name<< " " << age<< endl;
    }

    bool operator<(const Person& other) const {
        if(age != other.age) {
            return age< other.age;
        }

        return name < other.name;
    }
};

ostream& operator<<(ostream& out, const Person& p) {
    p.print(out);
    return out;
}

int maxAge(Person arr[], int n) {
    int maxAgeIndex = 0;
    for(int i = 0; i< n; ++i) {
        maxAgeIndex = (arr[i].age > arr[maxAgeIndex].age) ? i : maxAgeIndex;
    }

    return arr[maxAgeIndex].age;
}

void bucketSort(Person arr[], int n)
{
    // 1) Create n empty buckets
    int bucketCount = maxAge(arr, n);
    vector< vector<Person> > b(bucketCount+1);

    // 2) Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        cout<< arr[i];
        b[arr[i].age].push_back(arr[i]);
    }

    // 3) Sort individual buckets
    //for (int i = 0; i < bucketCount; i++)
    //    sort(b[i].begin(), b[i].end());

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < bucketCount+1; i++)
        for (int j = 0; j < b[i].size(); j++)
            arr[index++] = b[i][j];
}

int main()
{
    Person arr[] = {
        Person("pesho", 12),
        Person("zucc", 23),
        Person("tosho", 73),
        Person("ivan", 12),
        Person("georgi", 34),
        Person("stilian", 23),
        Person("petar", 34)
    };
    int n = sizeof(arr) / sizeof(arr[0]);
    bucketSort(arr, n);

    cout << "Sorted array is \n";
    for (int i = 0; i < n; i++)
        cout << arr[i];
    return 0;
}
