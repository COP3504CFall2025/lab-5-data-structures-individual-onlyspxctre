#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <cstddef>
#include <stdexcept>

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
        this->list.AddHead(item);
    }
    void pushBack(const T& item) override {
        this->list.AddTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (this->getSize() == 0) {
            throw std::runtime_error("LLDQ is empty");
        }
        T data = this->list.getHead()->data;

        list.RemoveHead();

        return data;
    }
    T popBack() override {
        if (this->getSize() == 0) {
            throw std::runtime_error("LLDQ is empty");
        }
        T data = this->list.getTail()->data;

        list.RemoveTail();

        return data;
    }

    // Element Accessors
    const T& front() const override {
        if (this->getSize() == 0) {
            throw std::runtime_error("LLDQ is empty");
        }
        return this->list.getTail()->data;
    }
    const T& back() const override {
        if (this->getSize() == 0) {
            throw std::runtime_error("LLDQ is empty");
        }
        return this->list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return this->list.getCount();
    }
};
