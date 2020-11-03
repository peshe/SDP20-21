#ifndef DLLIST
#define DLLIST

template<typename T>
class DoublyLinkedList {
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(T data, Node* prev, Node* next): data(data), prev(prev), next(next) {}
    };
    Node* head;
    Node* tail;

public:
    DoublyLinkedList(): head(NULL), tail(NULL) {}
    DoublyLinkedList(const DoublyLinkedList& other) = delete;
    const DoublyLinkedList& operator=(const DoublyLinkedList& other) = delete;
    ~DoublyLinkedList() {
        while(!empty()) {
            pop_front();
        }
    }

    void push_back(T element) {
        throw "not implemented";
    }

    void push_front(T element) {
        throw "not implemented";
    }

    void pop_back() {
        throw "not implemented";
    }

    void pop_front() {
        throw "not implemented";
    }

    void insert(T element, int index) {
        throw "not implemented";
    }

    void remove(int index) {
        throw "not implemented";
    }

    const T& getFront() const {
        throw "not implemented";
    }

    const T& getBack() const {
        throw "not implemented";
    }

    const T& getAt(int index) {
        throw "not implemented";
    }

    const bool empty() const {
        return head == NULL;
    }

};

#endif // DLLIST
