#include <iostream>
#include <vector>

struct Node
{
    int     fValue;
    Node*   fLeftPtr;
    Node*   fRightPtr;

    Node( int value, Node* left = nullptr, Node* right = nullptr )
        : fValue( value )
        , fLeftPtr( left )
        , fRightPtr( right )
    {}
};

int minOfBinaryTree( const Node* root )
{
    if ( !root->fLeftPtr )
        return root->fValue;

    minOfBinaryTree( root->fLeftPtr );
}

int maxOfBinaryTree( const Node* root )
{
    if ( !root->fRightPtr )
        return root->fValue;

    maxOfBinaryTree( root->fRightPtr );
}

bool areAllValuesInRange( const Node* root, int min, int max )
{
    return minOfBinaryTree( root ) >= min && maxOfBinaryTree( root ) <= max;
}

void deleteBinaryTree( const Node* root )
{
    if ( root )
    {
        deleteBinaryTree( root->fLeftPtr );
        deleteBinaryTree( root->fRightPtr );
        delete root;
    }
}


int main()
{
    Node* root =          
    new Node ( 10,                                            
        new Node ( 5,                                         
            new Node ( 2,                                     
                new Node( 1 ),
                new Node( 3 )
            ),                      /**             10           **/
            new Node ( 8,           /**           /    \         **/
                new Node( 7 ),      /**         /        \       **/
                new Node( 9 )       /**        5         15      **/
            )                       /**      /   \      /  \     **/
        ),                          /**     2     8    12  20    **/
        new Node ( 15,              /**    / \   / \    \        **/
            new Node( 12,           /**   1   3 7   9    13      **/
                nullptr,
                new Node( 13 )
            ),
            new Node( 20 )
        )
    );

    const int MIN1 = 7;
    const int MAX1 = 13;
    std::cout << "Are all values in the range [" << MIN1 << ", " << MAX1 << "]: " << areAllValuesInRange( root, MIN1, MAX1 ) << "\n";

    const int MIN2 = 0;
    const int MAX2 = 25;
    std::cout << "Are all values in the range [" << MIN2 << ", " << MAX2 << "]: " << areAllValuesInRange( root, MIN2, MAX2 );

    deleteBinaryTree( root );

    return 0;
}
