#include <iostream>
#include <stdexcept>
#include <cassert>
#include <initializer_list>

template <class T>
class LList
{
    struct Node
    {
        Node(const T& val = T(), Node * next = nullptr);
        T data;
        Node * next;
    };

public:
    // Конструктори
    LList();
    LList(const std::initializer_list<T>& values);
    LList(const LList& other);
    LList(LList&& other);
    LList& operator=(const LList &rhs);
    LList& operator=(LList&& other);
    ~LList();

    // Четене на елементи в списъка
    //  Само const версии за краткост
    // Би било добре да има и итератори,
    //  но отново са пропуснати за по-кратко
    const T& front() const;
    const T& back() const;
    const T& at(size_t pos) const;

    class iterator;

    iterator begin();
    iterator end() const;

    // Информативни методи
    bool is_empty() const;
    size_t size() const;

    // Добавяне на елементи
    void push_front(const T& val);
    void push_end(const T& val);
    void push_atPos(size_t pos, const T& val);

    // Премахване на елементи.
    //  Не връщат стойността на премахнатия елемент
    void pop_front();
    void pop_end();
    T pop_atPos(size_t pos);

    // Алгоритми
    void reverse();
    void toSet();
    void sort(bool stable = true);
    bool isSorted() const;

    template<class Func> void map(const Func& func);
    template<class Func> void filter(const Func& predicate);

private:
    Node *head, *tail;
    size_t sz;

    void copy(const LList& other);
    void freeHeap();

    Node * merge(Node * left, Node * right);
    void split(Node* list, Node*& left, Node*& right);
    void split(Node* list, Node*& left, Node*& right, size_t sz);
    Node * mergeSort(Node * list);
    Node * mergeSort(Node * list, size_t sz);

    void fixTail();
};

template<class T>
class LList<T>::iterator
{
    friend iterator LList<T>::begin();
    friend iterator LList<T>::end() const;

    LList<T>::Node* ptr;
    iterator(LList<T>::Node* ptr)
        : ptr(ptr){}

public:
    bool valid() const {return ptr;}
    operator bool() const {return ptr;}

    T& operator*() {return ptr->data;}
    T* operator->() {return &ptr->data;}
    const T& operator*() const {return ptr->data;}
    const T* operator->() const {return &ptr->data;}

    iterator& operator++()
    {
        ptr = ptr->next;
        return *this;
    }
    iterator operator++(int)
    {
        iterator res = *this;
        ++*this;
        return res;
    }

    bool operator == (const iterator& rhs) const
    {
        return ptr == rhs.ptr;
    }
    bool operator != (const iterator& rhs) const
    {
        return !(*this == rhs);
    }
};

template<class T>
inline LList<T>::Node::Node(const T& val, Node * next)
    :data(val), next(next)
{}

template<class T>
inline void LList<T>::copy(const LList<T>& other)
{
    Node dummy;
    Node * iter = &dummy;
    Node * curr = other.head;
    while (curr) {
        iter->next = new Node(curr->data);
        iter = iter->next;
        curr = curr->next;
    }
    head = dummy.next;
    tail = head ? iter : nullptr;
    sz = other.sz;
}

template<class T>
inline void LList<T>::freeHeap()
{
    Node * iter = head;
    Node * detach = head;

    for (size_t i = 0; i < sz; ++i) {
        detach = iter;
        iter = iter->next;
        delete detach;
    }

    tail = head = nullptr;
    sz = 0;
}

template<class T>
inline LList<T>::LList()
    :head(nullptr), tail (nullptr), sz(0) {}

template<class T>
inline LList<T>::LList(const std::initializer_list<T>& values)
    :head(nullptr), tail (nullptr), sz(0)
{
    for (const T& val : values) {
        push_end(val);
    }
}

template<class T>
inline LList<T>::LList(const LList& other)
    :LList()
{
    copy(other);
}

template<class T>
inline LList<T>::LList(LList&& other)
    :LList()
{
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(sz, other.sz);
}

template<class T>
inline LList<T>& LList<T>::operator=(const LList<T>& rhs)
{
    if (this != &rhs) {
        freeHeap();
        copy(rhs);
    }

    return *this;
}

template<class T>
inline LList<T>& LList<T>::operator=(LList<T>&& rhs)
{
    if (this != &rhs) {
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        std::swap(sz, rhs.sz);
    }
    return *this;
}

template<class T>
inline LList<T>::~LList()
{
    freeHeap();
}

template<class T>
inline const T& LList<T>::at(size_t pos) const
{
    if (is_empty() || pos >= sz) {
        throw std::invalid_argument("Index out of bounds\n");
    }

    if (pos == sz - 1) {
        return tail->data;
    }

    const Node * iter = head;
    for (size_t i = 0; i < pos; ++i,  iter = iter->next)
        ;
    return iter->data;
}

template<class T>
inline const T& LList<T>::front() const
{
    return at(0);
}

template< class T>
inline const T& LList<T>::back() const
{
    return at(sz - 1);
}

template<class T>
inline size_t LList<T>::size() const
{
    return sz;
}

template<class T>
inline typename LList<T>::iterator LList<T>::begin()
{
    return iterator(head);
}

template<class T>
inline typename LList<T>::iterator LList<T>::end() const
{
    return iterator(nullptr);
}

template<class T>
inline void LList<T>::push_atPos(size_t pos, const T & val)
{
    if (pos > sz) {
        throw std::invalid_argument("Index out of bounds\n");
    }

    if (pos == 0) {
        head = new Node(val, head);
        if (!sz) tail = head;
    }
    else if (pos == sz) {
        tail->next = new Node(val);
        tail = tail->next;
    }
    else {
        Node * iter = head;
        for (size_t i = 0; i < pos - 1; ++i, iter = iter->next)
            ;

        iter->next = new Node(val, iter->next);
    }

    ++sz;
}

template<class T>
inline void LList<T>::push_front(const T & val)
{
    push_atPos(0, val);
}

template<class T>
inline void LList<T>::push_end(const T & val)
{
    push_atPos(sz, val);
}

template<class T>
inline T LList<T>::pop_atPos(size_t pos)
{
    if (is_empty() || pos > sz - 1) {
        throw std::invalid_argument("Index out of bounds\n");
    }

    Node * detach = head;

    if (pos == 0) {
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
    }
    else {
        Node * iter = head;
        for (size_t i = 0; i < pos - 1; ++i, iter = iter->next)
            ;

        detach = iter->next;
        iter->next = detach->next;

        if (detach == tail) {
            tail = iter;
        }
    }
    --sz;
    T store = detach->data;
    delete detach;
    return store;
}

template<class T>
inline void LList<T>::pop_front()
{
    pop_atPos(0);
}

template<class T>
inline void LList<T>::pop_end()
{
    pop_atPos(sz - 1);
}

template<class T>
inline bool LList<T>::is_empty() const
{
    return sz == 0;
}

template<class T>
inline void LList<T>::reverse()
{
    if (size() < 2) {
        return;
    }

    Node * curr = head;
    Node * perv = nullptr;
    Node * next = nullptr;
    tail = head;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = perv;
        perv = curr;
        curr = next;
    }

    head = perv;
}

template<class T>
inline void LList<T>::toSet()
{
    Node *slow, *fast, *detach;
    slow = head;
    while (slow && slow->next) {
        fast = slow;
        while (fast->next) {
            if (slow->data == fast->next->data) {
                detach = fast->next;
                fast->next = detach->next;
                --sz;
                delete detach;
            }
            else {
                fast = fast->next;
            }
        }
        slow = slow->next;
    }
    tail = slow;
}

template<class T>
inline bool LList<T>::isSorted() const
{
    if (sz < 3) return true;

    Node* iter = head;
    while (iter->next && iter->data == iter->next->data) {
        iter = iter->next;
    }
    if (!iter->next) return true;

    bool asc = iter->data < iter->next->data;
    while (iter->next) {
        if ((iter->data != iter->next->data) &&
            ((iter->data < iter->next->data) != asc)) {
            return false;
        }
        iter = iter->next;
    }
    return true;
}

template<class T>
inline void LList<T>::sort(bool stable)
{
   head = stable ? mergeSort(head, sz) : mergeSort(head);
   fixTail();
}

template<class T>
inline void LList<T>::split(Node* list, Node*& left, Node*& right)
{
    Node dummyLeft;
    Node dummyRight;
    Node* iter = list;
    Node* end_left = &dummyLeft;
    Node* end_right = &dummyRight;

    bool swithToLeft = true;
    while (iter) {
        if (swithToLeft) {
            end_left->next = iter;
            end_left = end_left->next;
            swithToLeft = false;
        }
        else {
            end_right->next = iter;
            end_right = end_right->next;
            swithToLeft = true;
        }
        iter = iter->next;
    }

    end_left->next = nullptr;
    end_right->next = nullptr;

    left = dummyLeft.next;
    right = dummyRight.next;
}

template<class T>
inline void LList<T>::split(Node* head, Node *& left, Node*& right, size_t listSz)
{
    Node* iter = head;
    left = iter;
    size_t mid = listSz / 2 + listSz % 2;
    for (size_t i = 0; i < mid - 1; i++) {
        iter = iter->next;
    }

    right = iter->next;
    iter->next = nullptr;
}

template<class T>
inline typename LList<T>::Node * LList<T>::merge(Node * left, Node * right)
{
    Node merged;
    Node * curr = &merged;
    while (left && right) {
        if (left->data < right->data) {
            curr->next = left;
            left = left->next;
        }
        else {
            curr->next = right;
            right = right->next;
        }
        curr = curr->next;
    }
    curr->next = left ? left : right;
    return merged.next;
}

template<class T>
inline typename LList<T>::Node * LList<T>::mergeSort(Node* list, size_t size)
{
    if (list->next == nullptr) {
        return list;
    }
    Node *left = nullptr, *right = nullptr;
    split(list, left, right, size);
    return merge(mergeSort(left, size / 2 + size % 2), mergeSort(right, size / 2));
}

template<class T>
inline typename LList<T>::Node * LList<T>::mergeSort(Node* list)
{
    if (list->next == nullptr) {
        return list;
    }

    Node *left = nullptr, *right = nullptr;
    split(list, left, right);
    return merge(mergeSort(left), mergeSort(right));
}

template<class T>
inline void LList<T>::fixTail()
{
    if (!head) {
        tail = head;
        return;
    }
    Node* iterator;
    for (iterator = head; iterator->next; iterator = iterator->next)
        ;
    tail = iterator;
}

template<class T>
template<class Func>
inline void LList<T>::map(const Func& func)
{
    for (Node* iterator = head; iterator; iterator = iterator->next)
        func(iterator->data);
}

template<class T>
template<class Func>
inline void LList<T>::filter(const Func& predicate)
{
    Node dummy;
    Node* current = &dummy;
    Node* toDelete = nullptr;

    for (Node* iterator = head; iterator; iterator = iterator->next) {
        delete toDelete;
        current->next = iterator;
        if (predicate(current->next->data)) {
            current = current->next;
            toDelete = nullptr;
        }
        else {
            toDelete = iterator;
            --sz;
        }
    }
    if (sz) {
        head = dummy.next;
        tail = current;
    }
    else {
        head = tail = nullptr;
    }
}


/////////////////////////////////////////////////
// Прости unit test методи за тестване на списъка
// директна имплементация

void testPush()
{
     LList<int> test {1, 2};

     test.push_end(5);
     test.push_atPos(2, 3);
     test.push_atPos(3, 4);
     for (int i = 1;  i <= 5; i++) {
         assert(test.at(unsigned(i - 1)) == i);
     }

     bool flag = false;
     try {
         test.push_atPos(unsigned(-1), 0);
     } catch (const std::invalid_argument&) {
         flag = true;
     }

     assert(flag);
}

void testPop(unsigned seed = 1)
{
    LList<int> test;
    bool flag = false;
    try {
        test.pop_atPos(0);
    } catch (const std::invalid_argument&) {
        flag = true;
    }

    assert(flag);

    flag = false;
    try {
        test.pop_atPos(1);
    } catch (const std::invalid_argument&) {
        flag = true;
    }

    assert(flag);

    srand(seed);
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++) {
        test.push_atPos(i, i);
    }

    flag = false;
    try {
        for (size_t i = 0; i < testSz; i++) {
            test.pop_atPos(rand() % (testSz - i));
        }
    } catch (const std::invalid_argument&) {
        flag = true;
    }

    assert(flag || test.is_empty());
}

void testPos(unsigned seed = 1)
{
    LList<int> test;

    srand(seed);
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++) {
        test.push_atPos(i, rand() % testSz);
    }

    srand(seed);
    for (size_t i = 0; i < testSz; i++) {
        assert(rand() % testSz == (size_t)test.at(i));
    }

    bool flag = false;
    try {
        test.at(unsigned(-1));
    } catch (const std::invalid_argument&) {
        flag = true;
    }

    assert(flag);
}

void testCpy(unsigned seed = 1)
{
    LList<int> test;

    srand(seed);
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++) {
        test.push_atPos(i, rand() % testSz);
    }

    LList<int> testCpy(test);
    for (size_t i = 0; i < testSz; i++) {
        assert(testCpy.at(i) == test.at(i));
    }

    assert(testCpy.size() == test.size());

    LList<int> testOp = test;
    for (size_t i = 0; i < testSz; i++) {
        assert(testCpy.at(i) == test.at(i));
    }

    assert(testOp.size() == testOp.size());
}

void testReverse()
{
    LList<int> test;
    const size_t testSz = 100;
    for (size_t i = 0; i < testSz; i++) {
        test.push_front(i);
    }

    test.reverse();
    for (size_t i = 0; i < testSz; i++) {
        assert(test.at(0) == (int)i);
        test.pop_front();
    }
}

template <class DataType>
const DataType& print(const DataType& elem)
{
    std::cout << elem << " ";
    return elem;
}

void testSet(unsigned seed = 1)
{
    LList<int> test;
    const size_t testSz = 100;
    const size_t set_sz = 5;
    srand(seed);

    for (size_t i = 0; i < testSz; i++) {
        test.push_front(rand() % set_sz);
    }

    test.toSet();
    assert(test.size() <= 5);
    test.map(print<int>);
}

void testIsSorted(unsigned seed = 1)
{
    const size_t testSz = 100;
    const size_t set_sz = 5;
    srand(seed);

{
    LList<int> test1;
    for (size_t i = 0; i < testSz; ++i)
        test1.push_front(i);
    assert(test1.isSorted());
}

{
    LList<int> test2;
    for (size_t i = testSz; i > 0; --i)
        test2.push_front(i);
    assert(test2.isSorted());
}

{
    LList<int> test3;
    for (size_t i = set_sz; i > 0; --i)
        test3.push_front(0);

    for (size_t i = 0; i < testSz; ++i)
        test3.push_front(i);
    assert(test3.isSorted());
}

{
    LList<int> test4;
    for (size_t i = set_sz; i > 0; --i)
        test4.push_front(0);

    for (size_t i = testSz; i > 0; --i)
        test4.push_front(i);
    assert(!test4.isSorted());
}

{
    LList<int> test5;
    for (size_t i = 0; i < testSz; ++i)
        test5.push_front(i/4);
    assert(test5.isSorted());
}

{
    LList<int> test6;
    for (size_t i = 0; i < testSz; i++) {
        test6.push_front(rand() % set_sz);
    }
    assert(!test6.isSorted());
}
}

void testSort(unsigned seed = 1)
{
    LList<int> test;
    const size_t testSz = 100000;
    const size_t moduleSz = 2000;
    srand(seed);

    for (size_t i = 0; i < testSz; i++) {
        test.push_front(rand() % moduleSz);
    }

    test.sort(true);
    assert(test.isSorted());

    test.reverse();
    test.sort(false);
    assert(test.isSorted());
}

void testIterator()
{
    LList<int>test {1, 2, 3, 4, 5};

    int i = 1, sum = 0;
    for (const int & val : test) {
        assert (val == i);
        ++i;
        sum += val;
    }


    for (LList<int>::iterator it1 = test.begin(); it1 != test.end(); ++it1) {
        int innerSum = 0;

        LList<int>::iterator it2 = it1;
        while (it2) innerSum += *it2++;

        assert (innerSum == sum);
        sum -= *it1;
    }
}

void testMap()
{
    LList<int> test;
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++) {
        test.push_end(i);
    }

    test.map([](int& x){x *= 2;});

    for (size_t i = 0; i < testSz; i++) {
        assert(test.at(i) == (int)(2*i));
    }
    assert(test.back() == 198);

    test.push_front(0);
    test.push_end(200);
    assert(test.front() == 0);
    assert(test.back() == 200);
}

void testFilter()
{
    LList<int> test;
    const size_t testSz = 100;

    for (size_t i = 0; i < testSz; i++) {
        test.push_front(i);
    }

    test.filter([](int x){return x % 3;});

    assert(test.size() == 66);
    for (size_t i = 0; i < test.size(); i++) {
        assert(test.at(i)%3);
    }
    assert(test.back() == 1);

    test.push_front(0);
    test.push_end(200);
    assert(test.front() == 0);
    assert(test.back() == 200);
}


void makeTests()
{
    testPush();
    testPos();
    testPop();
    testCpy();
    testReverse();
    testSet();
    testIsSorted();
    testSort();
    testIterator();

    testMap();
    testFilter();
}

int main ()
{
    makeTests();
    return 0;
}
