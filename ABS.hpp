#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() {
        this->curr_size_ = 0;
        this->capacity_ = 1;
        this->array_ = new T[this->capacity_];
    }
    explicit ABS(const size_t capacity) {
        this->curr_size_ = 0;
        this->capacity_ = capacity;
        this->array_ = new T[this->capacity_];
    }
    ABS(const ABS& other) {
        this->curr_size_ = other.curr_size_;
        this->capacity_ = other.capacity_;
        this->array_ = new T[this->capacity_];

        for (size_t i = 0; i < this->capacity_; ++i) {
            this->array_[i] = other.array_;
        }
    }
    ABS& operator=(const ABS& rhs) {
        T* data = new T[rhs.capacity_];

        this->curr_size_ = rhs.curr_size_;
        this->capacity = rhs.capacity_;

        this->array_ = data;
        delete[] this->array_;
        for (size_t i = 0; i < this->capacity_; ++i) {
            this->array[i] = rhs.array_[i];
        }

        return *this;
    }
    ABS(ABS&& other) noexcept {
        this->curr_size_ = other.curr_size_;
        this->capacity_ = other.capacity_;
        this->array_ = other.array_;

        other.curr_size_ = 0;
        other.capacity_ = 0;
        other.array_ = nullptr;
    }
    ABS& operator=(ABS&& rhs) noexcept {
        delete[] this->array_;

        this->curr_size_ = rhs.curr_size_;
        this->capacity_ = rhs.capacity_;
        this->array_ = rhs.array_;

        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;
        rhs.array_ = nullptr;

        return *this;
    }
    ~ABS() noexcept override {
        delete[] this->array_;

        this->curr_size_ = 0;
        this->capacity_ = 0;
        this->array_ = nullptr;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return this->curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return this->capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return this->array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if (this->curr_size_ == this->capacity_) {
            this->realloc(this->capacity_ << 1);
        }
        this->array_[this->curr_size_] = data;
        this->curr_size_ += 1;
    }

    T peek() const override {
        if (this->getSize() == 0) {
            throw std::runtime_error("ABS is empty");
        }
        return this->array_[this->curr_size_ - 1];
    }

    T pop() override {
        if (this->getSize() == 0) {
            throw std::runtime_error("ABS is empty");
        }
        this->curr_size_ -= 1;

        if (this->curr_size <= this->capacity_ / 4) {
            this->realloc(this->capacity_ >> 1);
        }
        return this->array_[this->curr_size_];
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

    void realloc(size_t capacity) {
        T* data = new T[capacity];
        
        for (size_t i = 0; i < this->curr_size_; ++i) {
            data[i] = this->array_[i];
        }

        delete[] this->array_;
        this->array_ = data;
        this->capacity_ = capacity;
    }
};
