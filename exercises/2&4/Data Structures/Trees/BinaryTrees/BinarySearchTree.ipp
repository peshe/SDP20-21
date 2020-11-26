#pragma once
#include "BinarySearchTree.hpp"

namespace dsa
{


template<class T>
inline BST<T>::BST()
    : fRoot( nullptr )
{}


template<class T>
inline BST<T>::BST( const BST& other )
{
    this->copyBranch( fRoot, other.fRoot );
}


template<class T>
inline BST<T>& BST<T>::operator=( BST other )
{
    std::swap( fRoot, other.fRoot );
    return *this;
}


template<class T>
inline BST<T>::~BST()
{
    this->deleteBranch( fRoot );
}


template<class T>
inline void BST<T>::insert( const T& elem )
{
    this->insertRec( fRoot, elem );
}


template<class T>
inline bool BST<T>::tryInsert( const T& elem )
{
    return this->tryInsertRec( fRoot, elem );
}


template<class T>
inline typename BST<T>::opt_const_ref_wrapper
    BST<T>::find( const T& elem ) const
{
    return this->findRec( fRoot, elem );
}


template<class T>
inline bool BST<T>::erase( const T& elem )
{
    return this->eraseRec( fRoot, elem );
}


template<class T>
inline void BST<T>::print( std::ostream& out ) const
{
    this->printRec( fRoot, out );
}


template<class T>
inline const T& BST<T>::min() const
{
    if ( fRoot == nullptr )
        throw std::logic_error( "BST: min() of an empty BST!" );

    return this->minRec( fRoot )->fData;
}


template<class T>
inline const T& BST<T>::max() const
{
    if ( fRoot == nullptr )
        throw std::logic_error( "BST: max() of an empty BST!" );

    return this->maxRec( fRoot )->fData;
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
inline void BST<T>::copyBranch( Node*& node, const Node* otherNode )
{
    if ( otherNode )
    {
        node = new Node( otherNode->fData );
        this->copyBranch( node->fLeftPtr, otherNode->fLeftPtr );
        this->copyBranch( node->fRightPtr, otherNode->fRightPtr );
    }
}


template<class T>
inline void BST<T>::insertRec( Node*& node, const T& elem )
{
    if ( !this->tryInsertRec( node, elem ) )
        throw std::logic_error( "BST: Cannot store duplicate elements!" );
}


template<class T>
inline bool BST<T>::tryInsertRec( Node*& node, const T& elem )
{
    if ( node )
    {
        // Discard duplicates
        if ( elem == node->fData )
            return false;

        // Insert in the left subtree
        if ( elem < node->fData )
            return this->tryInsertRec( node->fLeftPtr, elem );

        // Insert in the right subtree ( elem > node->fData )
        return this->tryInsertRec( node->fRightPtr, elem );
    }

    // Free space (nullptr) found
    node = new Node( elem );
    return true;
}


template<class T>
inline typename BST<T>::opt_const_ref_wrapper
    BST<T>::findRec( const Node* node, const T& elem ) const
{
    if ( node )
    {
        if ( elem == node->fData )
            return node->fData;

        if ( elem < node->fData )
            return this->findRec( node->fLeftPtr, elem );

        // ( elem > node->fData )
        return this->findRec( node->fRightPtr, elem );
    }

    return std::nullopt;
}


template<class T>
inline bool BST<T>::eraseRec( Node*& node, const T& elem )
{
    if ( node )
    {
        if ( node->fData == elem ) // Element found
        {
            if ( !node->fLeftPtr && !node->fRightPtr )
            {
                // No children => it's a leaf
                delete node;
                node = nullptr;
            }
            else if ( ( node->fLeftPtr && !node->fRightPtr ) || ( !node->fLeftPtr && node->fRightPtr ) )
            {
                // Only one child => replace it with the child
                Node* onlyChild = node->fLeftPtr ? node->fLeftPtr : node->fRightPtr;
                Node* toRemove = node;
                node = onlyChild;
                delete toRemove;
            }
            else
            {
                // Two children => replace it with the smallest from the right subtree
                Node*& min = this->minRec( node->fRightPtr );
                std::swap( node->fData, min->fData );
                this->eraseRec( min, elem ); // Erase recursively incase it's not a leaf
            }

            return true;
        }
        else if ( elem < node->fData )
        {
            // Search the left subtree
            return this->eraseRec( node->fLeftPtr, elem );
        }

        // Search the right subtree ( elem > node->fData )
        return this->eraseRec( node->fRightPtr, elem );
    }

    return false;
}


template<class T>
inline void BST<T>::printRec( const Node* node, std::ostream& out ) const
{
    if ( node )
    {
        this->printRec( node->fLeftPtr );
        out << node->fData << " ";
        this->printRec( node->fRightPtr );
    }
}


template<class T>
inline typename BST<T>::Node*&
    BST<T>::minRec( Node*& node ) const
{
    if ( node )
    {
        if ( node->fLeftPtr )
            return this->minRec( node->fLeftPtr );

        return node;
    }
}


template<class T>
inline typename BST<T>::Node*&
    BST<T>::maxRec( Node*& node ) const
{
    if ( node )
    {
        if ( node->fRightPtr )
            return this->minRec ( node->fRightPtr );

        return node;
    }
}


} // end of namespace dsa
