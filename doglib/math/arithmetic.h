#include "../common/constant.h"
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

ull gcd(ull a, ull b) {
    while(b != 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

// struct frac_t {
//     int up;
//     int down;
//     operator<(){
//         //
//     }
// };

std::pair<ull, ull> frac_between(ull a, ull b, ull c, ull d) {
    if(!a) {
        return std::make_pair(1, c / d + 1);
    }
    if(a > b) {
        auto i = a / b;
        auto pr = frac_between(a - i * b, b, c - i * d, d);
        pr.first += i * pr.second; 
        return pr;
    }
    if(c > d){
        return std::make_pair(1LL, 1LL);
    }
    auto pr = frac_between(d, c, b, a);
    return std::make_pair(pr.second, pr.first);
}

}    // namespace math
}    // namespace doglib