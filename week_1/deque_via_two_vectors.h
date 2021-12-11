#include <iostream>
#include <vector>
#include <exception>

using namespace std;

template<typename T>
class Deque {
private:
    vector <T> data_front;
    vector <T> data_back;

public:
    Deque() = default;

    [[nodiscard]] bool Empty() const {
        return data_front.empty() && data_back.empty();
    }

    [[nodiscard]] size_t Size() const {
        return data_front.size() + data_back.size();
    }

    const T &operator[](const size_t &index) const {
//        if (data_front.size() <= index) {
//            return data_back[index - data_front.size()];
//        } else {
//            return data_front[data_front.size() - index - static_cast<size_t>(1)];
//        }
        return At(index);
    }

    T &operator[](const size_t &index) {
//        if (data_front.size() <= index) {
//            return data_back[index - data_front.size()];
//        } else {
//            return data_front[data_front.size() - index - static_cast<size_t>(1)];
//        }
        return At(index);
    }

    const T &At(const size_t &index) const {
        if (Size() <= index) {
            throw out_of_range("At: out of range");
        } else if (data_front.size() <= index) {
            return data_back[index - data_front.size()];
        } else {
            return data_front[data_front.size() - index - static_cast<size_t>(1)];
        }
    }

    T &At(const size_t &index) {
        if (Size() <= index) {
            throw out_of_range("At: out of range");
        } else if (data_front.size() <= index) {
            return data_back[index - data_front.size()];
        } else {
            return data_front[data_front.size() - index - static_cast<size_t>(1)];
        }
    }

    const T &Front() const {
        return At(0);
    }

    T &Front() {
        return At(0);
    }

    const T &Back() const {
        return At(Size() - static_cast<size_t>(1));
    }

    T &Back() {
        return At(Size() - static_cast<size_t>(1));
    }

    void PushFront(const T &value) {
        data_front.emplace_back(value);
    }

    void PushBack(const T &value) {
        data_back.emplace_back(value);
    }
};
