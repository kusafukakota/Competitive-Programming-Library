#include <bits/stdc++.h>
using namespace std;
#include <atcoder/segtree>
using namespace atcoder;
using ll = long long;

struct Modint2_61 {
  static constexpr unsigned long long MOD = (1ULL << 61) - 1;
  unsigned long long x;
  constexpr Modint2_61(): x(0ULL) {}
  constexpr Modint2_61(unsigned long long y): x(y >= MOD ? y - MOD : y) { assert(y < MOD * 2); }
  unsigned long long val() const noexcept { return x; }
  Modint2_61 operator-() const { return Modint2_61(MOD - x); }
  Modint2_61 operator+(const Modint2_61 &a) const { return Modint2_61(x + a.x); }
  Modint2_61 operator-(const Modint2_61 &a) const { return Modint2_61(x + MOD - a.x); }
  Modint2_61 operator*(const Modint2_61 &a) const {
    __uint128_t r = __uint128_t(x) * a.x;
    r = (r >> 61) + (r & MOD);
    return Modint2_61(r);
  }
  Modint2_61 operator/(const Modint2_61 &a) const { return *this * a.inv(); }
  Modint2_61 pow(ll n) const {
    if(n < 0) { return inv().pow(-n); }
    Modint2_61 r(1), t = *this;
    while(n) {
      if(n & 1) { r *= t; }
      t *= t;
      n >>= 1;
    }
    return r;
  }
  Modint2_61 inv() const { return pow(MOD - 2); }
  Modint2_61 &operator+=(const Modint2_61 &a) { return *this = *this + a; }
  Modint2_61 &operator-=(const Modint2_61 &a) { return *this = *this - a; }
  Modint2_61 &operator*=(const Modint2_61 &a) { return *this = *this * a; }
  Modint2_61 &operator/=(const Modint2_61 &a) { return *this = *this / a; }
  template<typename T> friend Modint2_61 operator+(T a, const Modint2_61 &b) { return (Modint2_61(a) += b); }
  template<typename T> friend Modint2_61 operator-(T a, const Modint2_61 &b) { return (Modint2_61(a) -= b); }
  template<typename T> friend Modint2_61 operator*(T a, const Modint2_61 &b) { return (Modint2_61(a) *= b); }
  template<typename T> friend Modint2_61 operator/(T a, const Modint2_61 &b) { return (Modint2_61(a) /= b); }
  explicit operator bool() const { return x; }
  bool operator==(const Modint2_61 &a) const { return (x == a.x); }
  bool operator!=(const Modint2_61 &a) const { return (x != a.x); }
  bool operator<(const Modint2_61 &a) const { return x < a.x; }  // to use map
  friend ostream &operator<<(ostream &os, const Modint2_61 &a) { return os << a.x; }
};

using mint = Modint2_61;
const unsigned long long base = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count() % Modint2_61::MOD;

vector<mint> power;

struct S {
  mint h1, h2;
  ll len;
};
S op(S l, S r) {
  S re;
  re.h1 = l.h1 * power[r.len] + r.h1;
  re.h2 = l.h2 + r.h2 * power[l.len];
  re.len = l.len + r.len;
  return re;
}
S e() { return {0, 0, 0}; }

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, q;
  string s;
  cin >> n >> q >> s;

  power.assign(n + 1, 1);
  for(ll i = 0; i < n; i++) { power[i + 1] = power[i] * base; }

  vector<S> v(n);
  for(ll i = 0; i < n; i++) {
    v[i].h1 = v[i].h2 = s[i];
    v[i].len = 1;
  }
  segtree<S, op, e> seg(v);

  while(q--) {
    ll type;
    cin >> type;
    if(type == 1) {
      ll x;
      char c;
      cin >> x >> c;
      seg.set(x - 1, {c, c, 1});
    }
    else {
      ll l, r;
      cin >> l >> r;
      l--;
      auto [h1, h2, len] = seg.prod(l, r);
      cout << (h1 == h2 ? "Yes" : "No") << "\n";
    }
  }
}
