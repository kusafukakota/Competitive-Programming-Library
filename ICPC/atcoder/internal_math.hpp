#ifndef ATCODER_INTERNAL_MATH_HPP
#define ATCODER_INTERNAL_MATH_HPP 1

#include <utility>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

namespace internal {

constexpr long long safe_mod(long long x, long long m) {
  x %= m;
  if(x < 0) { x += m; }
  return x;
}

struct barrett {
  unsigned int _m;
  unsigned long long im;
  explicit barrett(unsigned int m): _m(m), im((unsigned long long)(-1) / m + 1) {}
  unsigned int umod() const { return _m; }
  unsigned int mul(unsigned int a, unsigned int b) const {
    unsigned long long z = a;
    z *= b;
#ifdef _MSC_VER
    unsigned long long x;
    _umul128(z, im, &x);
#else
    unsigned long long x = (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
    unsigned long long y = x * _m;
    return (unsigned int)(z - y + (z < y ? _m : 0));
  }
};

constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
  if(m == 1) { return 0; }
  unsigned int _m = (unsigned int)(m);
  unsigned long long r = 1;
  unsigned long long y = safe_mod(x, m);
  while(n) {
    if(n & 1) { r = (r * y) % _m; }
    y = (y * y) % _m;
    n >>= 1;
  }
  return r;
}

constexpr bool is_prime_constexpr(int n) {
  if(n <= 1) { return false; }
  if(n == 2 || n == 7 || n == 61) { return true; }
  if(n % 2 == 0) { return false; }
  long long d = n - 1;
  while(d % 2 == 0) d /= 2;
  constexpr long long bases[3] = {2, 7, 61};
  for(long long a : bases) {
    long long t = d;
    long long y = pow_mod_constexpr(a, t, n);
    while(t != n - 1 && y != 1 && y != n - 1) {
      y = y * y % n;
      t <<= 1;
    }
    if(y != n - 1 && t % 2 == 0) { return false; }
  }
  return true;
}
template<int n> constexpr bool is_prime = is_prime_constexpr(n);

constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
  a = safe_mod(a, b);
  if(a == 0) return {b, 0};
  long long s = b, t = a;
  long long m0 = 0, m1 = 1;
  while(t) {
    long long u = s / t;
    s -= t * u;
    m0 -= m1 * u;
    auto tmp = s;
    s = t;
    t = tmp;
    tmp = m0;
    m0 = m1;
    m1 = tmp;
  }
  if(m0 < 0) { m0 += b / s; }
  return {s, m0};
}

constexpr int primitive_root_constexpr(int m) {
  if(m == 2) { return 1; }
  if(m == 167772161) { return 3; }
  if(m == 469762049) { return 3; }
  if(m == 754974721) { return 11; }
  if(m == 998244353) { return 3; }
  int divs[20] = {};
  divs[0] = 2;
  int cnt = 1;
  int x = (m - 1) / 2;
  while(x % 2 == 0) { x /= 2; }
  for(int i = 3; (long long)(i)*i <= x; i += 2) {
    if(x % i == 0) {
      divs[cnt++] = i;
      while(x % i == 0) { x /= i; }
    }
  }
  if(x > 1) { divs[cnt++] = x; }
  for(int g = 2;; g++) {
    bool ok = true;
    for(int i = 0; i < cnt; i++) {
      if(pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
        ok = false;
        break;
      }
    }
    if(ok) { return g; }
  }
}
template<int m> constexpr int primitive_root = primitive_root_constexpr(m);

unsigned long long floor_sum_unsigned(unsigned long long n, unsigned long long m, unsigned long long a, unsigned long long b) {
  unsigned long long ans = 0;
  while(true) {
    if(a >= m) {
      ans += n * (n - 1) / 2 * (a / m);
      a %= m;
    }
    if(b >= m) {
      ans += n * (b / m);
      b %= m;
    }
    unsigned long long y_max = a * n + b;
    if(y_max < m) break;
    n = (unsigned long long)(y_max / m);
    b = (unsigned long long)(y_max % m);
    std::swap(m, a);
  }
  return ans;
}

}  // namespace internal

}  // namespace atcoder

#endif  // ATCODER_INTERNAL_MATH_HPP
