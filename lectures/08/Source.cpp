#include <iostream>
#include "BST.hpp"

using fmi::sdp::BST;
using std::cout;
using std::endl;

int main()
{
    BST<int> tree;
    int data[] = { 4, 1, 7, 0, 2, 3, 5, 6, 8, 9 };
    for (int i = 0; i < 10; ++i)
        tree.insert(data[i]);
    cout << tree.getHeight() << endl;
    cout << tree.getSize() << endl;
    cout << tree.isBalanced() << endl;
    cout << tree.isPerfectlyBalanced() << endl;

    for (int i = -2; i < 13; ++i)
        cout << tree.find(i) << " ";
    cout << endl;

    {
        BST<int> t2 = tree;
        t2.remove(4);
        t2.printInorder();
        t2 = tree;
        t2.printInorder();
        for (int i = -3; i < 13; ++i) {
            t2.remove(i);
            t2.printInorder();
        }
        t2 = tree;
    }

    tree.printInorder();
    return 0;
}
