#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using ll = long long;
using mint = modint998244353;

template<typename T = mint> struct FPS : vector<T> {
  using vector<T>::vector;
  using vector<T>::operator=;
  FPS pre(ll deg) const { return FPS(begin(*this), begin(*this) + min((ll)this->size(), deg)); }
  FPS rev(ll deg = -1) const {
    FPS r(*this);
    if(deg != -1) r.resize(deg, T(0));
    reverse(r.begin(), r.end());
    return r;
  }
  void shrink() {
    while(this->size() && this->back() == T(0)) this->pop_back();
  }
  FPS operator+(const FPS &f) const { return FPS(*this) += f; }
  FPS operator+(const T &x) const { return FPS(*this) += x; }
  FPS operator-(const FPS &f) const { return FPS(*this) -= f; }
  FPS operator-(const T &x) const { return FPS(*this) -= x; }
  FPS operator*(const FPS &f) const { return FPS(*this) *= f; }
  FPS operator*(const T &x) const { return FPS(*this) *= x; }
  FPS operator/(const FPS &f) const { return FPS(*this) /= f; }
  FPS operator/(const T &x) const { return FPS(*this) /= x; }
  FPS operator%(const FPS &f) const { return FPS(*this) %= f; }
  FPS &operator+=(const FPS &f) {
    if(f.size() > this->size()) this->resize(f.size());
    for(ll i = 0; i < (ll)f.size(); i++) (*this)[i] += f[i];
    return *this;
  }
  FPS &operator-=(const FPS &f) {
    if(f.size() > this->size()) this->resize(f.size());
    for(ll i = 0; i < (ll)f.size(); i++) (*this)[i] -= f[i];
    return *this;
  }
  FPS &operator*=(const FPS &f) {
    if(T::mod() == 998244353) *this = convolution(*this, f);
    else {
      ll n = this->size(), m = f.size();
      vector<ll> a(n), b(m);
      static constexpr ll MOD1 = 754974721, MOD2 = 167772161, MOD3 = 469762049;
      static constexpr ll M1_M2 = internal::inv_gcd(MOD1, MOD2).second, M12_M3 = internal::inv_gcd(MOD1 * MOD2, MOD3).second, M12 = (MOD1 * MOD2) % T::mod();
      for(ll i = 0; i < n; i++) a[i] = (*this)[i].val();
      for(ll i = 0; i < m; i++) b[i] = f[i].val();
      vector<ll> x = convolution<MOD1>(a, b), y = convolution<MOD2>(a, b), z = convolution<MOD3>(a, b);
      vector<T> c(n + m - 1);
      for(ll i = 0; i < n + m - 1; i++) {
        ll v1 = (y[i] - x[i]) * M1_M2 % MOD2;
        if(v1 < 0) v1 += MOD2;
        ll v2 = (z[i] - (x[i] + MOD1 * v1) % MOD3) * M12_M3 % MOD3;
        if(v2 < 0) v2 += MOD3;
        c[i] = x[i] + MOD1 * v1 + M12 * v2;
      }
      *this = c;
    }
    return *this;
  }
  FPS &operator*=(vector<pair<ll, T>> &f) const {
    const ll n = (ll)this->size(), m = f.back().first;
    auto [d, c] = f.front();
    if(d == 0) f.erase(f.begin());
    else c = 0;
    for(ll i = n - 1; i >= 0; i--) {
      (*this)[i] *= c;
      for(auto &[j, b] : f) {
        if(j > i) break;
        (*this)[i] += (*this)[i - j] * b;
      }
    }
    return *this;
  }
  void mul_sparse(const ll d, const T c) {  // *(cx^d + 1)
    ll n = this->size();
    for(ll i = n - d - 1; i >= 0; i--) (*this)[i + d] += (*this)[i] * c;
  }
  FPS &operator/=(const FPS &f) {
    if(this->size() < f.size()) {
      this->clear();
      return *this;
    }
    ll n = this->size() - f.size() + 1;
    return *this = (rev().pre(n) * f.rev().inv(n)).pre(n).rev(n);
  }
  void div_sparse(const ll d, const T c) {  // /(cx^d + 1)
    ll n = this->size();
    for(ll i = 0; i < n - d; i++) (*this)[i + d] -= (*this)[i] * c;
  }
  FPS &operator%=(const FPS &f) { return *this -= *this / f * f; }
  pair<FPS, FPS> div_mod(const FPS &f) {
    FPS g = *this / f;
    return {g, *this - g * f};
  }
  FPS operator-() {
    FPS r(this->size());
    for(ll i = 0; i < (this->size()); i++) r[i] = -(*this)[i];
    return r;
  }
  FPS &operator+=(const T &x) {
    if(this->empty()) this->resize(1);
    (*this)[0] += x;
    return *this;
  }
  FPS &operator-=(const T &x) {
    if(this->empty()) this->resize(1);
    (*this)[0] -= x;
    return *this;
  }
  FPS &operator*=(const T &x) {
    for(ll i = 0; i < (ll)this->size(); i++) (*this)[i] *= x;
    return *this;
  }
  FPS &operator/=(const T &x) {
    for(ll i = 0; i < (ll)this->size(); i++) (*this)[i] /= x;
    return *this;
  }
  FPS operator>>(ll sz) {
    if((ll)this->size() <= sz) return {};
    FPS r(*this);
    r.erase(r.begin(), r.begin() + sz);
    return r;
  }
  FPS operator<<(ll sz) {
    FPS r(*this);
    r.insert(r.begin(), sz, T(0));
    return r;
  }
  FPS dot(const FPS &f) const {
    FPS r(min(this->size(), f.size()));
    for(ll i = 0; i < r.size(); i++) r[i] = (*this)[i] * f[i];
    return r;
  }
  T operator()(T x) const {
    T r = 0, w = 1;
    for(auto &i : (*this)) {
      r += w * i;
      w *= x;
    }
    return r;
  }
  FPS diff() const {
    const int n = (int)this->size();
    FPS r(n);
    for(ll i = 1; i < n; i++) r[i - 1] = (*this)[i] * T(i);
    r[n - 1] = 0;
    return r;
  }
  FPS integral() const {
    ll n = this->size(), mod = T::mod();
    vector<T> inv(n);
    inv[1] = 1;
    for(ll i = 2; i < n; i++) inv[i] = -inv[mod % i] * (mod / i);
    FPS r(n);
    for(ll i = n - 2; i >= 0; i--) r[i + 1] = (*this)[i] * inv[i + 1];
    r[0] = 0;
    return r;
  }
  FPS inv(ll deg = -1) const {
    ll n = this->size();
    if(deg == -1) deg = n;
    assert(n != 0 && (*this)[0] != T(0));
    FPS res{(*this)[0].inv()};
    if(T::mod() == 998244353) {
      while((ll)res.size() < deg) {
        ll d = res.size();
        FPS f(this->begin(), this->begin() + min(n, d * 2)), g(res);
        f.resize(d * 2);
        g.resize(d * 2);
        internal::butterfly(f);
        internal::butterfly(g);
        for(ll i = 0; i < d * 2; i++) f[i] *= g[i];
        internal::butterfly_inv(f);
        f.erase(f.begin(), f.begin() + d);
        f.resize(d * 2);
        internal::butterfly(f);
        for(ll i = 0; i < d * 2; i++) f[i] *= g[i];
        internal::butterfly_inv(f);
        T iz = T(d * 2).inv();
        iz *= -iz;
        for(ll i = 0; i < d; i++) f[i] *= iz;
        res.insert(res.end(), f.begin(), f.begin() + d);
      }
    }
    else {
      for(ll i = 1; i < deg; i <<= 1) res = (res + res - res * res * pre(i << 1)).pre(i << 1);
    }
    return res.pre(deg);
  }
  FPS log(ll deg = -1) const {
    assert((*this)[0] == T(1));
    if(deg == -1) deg = this->size();
    return (this->diff() * this->inv(deg)).pre(deg).integral();
  }
  FPS sqrt(
      ll deg = -1, const function<T(T)> &get_sqrt = [](T) { return T(1); }) const {
    const ll n = (ll)this->size();
    if(deg == -1) deg = n;
    if((*this)[0] == T(0)) {
      for(ll i = 1; i < n; i++) {
        if((*this)[0] != T(0)) {
          if(i & 1) return {};
          if(deg - i / 2 <= 0) break;
          auto r = (*this >> i).sqrt(deg - i / 2, get_sqrt);
          if(r.empty()) return {};
          r = r << (i / 2);
          if(r.size() < deg) r.resize(deg, T(0));
          return r;
        }
      }
      return FPS(deg, 0);
    }
    auto sq = T(get_sqrt((*this)[0]));
    if(sq * sq != (*this)[0]) return {};
    FPS r{sq};
    T inv2 = T(1) / T(2);
    for(ll i = 1; i < deg; i <<= 1) r = (r + pre(i << 1) * r.inv(i << 1)) * inv2;
    return r.pre(deg);
  }
  FPS sqrt(const function<T(T)> &get_sqrt, ll deg = -1) const { return sqrt(deg, get_sqrt); }
  FPS exp(ll deg = -1) const {
    ll n = this->size();
    assert((*this)[0] == T(0));
    if(deg == -1) deg = n;
    if(T::mod() == 998244353) {
      FPS inv;
      inv.reserve(deg);
      inv.emplace_back(T(0));
      inv.emplace_back(T(1));
      auto internal_integral = [&](FPS &f) {
        ll n = f.size(), mod = T::mod();
        while((ll)inv.size() <= n) {
          ll i = inv.size();
          inv.emplace_back((-inv[mod % i]) * (mod / i));
        }
        f.insert(f.begin(), T(0));
        for(ll i = 1; i <= n; i++) f[i] *= inv[i];
      };
      auto internal_diff = [](FPS &f) {
        if(f.empty()) return;
        f.erase(f.begin());
        T c = 1;
        for(ll i = 0; i < (ll)f.size(); i++, c++) f[i] *= c;
      };
      FPS b{1, 1 < (ll)this->size() ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};
      for(ll m = 2; m <= deg; m <<= 1) {
        auto y = b;
        y.resize(m * 2);
        internal::butterfly(y);
        z1 = z2;
        FPS z(m);
        for(ll i = 0; i < m; i++) z[i] = y[i] * z1[i];
        internal::butterfly_inv(z);
        T si = T(m).inv();
        for(ll i = 0; i < m; i++) z[i] *= si;
        fill(z.begin(), z.begin() + m / 2, T(0));
        internal::butterfly(z);
        for(ll i = 0; i < m; i++) z[i] *= -z1[i];
        internal::butterfly_inv(z);
        for(ll i = 0; i < m; i++) z[i] *= si;
        c.insert(c.end(), z.begin() + m / 2, z.end());
        z2 = c;
        z2.resize(m * 2);
        internal::butterfly(z2);
        FPS x(this->begin(), this->begin() + min((ll)this->size(), m));
        x.resize(m);
        internal_diff(x);
        x.emplace_back(T(0));
        internal::butterfly(x);
        for(ll i = 0; i < m; i++) x[i] *= y[i];
        internal::butterfly_inv(x);
        for(ll i = 0; i < m; i++) x[i] *= si;
        x -= b.diff();
        x.resize(m * 2);
        for(ll i = 0; i < m - 1; i++) {
          x[m + i] = x[i];
          x[i] = T(0);
        }
        internal::butterfly(x);
        for(ll i = 0; i < m * 2; i++) x[i] *= z2[i];
        internal::butterfly_inv(x);
        T si2 = T(m << 1).inv();
        for(ll i = 0; i < m * 2; i++) x[i] *= si2;
        x.pop_back();
        internal_integral(x);
        for(ll i = m; i < min((ll)this->size(), m * 2); i++) x[i] += (*this)[i];
        fill(x.begin(), x.begin() + m, T(0));
        internal::butterfly(x);
        for(ll i = 0; i < m * 2; i++) x[i] *= y[i];
        internal::butterfly_inv(x);
        for(ll i = 0; i < m * 2; i++) x[i] *= si2;
        b.insert(b.end(), x.begin() + m, x.end());
      }
      return b.pre(deg);
    }
    else {
      FPS r({T(1)});
      for(ll i = 1; i < deg; i <<= 1) r = (r * (pre(i << 1) + T(1) - r.log(i << 1))).pre(i << 1);
      return r.pre(deg);
    }
  }
  FPS pow(ll k) {
    ll n = (ll)this->size();
    assert(k >= 0);
    if(k == 0) {
      FPS r(n, T(0));
      r[0] = T(1);
      return r;
    }
    for(ll i = 0; i < n; i++) {
      if(i * k > n) return FPS(n, T(0));
      if((*this)[i] != T(0)) {
        T rev = (*this)[i].inv();
        FPS r = (((*this * rev) >> i).log() * k).exp() * ((*this)[i].pow(k));
        r = (r << (i * k)).pre(n);
        if((ll)r.size() < n) r.resize(n, T(0));
        return r;
      }
    }
    return *this;
  }
  FPS mod_pow(ll k, FPS f) const {
    FPS modinv = f.rev().inv();
    auto get_div = [&](FPS base) {
      if(base.size() < f.size()) {
        base.clear();
        return base;
      }
      ll n = base.size() - f.size() + 1;
      return (base.rev().pre(n) * modinv.pre(n)).pre(n).rev(n);
    };
    FPS x(*this), r{1};
    while(k > 0) {
      if(k & 1) {
        r *= x;
        r -= get_div(r) * f;
        r.shrink();
      }
      x *= x;
      x -= get_div(x) * f;
      x.shrink();
      k >>= 1;
    }
    return r;
  }
  FPS taylor_shift(T c) const {  // g(x) s.t. g(x)=f(x+c)
    ll n = (ll)this->size();
    vector<T> fact(n), rfact(n);
    fact[0] = rfact[0] = T(1);
    for(ll i = 1; i < n; i++) fact[i] = fact[i - 1] * T(i);
    rfact[n - 1] = T(1) / fact[n - 1];
    for(ll i = n - 1; i >= 2; i--) rfact[i - 1] = rfact[i] * T(i);
    FPS r(*this);
    for(ll i = 0; i < n; i++) r[i] *= fact[i];
    r = r.rev();
    FPS bs(n, T(1));
    for(ll i = 1; i < n; i++) bs[i] = bs[i - 1] * c * rfact[i] * fact[i - 1];
    r = (r * bs).pre(n);
    r = r.rev();
    for(ll i = 0; i < n; i++) r[i] *= rfact[i];
    return r;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll q, k;
  cin >> q >> k;
  FPS<mint> f(k + 1, 0);
  f[0] = 1;
  while(q--) {
    char op;
    ll x;
    cin >> op >> x;
    if(op == '+') {
      f.mul_sparse(x, 1);
    }
    else {
      f.div_sparse(x, 1);
    }
    cout << f[k].val() << "\n";
  }
}
