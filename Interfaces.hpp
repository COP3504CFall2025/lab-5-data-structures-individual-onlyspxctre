#pragma once

#include <cstddef>

template <typename T>
class StackInterface {
  public:
    virtual void push(const T& item) = 0;
    virtual T pop() = 0;
    virtual T peek() const = 0;
    virtual std::size_t getSize() const noexcept = 0;

    virtual ~StackInterface() = default;
};

template <typename T>
class QueueInterface {
    virtual void enqueue(const T& item) = 0;
    T dequeue() = 0;
    T peek() const = 0;
    std::size_t getSize() const noexcept = 0;

    virtual ~QueueInterface() = default;
};

template <typename T>
class DequeInterface {
    virtual void pushFront(const T& item) = 0;
    virtual void pushBack(const T& item) = 0;
    virtual T popFront() = 0;
    virtual T popBack() = 0;

    virtual ~DequeInterface() = default;
};
