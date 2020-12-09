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

bool cstRec( const Node* node, size_t& count, int min, int max )
{
    if ( !node )
        return true;

    // Traverse postorder and save the results first
    bool    bLeft   = cstRec( node->fLeftPtr,   count, min, max );
    bool    bRight  = cstRec( node->fRightPtr,  count, min, max );

    if ( node->fValue >= min && node->fValue <= max && bLeft && bRight )
    {
        ++count;
        return true;
    }

    return false;
}

size_t countSubTrees( const Node* node, int min, int max )
{
    size_t count = 0;
    cstRec( node, count, min, max );
    return count;
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

    const int MIN = 7;
    const int MAX = 13;
    std::cout << "Subtrees count in the range [" << MIN << ", " << MAX << "]: " << countSubTrees( root, MIN, MAX );

    deleteBinaryTree( root );

    return 0;
}
