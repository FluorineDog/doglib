namespace doglib {
namespace std {

template <typename T>
class DataIter {
  public:
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
    bool operator!=(DataIter<T>& t) const {
        return data != t.data;
    }
    bool operator<(DataIter<T>& t) const {
        return data < t.data;
    }
    bool operator==(DataIter<T>& t) const {
        return !(*this != t);
    }
    bool operator>(DataIter<T>& t) const {
        return t < *this;
    }
    bool operator<=(DataIter<T>& t) const {
        return !(t < *this);
    }
    bool operator>=(DataIter<T>& t) const {
        return !(*this < t);
    }
    // for random access, in case for binary search
    ssize_t operator-(DataIter<T>& t) const {
        return data - t.data;
    }
    DataIter<T>& operator+=(ssize_t n) {
        data += n;
        return *this;
    }
    DataIter<T>& operator-=(ssize_t n)  {
        data -= n;
        return *this;
    }
    DataIter<T> operator+(ssize_t n) const {
        int tmp = *this;
        tmp += n;
        return tmp;
    }
    DataIter<T> operator-(ssize_t n) const {
        int tmp = *this;
        tmp -= n;
        return tmp;
    }
  private:
    T data;
};
template <typename T>
auto make_iter(T x) -> DataIter<T> {
    return DataIter<T>(x);
}

namespace impl {
template <class T>
class RangeImpl {
  public:
    RangeImpl(T beg, T end) : beg(beg), end(end) {}
    DataIter<T> begin() {
        return
    }

  private:
    T beg, end;
}

}    // namespace impl

template <typename T>
inline auto Range(T beg, T end) -> impl::RangeImpl<T> {
    return
}

}    // namespace std
}    // namespace doglib