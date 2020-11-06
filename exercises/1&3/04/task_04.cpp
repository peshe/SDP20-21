#include <iostream>
#include <queue>

int main() {
    const int PARTICIPANT_CNT = 41;
    const int K = 3; // every 
    std::queue<int> q;
    
    for (size_t i = 1; i <= PARTICIPANT_CNT; i++)
        q.push(i);

    while (q.size() != 2) {

        for (size_t i = 0; i < K - 1; i++) {
            q.push(q.front());
            q.pop();
        }
        q.pop();
    }
    
    std::cout << q.front() << std::endl;
    q.pop();
    std::cout << q.front() << std::endl;

    return 0;
}