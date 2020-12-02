//
// Created by Yasen Aleksiev on 25/10/20.
// Edited by Aleksandar Dimitrov
//

#include "DoubleLinkedList.hpp"

namespace dsa {


template<class T>
DoubleLinkedList<T>::DoubleLinkedList()
    : head( nullptr )
    , tail( nullptr )
    , size( 0 )
{}


template<class T>
inline DoubleLinkedList<T>::DoubleLinkedList( const std::initializer_list<T>& il )
    : DoubleLinkedList()
{
    for ( const T& el : il )
    {
        this->push_back( el );
    }
}


template<class T>
DoubleLinkedList<T>::DoubleLinkedList( const DoubleLinkedList<T>& other )
    : DoubleLinkedList()
{
    this->copy( other );
}


template<class T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=( const DoubleLinkedList<T>& other )
{
    if ( this != &other )
    {
        this->clean();
        this->copy( other );
    }
    return *this;
}


template<class T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    this->clean();
}


template<class T>
inline typename DoubleLinkedList<T>::iterator&
DoubleLinkedList<T>::iterator::operator++()
{

    m_node_ptr = m_node_ptr->pNext;
    return *this;
}


template<class T>
inline typename DoubleLinkedList<T>::iterator
DoubleLinkedList<T>::iterator::operator++( int )
{

    self_type res( *this );
    ++( *this );
    return res;
}


template<class T>
inline typename DoubleLinkedList<T>::iterator&
DoubleLinkedList<T>::iterator::operator--()
{

    m_node_ptr = m_node_ptr->pPrev;
    return *this;
}


template<class T>
inline typename DoubleLinkedList<T>::iterator
DoubleLinkedList<T>::iterator::operator--( int )
{ 

    self_type res( *this );
    --( *this );
    return res;
}


template<class T>
void DoubleLinkedList<T>::copy( const DoubleLinkedList<T>& other )
{
    if ( other.isEmpty() )
    {
        return;
    }

    try
    {
        head = new Node( other.head->data );
        Node* toCopy = other.head;
        Node* copied = head;

        while ( toCopy->pNext != nullptr )
        {
            toCopy = toCopy->pNext;

            copied->pNext = new Node( toCopy->data, nullptr, copied );
            copied = copied->pNext;
            size++;
        }

        tail = copied;
    }
    catch ( ... )
    {
        this->clean();
        throw;
    }
}


template<class T>
void DoubleLinkedList<T>::clean()
{
    while ( !this->isEmpty() )
    {
        this->pop_front();
    }
}


template<class T>
void DoubleLinkedList<T>::print() const
{
    if ( size == 0 )
    {
        std::cout << "[]" << std::endl;
    }
    else if ( size == 1 )
    {
        std::cout << "[ " << head->data << " ]" << std::endl;
    }
    else
    {
        std::cout << "[ ";
        Node* ptr = head;
        while ( ptr->pNext != nullptr )
        {
            std::cout << ptr->data << " <-> ";
            ptr = ptr->pNext;
        }
        std::cout << ptr->data << " ]" << std::endl;
    }
    std::cout << std::endl;
}


template<class T>
void DoubleLinkedList<T>::push_front( const T& newData )
{
    Node* newNode = new Node( newData, head );
    head->prev = newNode;
    head = newNode;
    if ( size == 0 )
    {
        tail = head;
    }

    ++size;
}


template<class T>
void DoubleLinkedList<T>::pop_front()
{
    if ( size == 0 )
    {
        throw std::logic_error( "the list is empty!\n" );
    }

    if ( size == 1 )
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        head = head->pNext;
        delete head->pPrev;
        head->pPrev = nullptr;
    }
    --size;
}


template<class T>
void DoubleLinkedList<T>::push_back( const T& newData )
{
    tail = new Node( newData, nullptr, tail );
    if ( size == 0 )
    {
        head = tail;
    }
    else
    {
        tail->pPrev->pNext = tail;
    }
    ++size;
}


template<class T>
void DoubleLinkedList<T>::pop_back()
{
    if ( size == 0 )
    {
        throw std::logic_error( "the list is empty!\n" );
    }
    if ( size == 1 )
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        size = 0;
        return;
    }

    tail = tail->pPrev;
    delete tail->pNext;
    tail->pNext = nullptr;
    --size;
}


template<class T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::insert( const iterator& it, const T& newData )
{
    if ( it == this->begin() || size < 2 )
    {
        this->push_front( newData );
        return iterator( head );
    }

    Node* prev = it.m_node_ptr->pPrev;

    Node* newNode = new Node( newData, it.m_node_ptr, prev );
    prev->pNext = newNode;

    it.m_node_ptr->pPrev = newNode;

    ++size;
    return newNode;
}


template<class T>
typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::remove( const iterator& it )
{
    if ( this->isEmpty() )
    {
        throw std::logic_error( "empty double linked list!" );
    }
    // there is no element
    if ( it == this->end() )
    {
        return end();
    }
    // first element case
    if ( it.m_node_ptr == head )
    {
        this->pop_front();
        return iterator( head );
    }
    // last element case
    if ( it.m_node_ptr == tail )
    {
        this->pop_back();
        return iterator( tail );
    }

    Node* prev = it.m_node_ptr->pPrev;
    Node* next = it.m_node_ptr->pNext;

    // link the previous with the next
    prev->pNext = next;

    // link next with the previous
    next->pPrev = prev;

    // free the resources for the deleted box
    delete it.m_node_ptr;
    --size;

    return next;
}


}
