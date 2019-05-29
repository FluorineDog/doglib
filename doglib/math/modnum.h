#pragma once

namespace doglib {
namespace math {

using ull = long long;
// find out leading zeros
int clz(ull x) {
    return __builtin_clzll(x);
}

template <ull mod, bool is_prime = false>
class ModNum {
  public:
    ModNum(ull x) : data(x % mod) {}

    friend ModNum operator+(const ModNum& a, const ModNum& b) {
        return (a.data + b.data) % mod;
    }

    friend ModNum operator-(const ModNum& a) {
        return mod - a.data;
    }

    friend ModNum operator-(const ModNum& a, const ModNum& b) {
        return (a.data + mod - b.data) % mod;
    }

    friend ModNum operator*(const ModNum& a, const ModNum& b) {
        return (a.data * b.data) % mod;
    }

    ModNum& operator+=(const ModNum& x) {
        return *this = *this + x;
    }
    ModNum& operator-=(const ModNum& x) {
        return *this = *this - x;
    }
    ModNum& operator*=(const ModNum& x) {
        return *this = *this * x;
    }
    ModNum& operator/=(const ModNum& x) {
        return *this = *this / x;
    }

    ModNum pow(ull exp) const {
        if(exp == 0) return 1;
        int count1s = (int)sizeof(ull) * 8 - clz(exp);
        ModNum x = 1;
        for(int shift = count1s; shift-- > 0;) {
            x = x * x;
            if((exp >> shift) & 1) {
                x = x * data;
            }
        }
        return x;
    }

    ModNum rev() const {
        static_assert(is_prime, "mod must be prime");
        auto ans = this->pow(mod - 2);
        assert((ull)(ans * (*this)) == 1);
        return ans;
    }

    friend ModNum operator/(const ModNum& a, const ModNum& b) {
        static_assert(is_prime, "mod must be prime");
        return a * b.rev();
    }

    explicit operator ull() {
        return data;
    }

  protected:
    ull data;
};

template <ull mod>
using PrimeModNum = ModNum<mod, true>;

}    // namespace math
}    // namespace doglib