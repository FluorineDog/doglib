#pragma once
namespace doglib {
namespace common {


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