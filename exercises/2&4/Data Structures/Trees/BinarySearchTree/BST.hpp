#pragma once
#include <optional>

namespace dsa
{

template<class T>
class BST
{
public:
    using opt_const_ref_wrapper     = std::optional< std::reference_wrapper<const T> >;

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
    BST();
    BST( const BST& other );
    BST& operator=( BST other );
    ~BST();

    void                    insert( const T& elem );
    opt_const_ref_wrapper   find( const T& elem ) const;
    void                    remove( const T& elem );
    void                    print( std::ostream& out = std::cout ) const;

    const T&                getMin() const;
    const T&                getMax() const;

private:
    void                    deleteBranch( Node*& node );
    void                    copyNode( Node*& node, const Node* otherNode );
    void                    insert( Node*& node, const T& elem );
    opt_const_ref_wrapper   find( const Node* node, const T& elem ) const;
    void                    remove( Node*& node, const T& elem );
    void                    print( const Node* node, std::ostream& out = std::cout ) const;

    const T&                getMin( const Node* node ) const;
    const T&                getMax( const Node* node ) const;

private:
    Node* fRoot;
};

}

#include "BST.ipp"
