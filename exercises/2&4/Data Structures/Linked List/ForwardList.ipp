#include "ForwardList.hpp"

namespace dsa
{


template<class T>
ForwardList<T>::ForwardList() 
    : head( nullptr )
    , tail( nullptr )
    , size( 0 )
{}


template<class T>
inline ForwardList<T>::ForwardList( const std::initializer_list<T>& il )
    : ForwardList()
{
    for ( typename std::initializer_list<T>::iterator it = il.end() - 1;
        it >= il.begin();
        --it )
    {
        this->push_front( *it );
    }
}


template<class T>
ForwardList<T>::ForwardList( const ForwardList<T>& other )
    : ForwardList()
{
    this->copy( other );
}


template<class T>
ForwardList<T>& ForwardList<T>::operator=( const ForwardList<T>& other )
{
    if ( this != &other )
    {
        this->clean();
        this->copy( other );
    }
    return *this;
}


template<class T>
ForwardList<T>::~ForwardList()
{
    this->clean();
}


template<class T>
void ForwardList<T>::copy( const ForwardList<T>& other )
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
void ForwardList<T>::clean()
{
    while ( !this->isEmpty() )
    {
        this->pop_front();
    }
}


template<class T>
inline typename ForwardList<T>::iterator&
    ForwardList<T>::iterator::operator++()
{
    m_node_ptr = m_node_ptr->pNext;
    return *this;
}


template<class T>
inline typename ForwardList<T>::iterator
    ForwardList<T>::iterator::operator++( int )
{ 
    self_type res(*this);
    ++(*this);
    return res;
}


template<class T>
void ForwardList<T>::print() const
{
    Node* ptr = head;
    while ( ptr != nullptr )
    {
        std::cout << ptr->data << ' ';
        ptr = ptr->pNext;
    }
    std::cout << std::endl;
}


template<class T>
void ForwardList<T>::push_front( const T& newData )
{
    head = new Node( newData, head );
    if ( size == 0 )
    {
        tail = head;
    }
    ++size;
}


template<class T>
void ForwardList<T>::pop_front()
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
    }
}


template<class T>
typename ForwardList<T>::iterator ForwardList<T>::insertAfter( const iterator& it, const T& newData )
{
    Node* new_node = new Node( newData, it.m_node_ptr->pNext );

    it.m_node_ptr->pNext = new_node;

    if ( new_node->pNext == nullptr )
    {
        tail = new_node;
    }

    ++size;
    return new_node;
}


template<class T>
typename ForwardList<T>::iterator ForwardList<T>::removeAfter( const iterator& it )
{
    if ( this->isEmpty() )
    {
        throw std::logic_error( "empty forward list!" );
    }

    Node* removed = it.m_node_ptr->pNext;
    it.m_node_ptr->pNext = removed->pNext;

    if ( removed->pNext == nullptr )
    {
        tail = it.m_node_ptr;
    }

    delete removed;

    --size;
    return it.m_node_ptr->pNext;
}


}
