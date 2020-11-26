#include <iostream>

struct TreeNode
{
    int         fData;
    TreeNode*   fLeftPtr;
    TreeNode*   fRightPtr;
    TreeNode( int data, TreeNode* left = nullptr, TreeNode* right = nullptr )
        : fData( data )
        , fLeftPtr( left )
        , fRightPtr( right )
    {}
};


// Printing in the Root, Left, Right order
void printTreePreorder( const TreeNode* root )
{
    if ( root )
    {
        std::cout << root->fData << " ";
        printTreePreorder( root->fLeftPtr );
        printTreePreorder( root->fRightPtr );
    }
}


// Printing in the Left, Root, Right order
void printTreeInorder( const TreeNode* root )
{
    if ( root )
    {
        printTreeInorder( root->fLeftPtr );
        std::cout << root->fData << " ";
        printTreeInorder( root->fRightPtr );
    }
}


// Printing in the Left, Right, Root order
void printTreePostorder( const TreeNode* root )
{
    if ( root )
    {
        printTreePostorder( root->fLeftPtr );
        printTreePostorder( root->fRightPtr );
        std::cout << root->fData << " ";
    }
}


// Deleting each node lastly => postorder traversal
void deleteTree( TreeNode*& root )
{
    if ( root )
    {
        deleteTree( root->fLeftPtr );
        deleteTree( root->fRightPtr );
        delete root;
        root = nullptr;
    }
}


int main()
{
    TreeNode* root =
        new TreeNode 
            ( 2
            , new TreeNode 
                ( 3
                , new TreeNode
                    ( 4
                    , nullptr
                    , new TreeNode( 5 )
                    )
                , new TreeNode( 9 )
                )
            , new TreeNode
                ( 6
                , new TreeNode( 7 )
                , new TreeNode( 8 )
                )
            );


    // Note: Pre-, In- and Post- indicate when the root is handled
    std::cout << "Printing the tree where W = Root, A = Left, D = Right (WASD style)";
    std::cout << "\nPreorder  (WAD): ";  printTreePreorder( root );
    std::cout << "\nInorder   (AWD): ";  printTreeInorder( root );
    std::cout << "\nPostorder (ADW): ";  printTreePostorder( root );

    deleteTree( root );
}
