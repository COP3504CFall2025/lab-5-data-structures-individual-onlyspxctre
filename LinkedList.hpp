#pragma once
#include <cassert>
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* prev = nullptr;
    Node* next = nullptr;
};

template <typename T>
class LinkedList {
  public:
    // Behaviors
    void printForward() const {
        Node<T>* curr = this->head;
        Node<T>* next;

        std::cout << '{';

        while (curr) {
            next = curr->next;

            std::cout << ' ' << curr->data;

            curr = next;
        }

        std::cout << " }" << std::endl;
    }

    void PrintReverse() const {
        Node<T>* curr = this->tail;
        Node<T>* prev;

        std::cout << '{';

        while (curr) {
            prev = curr->prev;

            std::cout << ' ' << curr->data;

            curr = prev;
        }

        std::cout << " }" << std::endl;
    }

    // Accessors
    [[nodiscard]] unsigned int getCount() const {
        return this->count;
    }

    Node<T>* getHead() {
        return this->head;
    }
    const Node<T>* getHead() const {
        return this->head;
    }

    Node<T>* getTail() {
        return this->tail;
    }
    const Node<T>* getTail() const {
        return this->tail;
    }

    // Insertion
    void AddHead(const T& data) {
        Node<T>* newHead = new Node<T>;
        newHead->data = data;
        if (this->head == nullptr) {
            this->head = newHead;
            this->tail = this->head;
        } else {
            newHead->next = this->head;
            this->head->prev = newHead;
            this->head = newHead;
        }

        this->count += 1;
    }
    void AddTail(const T& data) {
        Node<T>* newTail = new Node<T>;
        newTail->data = data;
        if (this->tail == nullptr) {
            this->tail = newTail;
            this->head = this->tail;
        } else {
            newTail->prev = this->tail;
            this->tail->next = newTail;
            this->tail = newTail;
        }

        this->count += 1;
    }

    // Removal
    bool RemoveHead() {
        if (this->count == 0) {
            return false;
        }

        Node<T>* next = this->head->next;
        delete this->head;

        if (!next) {
            this->head = NULL;
            this->tail = NULL;
        } else {
            this->head = next;
            this->head->prev = nullptr;
        }

        this->count -= 1;

        return true;
    }
    bool RemoveTail() {
        if (this->count == 0) {
            return false;
        }

        Node<T>* prev = this->tail->prev;
        delete this->tail;

        if (this->count == 1) {
            this->head = nullptr;
            this->tail = nullptr;
        } else {
            this->tail = prev;
            this->tail->next = nullptr;
        }

        this->count -= 1;

        return true;
    }
    void Clear() {
        Node<T>* curr = this->head;
        Node<T>* next = nullptr;

        while (curr) {
            next = curr->next;

            delete curr;
            this->count -= 1;

            curr = next;
        }

        this->head = nullptr;
        this->tail = nullptr;
    }

    // Operators
    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept { // move constructor
        this->Clear();

        this->head = other.head;
        this->tail = other.tail;
        this->count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;

        return *this;
    }
    LinkedList<T>& operator=(const LinkedList<T>& rhs) { // copy constructor
        auto list = LinkedList<T>();

        auto curr = rhs.getHead();

        while (curr) {
            try {
                list.AddTail(curr->data);
            } catch (std::bad_alloc& e) {
                std::cerr << "Failed to copy linked list: " << e.what() << std::endl;
                return *this;
            }

            curr = curr->next;
        }

        *this = std::move(list);

        return *this;
    }

    // Construction/Destruction
    LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }
    LinkedList(const LinkedList<T>& list) : LinkedList() {
        Node<T>* other = list.head;

        while (other != nullptr) {
            this->AddTail(other->data);
            other = other->next;
        }
    }
    LinkedList(LinkedList<T>&& other) noexcept {
        this->head = other.head;
        this->tail = other.tail;
        this->count = other.count;

        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
    }
    ~LinkedList() {
        this->Clear();
    }

  private:
    // Stores pointers to first and last nodes and count
    Node<T>* head;
    Node<T>* tail;
    unsigned int count;
};
