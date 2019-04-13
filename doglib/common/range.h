#pragma once
namespace doglib {
namespace common {
namespace impl {
template <class T>
class RangeImpl {
  public:
    RangeImpl(T beg, T end) : beg(beg), end(end) {}
    DataIter<T> begin() {
        return DataIter<T>(beg);
    }
    DataIter<T> end() {
        return DataIter<T>(end);
    }
  private:
    T beg, end;
};

}    // namespace impl

template <typename T>
inline auto Range(T beg, T end) -> impl::RangeImpl<T> {
    return RangeImpl(beg, end);
}

template <typename T>
inline auto Range(T end) -> impl::RangeImpl<T> {
    return RangeImpl(T(0), end);
}

}    // namespace std
}    // namespace doglib