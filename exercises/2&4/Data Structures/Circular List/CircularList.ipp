#include "CircularList.hpp"

namespace dsa
{


template<class T>
CircularList<T>::CircularList() 
    : head( nullptr )
    , tail( nullptr )
    , size( 0 )
{}


template<class T>
CircularList<T>::CircularList( const CircularList<T>& other )
    : CircularList()
{
    this->copy( other );
}


template<class T>
CircularList<T>& CircularList<T>::operator=( const CircularList<T>& other )
{
    if ( this != &other )
    {
        this->clean();
        this->copy( other );
    }
    return *this;
}


template<class T>
CircularList<T>::~CircularList()
{
    this->clean();
}


template<class T>
void CircularList<T>::copy( const CircularList<T>& other )
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
        size++;

        while ( toCopy->pNext != other.head )
        {
            toCopy = toCopy->pNext;

            copied->pNext = new Node( toCopy->data );
            copied = copied->pNext;
            size++;
        }

        tail = copied;
    }
    catch (...)
    {
        this->clean();
        throw;
    }
}


template<class T>
void CircularList<T>::clean()
{
    while ( !this->isEmpty() )
    {
        this->pop();
    }
}


template<class T>
inline typename CircularList<T>::iterator&
    CircularList<T>::iterator::operator++()
{
    m_node_ptr = m_node_ptr->pNext;
    return *this;
}


template<class T>
inline typename CircularList<T>::iterator
    CircularList<T>::iterator::operator++( int )
{ 
    self_type res(*this);
    ++(*this);
    return res;
}


template<class T>
void CircularList<T>::print() const
{
    Node* ptr = head;
    if ( head )
    {
        do
        {
            std::cout << ptr->data << ' ';
            ptr = ptr->pNext;
        }
        while ( ptr != head );
    }
    std::cout << std::endl;
}


//template<class T>
//inline ForwardList<T>& ForwardList<T>::reverse()
//{
//    tail    = head;
//
//    Node*   prev    = nullptr;
//    Node*   next    = head->pNext;
//    while ( next )
//    {
//        head->pNext = prev;
//        prev        = head;
//        head        = next;
//        next        = next->pNext;
//    }
//
//    head->pNext = prev;
//
//    return *this;
//}
//
//
//template<class T>
//inline ForwardList<T>& ForwardList<T>::removeDuplicates()
//{
//    Node*   curr    = head;
//    Node*   next    = curr->pNext;
//
//    while ( next )
//    {
//        if ( curr->data == next->data )
//        {
//            next = this->removeAfter( curr );
//        }
//        else
//        {
//            curr = curr->pNext;
//            next = next->pNext;
//        }
//    }
//
//    return *this;
//}


template<class T>
void CircularList<T>::push( const T& newData )
{
    head = new Node( newData, head );
    if ( size == 0 )
    {
        tail = head;
    }
    ++size;

    tail->pNext = head;
}


template<class T>
void CircularList<T>::pop()
{
    if ( size == 0 )
    {
        throw std::logic_error( "the list is empty!\n" );
    }
    Node* temp = head;
    head = head->pNext;
    delete temp;
    --size;
    if ( size == 0 )
    {
        tail = nullptr;
        head = nullptr;
    }
    else
    {
        tail->pNext = head;
    }
}


template<class T>
typename CircularList<T>::iterator CircularList<T>::insertAfter( const iterator& it, const T& newData )
{
    Node* new_node = new Node( newData, it.m_node_ptr->pNext );

    it.m_node_ptr->pNext = new_node;

    ++size;
    return new_node;
}


template<class T>
typename CircularList<T>::iterator CircularList<T>::removeAfter( const iterator& it )
{
    if ( this->isEmpty() )
    {
        throw std::logic_error( "empty forward list!" );
    }

    Node* removed = it.m_node_ptr->pNext;
    it.m_node_ptr->pNext = removed->pNext;

    delete removed;

    --size;
    return it.m_node_ptr->pNext;
}


}
