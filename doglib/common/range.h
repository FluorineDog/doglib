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

template <typename T>
struct reverse_wrapper { T& iterable; };

template <typename T>
auto begin (reverse_wrapper<T> w) { return std::rbegin(w.iterable); }

template <typename T>
auto end (reverse_wrapper<T> w) { return std::rend(w.iterable); }

template <typename T>
reverse_wrapper<T> reverse_wrap (T&& iterable) { return { iterable }; }


}    // namespace std
}    // namespace doglib