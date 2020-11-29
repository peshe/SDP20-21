#include <iostream>
#include "LcRsTree.hpp"

using namespace std;
using namespace fmi::sdp;

int main()
{
    Tree<int> tree;
    int path[] = {-1, -1, -1, -1};

    tree.insert(0, path);


    path[0] = 0;
    tree.insert(1, path);
    tree.insert(2, path);

    tree.print();
    cout << tree.getHeight() << endl;
    cout << boolalpha << tree.find(1) << endl;
    tree.remove(1);
    tree.print();

    tree.insert(1, path);
    tree.print();

    path[0] = 1;
    tree.insert(3, path);
    tree.print();

    path[0] = 0;
    path[1] = 0;
    tree.insert(5, path);
    tree.insert(4, path);
    tree.print();
    tree.printByLevels();

    return 0;
}
