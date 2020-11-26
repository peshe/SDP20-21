#pragma once
#include <iostream>
#include <optional>

namespace dsa
{

template<class T>
class BST
{
private:
    struct Node
    {
        T       fData;
        Node*   fLeftPtr;
        Node*   fRightPtr;
        Node( const T& data )
            : fData( data )
            , fLeftPtr( nullptr )
            , fRightPtr( nullptr )
        {}
    };

public:
    using opt_const_ref_wrapper = std::optional< std::reference_wrapper<const T> >;

public:
    BST();
    BST( const BST& other );
    BST& operator=( BST other );
    ~BST();

    void                        insert( const T& elem );
    bool                        tryInsert( const T& elem );
    opt_const_ref_wrapper       find( const T& elem ) const;
    bool                        erase( const T& elem );
    void                        print( std::ostream& out = std::cout ) const;

    const T&                    min() const;
    const T&                    max() const;

private:
    void                        deleteBranch( Node*& node );
    void                        copyBranch( Node*& node, const Node* otherNode );

    void                        insertRec( Node*& node, const T& elem );
    bool                        tryInsertRec( Node*& node, const T& elem );
    opt_const_ref_wrapper       findRec( const Node* node, const T& elem ) const;
    bool                        eraseRec( Node*& node, const T& elem );
    void                        printRec( const Node* node, std::ostream& out = std::cout ) const;

    Node*&                      minRec( Node*& node ) const;
    Node*&                      maxRec( Node*& node ) const;

private:
    Node*                       fRoot;
};

}

#include "BinarySearchTree.ipp"
