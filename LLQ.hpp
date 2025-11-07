#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() {
        this->list = LinkedList<T>();
    }

    // Insertion
    void enqueue(const T& item) override {
        this->list.AddTail(item);
    }

    // Deletion
    T dequeue() override {
        if (this->getSize() == 0) {
            throw std::runtime_error("LLQ is empty");
        }
        T data = this->list.getHead()->data;

        this->list.RemoveHead();

        return data;
    }

    // Access
    T peek() const override {
        if (this->getSize() == 0) {
            throw std::runtime_error("LLQ is empty");
        }
        return this->list.getHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return this->list.getCount();
    }

};
