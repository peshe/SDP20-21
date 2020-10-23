#include "linkedStack.h"
#include <stdexcept>
#include <cassert>

namespace fmi {
namespace sdp {

LinkedStack::LinkedStack()
    : tos(nullptr)
{}

LinkedStack::LinkedStack(const LinkedStack& stack)
    : tos(nullptr)
{
    try {
        copy(stack.tos);
    }
    catch (std::bad_alloc&){
        clear();
        throw;
    }
}

LinkedStack::~LinkedStack()
{
    clear();
}

LinkedStack& LinkedStack::operator=(const LinkedStack& rhs)
{
    if (this != &rhs) {
        clear();
        copy(rhs.tos);
    }
    return *this;
}

void LinkedStack::push(int elem)
{
    tos = new node(elem, tos);
}

int LinkedStack::pop()
{
    int res = top();
    node* keep = tos;
    tos = tos->next;
    delete keep;
    return res;
}

const int& LinkedStack::top() const
{
    if (!isEmpty())
        return tos->data;
    throw std::underflow_error("Empty stack");
}

bool LinkedStack::isEmpty() const
{
    return tos == nullptr;
}

void LinkedStack::clear()
{
    while (!isEmpty())
        pop();
}

void LinkedStack::copy(const node* top)
{
    assert(tos == nullptr);
    if (top) {
        tos = new node(top->data);
        top = top->next;

        node* prev = tos;
        while (top) {
            prev->next = new node(top->data);
            prev = prev->next;
            top = top->next;
        }
    }
}

} // namespace sdp
} // namespace fmi
