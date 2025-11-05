#pragma once

#include <cstddef>
#include "Interfaces.hpp"
#include "LinkedList.hpp"

template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() {
        this->list = LinkedList<T>();
    }

    // Core Insertion Operations
    void pushFront(const T& item) override {
        this->list.addHead(item);
    }
    void pushBack(const T& item) override {
        this->list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        T data = this->list.getHead()->data;

        list.removeHead();

        return data;
    }
    T popBack() override {
        T data = this->list.getTail()->data;

        list.removeTail();

        return data;
    }

    // Element Accessors
    const T& front() const override {
        return this->list.getTail()->data;
    }
    const T& back() const override {
        return this->list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return this->list.getCount();
    }
};
