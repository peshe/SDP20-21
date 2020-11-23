#pragma once
#include "BST.hpp"

namespace dsa
{


template<class T>
inline BST<T>::BST()
    : fRoot( nullptr )
{}


template<class T>
inline BST<T>::BST( const BST& other )
{
    this->copyNode( fRoot, other.fRoot );
}


template<class T>
inline BST<T>& BST<T>::operator=( BST other )
{
    std::swap( fRoot, other.fRoot );
}


template<class T>
inline BST<T>::~BST()
{
    this->deleteBranch( fRoot );
}


template<class T>
inline void BST<T>::insert( const T& elem )
{
    this->insert( fRoot, elem );
}


template<class T>
inline typename BST<T>::opt_const_ref_wrapper
BST<T>::find( const T& elem ) const
{
    return this->find( fRoot, elem );
}


template<class T>
inline void BST<T>::print( std::ostream& out ) const
{
    this->print( fRoot, out );
}


template<class T>
inline void BST<T>::deleteBranch( Node*& node )
{
    if ( node )
    {
        deleteBranch( node->fLeftPtr );
        deleteBranch( node->fRightPtr );
        delete node;
        node = nullptr;
    }
}


template<class T>
inline void BST<T>::copyNode( Node*& node, const Node* otherNode )
{
    if ( otherNode )
    {
        node = new Node( otherNode->fData );
        copyNode( node->fLeftPtr, otherNode->fLeftPtr );
        copyNode( node->fRightPtr, otherNode->fRightPtr );
    }
}


template<class T>
inline void BST<T>::insert( Node*& node, const T& elem )
{
    if ( node )
    {
        if ( elem < node->fData )
            insert( node->fLeftPtr, elem );
        else if ( elem > node->fData )
            insert( node->fRightPtr, elem );
        else
            throw std::logic_error( "BST: Cannot store duplicate elements!" );
    }
    else
    {
        node = new Node( elem );
    }
}


template<class T>
inline typename BST<T>::opt_const_ref_wrapper
BST<T>::find( const Node* node, const T& elem ) const
{
    if ( node )
    {
        if ( elem == node->fData )
            return node->fData;

        if ( elem < node->fData )
            return find( node->fLeftPtr, elem );

        return find( node->fRightPtr, elem );
    }
    return std::nullopt;
}


template<class T>
inline void BST<T>::print( const Node* node, std::ostream& out ) const
{
    if ( node )
    {
        print( node->fLeftPtr );
        out << node->fData << " ";
        print( node->fRightPtr );
    }
}


}
