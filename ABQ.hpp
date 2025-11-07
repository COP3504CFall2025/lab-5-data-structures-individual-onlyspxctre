#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t index_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

    void realloc(const size_t capacity) {
        T* data = new T[capacity];

        this->capacity_ = capacity;
        for (size_t i = 0; i < this->curr_size_; ++i) {
            data[i] = this->array_[this->index_ - this->curr_size_ + i];
        }

        delete[] this->array_;
        this->array_ = data;
        this->index_ = this->curr_size_;
    }

public:
    // Constructors + Big 5
    ABQ() {
        this->capacity_ = 1;
        this->index_ = 0;
        this->curr_size_ = 0;
        this->array_ = new T[this->capacity_];
    }
    explicit ABQ(const size_t capacity) {
        this->capacity_ = capacity;
        this->index_ = 0;
        this->curr_size_ = 0;
        this->array_ = new T[this->capacity_];
    }
    ABQ(const ABQ& other) {
        this->capacity_ = other.capacity_;
        this->index_ = other.index_;
        this->curr_size_ = other.curr_size_;

        this->array_ = new T[this->capacity_];
        for (size_t i = 0; i < this->capacity_; ++i) {
            this->array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) {
        T* data = new T[rhs.capacity_];

        delete[] this->array_;
        this->array_ = data;

        this->capacity_ = rhs.capacity_;
        this->index_ = rhs.index_;
        this->curr_size_ = rhs.curr_size_;

        for (size_t i = 0; i < this->capacity_; ++i) {
            this->array_[i] = rhs.array_[i];
        }

        return *this;
    }
    ABQ(ABQ&& other) noexcept {
        this->capacity_ = other.capacity_;
        this->index_ = other.index_;
        this->curr_size_ = other.curr_size_;
        this->array_ = other.array_;

        other.capacity_ = 0;
        other.index_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        delete[] this->array_;

        this->capacity_ = rhs.capacity_;
        this->index_ = rhs.index_;
        this->curr_size_ = rhs.curr_size_;
        this->array_ = rhs.array_;

        rhs.capacity_ = 0;
        rhs.index_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;

        return *this;
    }
    ~ABQ() noexcept override {
        delete[] this->array_;

        this->array_ = nullptr;
        this->curr_size_ = 0;
        this->index_ = 0;
        this->capacity_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return this->curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return this->capacity_;
    }
    [[nodiscard]] T* getData() const noexcept {
        return this->array_;
    }

    // Insertion
    void enqueue(const T& data) override {
        if (this->index_ == this->capacity_) {
            realloc(this->capacity_ << 1);
        }
        this->array_[this->index_] = data;

        this->index_ += 1;
        this->curr_size_ += 1;
    }

    // Access
    T peek() const override {
        if (this->getSize() == 0) {
            throw std::runtime_error("ABQ is empty");
        }
        return this->array_[this->index_ - this->curr_size_];
    }

    // Deletion
    T dequeue() override {
        if (this->getSize() == 0) {
            throw std::runtime_error("ABQ is empty");
        }
        this->curr_size_ -= 1;
        return this->array_[this->index_ - this->curr_size_ - 1];
    }

};
