#pragma once

#include "Interfaces.hpp"
#include <cstddef>
#include <stdexcept>

template <typename T>
class ABDQ : public DequeInterface<T> {
  private:
    T* data_;              // underlying dynamic array
    std::size_t capacity_; // total allocated capacity
    std::size_t size_;     // number of stored elements
    std::size_t front_;    // index of front element
    std::size_t back_;     // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

    void realloc(size_t capacity) {

        T* data = new T[capacity];

        size_t index;
        for (size_t i = 0; i < this->capacity_; ++i) {
            index = this->front_ + i + 1;
            if (index >= this->capacity_)
                index -= this->capacity_;

            data[i] = this->data_[index];
        }

        delete[] this->data_;
        this->data_ = data;
        this->capacity_ = capacity;
        this->front_ = this->capacity_ - 1;
        this->back_ = this->size_;
    }

  public:
    // Big 5
    ABDQ() {
        this->capacity_ = 4;
        this->size_ = 0;
        this->front_ = this->capacity_ - 1;
        this->back_ = 0;

        this->data_ = new T[this->capacity_];
    }
    explicit ABDQ(std::size_t capacity) {
        this->capacity_ = capacity;
        this->size_ = 0;
        this->front_ = this->capacity_ - 1;
        this->back_ = 0;

        this->data_ = new T[this->capacity_];
    }
    ABDQ(const ABDQ& other) {
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        this->data_ = new T[this->capacity_];

        for (size_t i = 0; i < this->capacity_; ++i) {
            this->data_[i] = other.data_[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        this->data_ = other.data_;

        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
    }
    ABDQ& operator=(const ABDQ& other) {
        T* data = new T[other.capacity_];

        delete[] this->data_;
        this->data_ = data;

        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;

        for (size_t i = 0; i < this->capacity_; ++i) {
            this->data_[i] = other.data_[i];
        }

        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        delete[] this->data_;

        this->capacity_ = other.capacity_;
        this->size_ = other.size_;
        this->front_ = other.front_;
        this->back_ = other.back_;
        this->data_ = other.data_;

        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;

        return *this;
    }
    ~ABDQ() override {
        delete[] this->data_;

        this->capacity_ = 0;
        this->size_ = 0;
        this->front_ = 0;
        this->back_ = 0;
        this->data_ = nullptr;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (this->size_ == this->capacity_) {
            this->realloc(this->capacity_ << 1);
        }

        this->data_[this->front_] = item;
        this->front_ = this->front_ == 0 ? this->capacity_ - 1 : this->front_ - 1;
        this->size_ += 1;
    }
    void pushBack(const T& item) override {
        if (this->size_ == this->capacity_) {
            this->realloc(this->capacity_ << 1);
        }

        this->data_[this->back_] = item;
        this->back_ = this->back_ == this->capacity_ - 1 ? 0 : this->back_ + 1;
        this->size_ += 1;
    }

    // Deletion
    T popFront() override {
        if (this->getSize() == 0) {
            throw std::runtime_error("ABDQ is empty");
        }
        this->front_ = this->front_ == this->capacity_ - 1 ? 0 : this->front_ + 1;
        this->size_ -= 1;

        T data = this->data_[this->front_];

        return data;
    }
    T popBack() override {
        if (this->getSize() == 0) {
            throw std::runtime_error("ABDQ is empty");
        }
        this->back_ = this->back_ == 0 ? this->capacity_ - 1 : this->back_ - 1;
        this->size_ -= 1;

        T data = this->data_[this->back_];

        return data;
    }

    // Access
    const T& front() const override {
        if (this->getSize() == 0) {
            throw std::runtime_error("ABDQ is empty");
        }

        size_t index = this->front_ + 1;
        if (index >= this->capacity_) index -= this->capacity_;

        return this->data_[index];
    }
    const T& back() const override {
        if (this->getSize() == 0) {
            throw std::runtime_error("ABDQ is empty");
        }

        size_t index = this->back_ - 1;
        if (index >= this->capacity_) index -= this->capacity_;

        return this->data_[index];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return this->size_;
    }

    std::size_t getMaxCapacity() const noexcept {
        return this->capacity_;
    }
};
