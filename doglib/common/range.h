#pragma once
#include "iter.h"
namespace doglib {
namespace common {
namespace impl {
template <class T>
class RangeImpl {
  public:
    RangeImpl(T beg, T end) : beg_(beg), end_(end) {}
    DataIter<T> begin() {
        return DataIter<T>(beg_);
    }
    DataIter<T> end() {
        return DataIter<T>(end_);
    }
  private:
    T beg_, end_;
};

}    // namespace impl

template <typename T>
inline auto Range(T beg, T end) -> impl::RangeImpl<T> {
    return impl::RangeImpl<T>(beg, end);
}

template <typename T>
inline auto Range(T end) -> impl::RangeImpl<T> {
    return impl::RangeImpl<T>(T(0), end);
}

}    // namespace std
}    // namespace doglib