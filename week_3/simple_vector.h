#pragma once

#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector
{
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size) : data_(new T[size]), size_(size), capacity_(size) {}
    ~SimpleVector() { delete[] data_; }

    T &operator[](size_t index) { return data_[index]; }

    T *begin() { return data_; }
    T *end() { return data_ + size_; }

    const T *begin() const { return data_; }
    const T *end() const { return data_ + size_; }

    size_t Size() const { return size_; }
    size_t Capacity() const { return capacity_; }
    void PushBack(const T &value)
    {
        if (size_ == capacity_) {
            if (capacity_ == 0) {
                capacity_ = 1;
            } else {
                capacity_ = 2 * capacity_;
            }

            T *temp = new T[capacity_];

            for (size_t i = 0; i < size_; i++) {
                temp[i] = data_[i];
            }
            
            delete[] data_;
            data_ = temp;
        }

        data_[size_] = value;
        size_++;
    }

private:
    // Добавьте поля для хранения данных вектора
    T *data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};
