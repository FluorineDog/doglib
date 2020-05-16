#pragma once
#include <unistd.h>
#include <type_traits>
#include <iterator>
namespace doglib {
namespace common {

template <typename T>
class DataIter {
  public:
    using difference_type = ssize_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;

    static_assert(std::is_integral<T>::value, "support integer only");
    DataIter(T data) : data(data) {}
    const T& operator*() const {
        return data;
    }
    DataIter<T>& operator++() {
        ++data;
        return *this;
    }
    DataIter<T> operator++(int) {
        auto x = *this;
        ++data;
        return std::move(x);
    }
    DataIter<T>& operator--() {
        --data;
        return *this;
    }
    DataIter<T> operator--(int) {
        auto x = *this;
        --data;
        return std::move(x);
    }

    // that's why everyone loves spaceship operator
    bool operator!=(const DataIter<T>& t) const {
        return data != t.data;
    }
    bool operator<(const DataIter<T>& t) const {
        return data < t.data;
    }
    bool operator==(const DataIter<T>& t) const {
        return !(*this != t);
    }
    bool operator>(const DataIter<T>& t) const {
        return t < *this;
    }
    bool operator<=(const DataIter<T>& t) const {
        return !(t < *this);
    }
    bool operator>=(const DataIter<T>& t) const {
        return !(*this < t);
    }
    // for random access, in case for binary search
    ssize_t operator-(const DataIter<T>& t) const {
        return data - t.data;
    }
    DataIter<T>& operator+=(ssize_t n) {
        data += (T)n;
        return *this;
    }
    DataIter<T>& operator-=(ssize_t n) {
        data -= (T)n;
        return *this;
    }
    DataIter<T> operator+(ssize_t n) const {
        auto tmp = *this;
        tmp += (T)n;
        return tmp;
    }
    DataIter<T> operator-(ssize_t n) const {
        auto tmp = *this;
        tmp -= (T)n;
        return tmp;
    }

  private:
    T data;
};
template <typename T>
auto make_iter(T x) -> DataIter<T> {
    return DataIter<T>(x);
}
}    // namespace common
}    // namespace doglib

//namespace std{
//template <typename T>
//// template <>
//struct iterator_traits< doglib::common::DataIter<T>> {
//    using difference_type = ssize_t;
//    using value_type = T;
//    using pointer = T*;
//    using reference = T&;
//    using iterator_category = std::random_access_iterator_tag;
//};
//}
