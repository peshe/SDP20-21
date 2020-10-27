/******************************************************************
*  Sample code to the course "Data Structures And Algorithms", FMI
*
* A education class, representing linked stack implementation
*
* (cc) Petar Armyanov, FMI, 2020
*******************************************************************/
#pragma once

#ifndef _LINKED_STAC_HEADER_INCLUDED_
#define _LINKED_STC_HEADER_INCLUDED_


namespace fmi {
namespace sdp {

class LinkedStack
{
public:
    LinkedStack();
    LinkedStack(const LinkedStack& stack);
    ~LinkedStack();
    LinkedStack& operator= (const LinkedStack& rhs);

    void push(int elem);
    int pop();
    const int& top() const;
    bool isEmpty() const;

private:
    struct node
    {
        int data;
        node* next;

        node(int d, node* n = nullptr)
            : data(d)
            , next(n)
        {}
    } *tos;

private:
    void clear();
    void copy(const node* top);
};

} // namespace sdp
} // namespace fmi

#endif  //_LINKED_STAC_HEADER_INCLUDED_
