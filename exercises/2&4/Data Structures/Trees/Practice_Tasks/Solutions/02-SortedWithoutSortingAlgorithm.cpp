#include <iostream>
#include <set>

int main()
{
    size_t count;
    std::cin >> count;

    std::set<int> redBlackTree;
    int curr;
    for ( size_t i = 0; i < count; i++ )    // O(n)
    {
        std::cin >> curr;
        redBlackTree.insert( curr );        // O(log(n))
    }

    for ( int num : redBlackTree )          // O(n)
        std::cout << num << " ";

    // O(n) * O(log(n)) + O(n)
    // Gives us a total time complexity of: O(n*log(n))

    return 0;
}
