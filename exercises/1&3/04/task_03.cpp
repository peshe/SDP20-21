#include <iostream>
#include <stack>

template <typename T>
class Queue {
public:
    void enqueue(const T& elem) {
        s1.push(elem);
    }

    void dequeue() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        s2.pop();
    }

    const T& first() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }

private:
    std::stack<T> s1, s2;
};

int main() {

    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    std::cout << q.first() << std::endl;
    q.dequeue();

    std::cout << q.first() << std::endl;

    return 0;
}