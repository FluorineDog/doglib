#include "../common/constants.h"
namespace doglib {
namespace math {
template <class T, class U>
T pow_int(T x, U y) {
    U offset = 1;
    while(offset < y) {
        offset <<= 1;
    }
    T acc = 1;
    while(offset) {
        acc = acc * acc;
        if(offset & y) {
            acc *= x;
        }
        offset >>= 1;
    }
    return acc;
}

}    // namespace math
}    // namespace doglib