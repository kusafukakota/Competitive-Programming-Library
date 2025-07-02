#pragma once

#include <atcoder/convolution>
using namespace atcoder;

struct FPS : vector<mint> {
  using vector<mint>::vector;
  using vector<mint>::operator=;
  ll MOD = mint::mod();
  bool FAST = !((MOD - 1) & ((1 << 23) - 1));
  FPS pre(int deg) const {
    FPS r((*this).begin(), (*this).begin() + min((int)this->size(), deg));
    if((int)r.size() < deg) { r.resize(deg); }
    return r;
  }
  FPS rev(int deg = -1) const {
    FPS r(*this);
    if(deg != -1) { r.resize(deg, mint(0)); }
    ranges::reverse(r);
    return r;
  }
  void shrink() {
    while(this->size() && this->back() == mint(0)) { this->pop_back(); }
  }
  FPS operator+(const FPS &f) const { return FPS(*this) += f; }
  FPS operator+(const mint &x) const { return FPS(*this) += x; }
  FPS operator-(const FPS &f) const { return FPS(*this) -= f; }
  FPS operator-(const mint &x) const { return FPS(*this) -= x; }
  FPS operator*(const FPS &f) const { return FPS(*this) *= f; }
  template<typename I> FPS operator*(const vector<pair<I, mint>> &f) const { return FPS(*this) *= f; }
  template<typename I> FPS operator*(const pair<I, mint> &f) const { return FPS(*this) *= f; }
  FPS operator*(const mint &x) const { return FPS(*this) *= x; }
  FPS operator/(const FPS &f) const { return FPS(*this) /= f; }
  template<typename I> FPS operator/(vector<pair<I, mint>> &f) const { return FPS(*this) /= f; }
  template<typename I> FPS operator/(const pair<I, mint> &f) const { return FPS(*this) /= f; }
  FPS operator/(const mint &x) const { return FPS(*this) /= x; }
  FPS operator%(const FPS &f) const { return FPS(*this) %= f; }
  FPS &operator+=(const FPS &f) {
    if(f.size() > this->size()) { this->resize(f.size()); }
    for(int i = 0; i < (int)f.size(); i++) { (*this)[i] += f[i]; }
    return *this;
  }
  FPS &operator-=(const FPS &f) {
    if(f.size() > this->size()) { this->resize(f.size()); }
    for(int i = 0; i < (int)f.size(); i++) { (*this)[i] -= f[i]; }
    return *this;
  }
  FPS &operator*=(const FPS &f) {
    if(FAST) { *this = convolution(*this, f); }
    else {
      const int n = this->size(), m = f.size();
      vector<ll> a(n), b(m);
      static constexpr ll MOD1 = 754974721, MOD2 = 167772161, MOD3 = 469762049;
      static constexpr ll M1_M2 = internal::inv_gcd(MOD1, MOD2).second, M12_M3 = internal::inv_gcd(MOD1 * MOD2, MOD3).second;
      ll M12 = (MOD1 * MOD2) % MOD;
      for(int i = 0; i < n; i++) { a[i] = (*this)[i].val(); }
      for(int i = 0; i < m; i++) { b[i] = f[i].val(); }
      vector<ll> x = convolution<MOD1>(a, b), y = convolution<MOD2>(a, b), z = convolution<MOD3>(a, b);
      vector<mint> c(n + m - 1);
      for(int i = 0; i < n + m - 1; i++) {
        ll v1 = (y[i] - x[i]) * M1_M2 % MOD2;
        if(v1 < 0) { v1 += MOD2; }
        ll v2 = (z[i] - (x[i] + MOD1 * v1) % MOD3) * M12_M3 % MOD3;
        if(v2 < 0) { v2 += MOD3; }
        c[i] = x[i] + MOD1 * v1 + M12 * v2;
      }
      *this = c;
    }
    return *this;
  }
  template<typename I> FPS &operator*=(const vector<pair<I, mint>> &f) {
    const int n = this->size() - 1, m = f.back().first;
    FPS r(n + m + 1, 0);
    for(int i = 0; i <= n; i++) {
      for(auto &[j, c] : f) { r[i + j] += (*this)[i] * c; }
    }
    return *this = r;
  }
  template<typename I> FPS &operator*=(const pair<I, mint> &f) {  // *(cx^d + 1)
    const int n = this->size();
    auto [d, c] = f;
    for(int i = n - d - 1; i >= 0; i--) { (*this)[i + d] += (*this)[i] * c; }
    return *this;
  }
  FPS &operator/=(const FPS &f) {
    if(this->size() < f.size()) {
      this->clear();
      return *this;
    }
    return *this *= f.inv();
  }
  template<typename I> FPS &operator/=(vector<pair<I, mint>> &f) {
    ranges::sort(f, [&](auto x, auto y) { return x.first > y.first; });
    const ll n = this->size() - 1, m = f[0].first;
    FPS r(n - m + 1, 0);
    for(int i = n - m; i >= 0; i--) {
      r[i] = (*this)[i + m] / f[0].second;
      for(auto &[j, c] : f) { (*this)[i + j] -= r[i] * c; }
    }
    return *this = r;
  }
  template<typename I> FPS &operator/=(const pair<I, mint> &f) {  // /(cx^d + 1)
    const int n = this->size();
    auto [d, c] = f;
    for(int i = 0; i < n - d; i++) { (*this)[i + d] -= (*this)[i] * c; }
    return *this;
  }
  FPS &operator%=(const FPS &f) { return *this -= *this / f * f; }
  pair<FPS, FPS> div_mod(const FPS &f) {
    FPS g = *this / f;
    return {g, *this - g * f};
  }
  FPS operator-() {
    FPS r(this->size());
    for(int i = 0; i < (int)(this->size()); i++) { r[i] = -(*this)[i]; }
    return r;
  }
  FPS &operator+=(const mint &x) {
    if(this->empty()) { this->resize(1); }
    (*this)[0] += x;
    return *this;
  }
  FPS &operator-=(const mint &x) {
    if(this->empty()) { this->resize(1); }
    (*this)[0] -= x;
    return *this;
  }
  FPS &operator*=(const mint &x) {
    for(int i = 0; i < (int)this->size(); i++) { (*this)[i] *= x; }
    return *this;
  }
  FPS &operator/=(const mint &x) {
    for(int i = 0; i < (int)this->size(); i++) { (*this)[i] /= x; }
    return *this;
  }
  FPS operator>>(ll sz) {
    if((int)this->size() <= sz) { return {}; }
    FPS r(*this);
    r.erase(r.begin(), r.begin() + sz);
    return r;
  }
  FPS operator<<(ll sz) {
    FPS r(*this);
    r.insert(r.begin(), sz, mint(0));
    return r;
  }
  FPS dot(const FPS &f) const {
    FPS r(min(this->size(), f.size()));
    for(int i = 0; i < (int)r.size(); i++) { r[i] = (*this)[i] * f[i]; }
    return r;
  }
  mint operator()(mint x) const {
    mint r = 0, w = 1;
    for(auto &i : (*this)) {
      r += w * i;
      w *= x;
    }
    return r;
  }
  FPS diff() const {
    const int n = this->size();
    FPS r(n);
    for(int i = 1; i < n; i++) { r[i - 1] = (*this)[i] * mint(i); }
    r[n - 1] = 0;
    return r;
  }
  FPS integral() const {
    const int n = this->size();
    vector<mint> inv(n);
    inv[1] = 1;
    for(int i = 2; i < n; i++) { inv[i] = -inv[MOD % i] * (MOD / i); }
    FPS r(n);
    for(int i = n - 2; i >= 0; i--) { r[i + 1] = (*this)[i] * inv[i + 1]; }
    r[0] = 0;
    return r;
  }
  FPS inv(ll deg = -1) const {
    const int n = this->size();
    if(deg == -1) { deg = n; }
    assert(n && (*this)[0] != mint(0));
    FPS res{(*this)[0].inv()};
    if(FAST) {
      while((int)res.size() < deg) {
        int d = res.size();
        FPS f(this->begin(), this->begin() + min(n, d * 2)), g(res);
        f.resize(d * 2);
        g.resize(d * 2);
        internal::butterfly(f);
        internal::butterfly(g);
        for(int i = 0; i < d * 2; i++) { f[i] *= g[i]; }
        internal::butterfly_inv(f);
        f.erase(f.begin(), f.begin() + d);
        f.resize(d * 2);
        internal::butterfly(f);
        for(int i = 0; i < d * 2; i++) { f[i] *= g[i]; }
        internal::butterfly_inv(f);
        mint iz = mint(d * 2).inv();
        iz *= -iz;
        for(int i = 0; i < d; i++) { f[i] *= iz; }
        res.insert(res.end(), f.begin(), f.begin() + d);
      }
    }
    else {
      for(int i = 1; i < deg; i <<= 1) { res = (res + res - res * res * pre(i << 1)).pre(i << 1); }
    }
    return res.pre(deg);
  }
  FPS log(ll deg = -1) const {
    assert((*this)[0] == mint(1));
    if(deg == -1) { deg = this->size(); }
    return (this->diff() * this->inv(deg)).pre(deg).integral();
  }
  FPS sqrt(ll deg = -1) {
    const int n = this->size();
    if(deg == -1) { deg = n; }
    if((*this)[0] == mint(0)) {
      for(int i = 1; i < n; i++) {
        if((*this)[i] != mint(0)) {
          if(i & 1) { return {}; }
          if(deg - i / 2 <= 0) { break; }
          auto r = (*this >> i).sqrt(deg - i / 2);
          if(r.empty()) { return {}; }
          r = r << (i / 2);
          if((int)r.size() < deg) { r.resize(deg, mint(0)); }
          return r;
        }
      }
      return FPS(deg, 0);
    }
    auto mod_sqrt = [&](const ll &a) -> ll {
      ll m = MOD - 1, e = 0;
      if(!a) { return 0; }
      if(MOD == 2) { return a; }
      if(mint(a).pow(m >> 1) != 1) { return -1; }
      mint b = 1;
      while(b.pow(m >> 1) == 1) { b++; }
      while(~m & 1) {
        m >>= 1;
        e++;
      }
      mint x = mint(a).pow((m - 1) >> 1), y = mint(a) * x * x, z = mint(b).pow(m);
      x *= a;
      while(y != 1) {
        ll j = 0;
        mint t = y;
        while(t != 1) {
          j++;
          t *= t;
        }
        z = z.pow(1LL << (e - j - 1));
        x *= z;
        z *= z;
        y *= z;
        e = j;
      }
      return x.val();
    };
    auto sq = mint(mod_sqrt((*this)[0].val()));
    if(sq * sq != (*this)[0]) { return {}; }
    FPS r{sq};
    mint inv2 = mint(1) / mint(2);
    for(int i = 1; i < deg; i <<= 1) { r = (r + pre(i << 1) * r.inv(i << 1)) * inv2; }
    return r.pre(deg);
  }
  FPS exp(ll deg = -1) const {
    const int n = this->size();
    assert((*this)[0] == mint(0));
    if(deg == -1) { deg = n; }
    if(FAST) {
      FPS inv;
      inv.reserve(deg);
      inv.emplace_back(mint(0));
      inv.emplace_back(mint(1));
      auto internal_integral = [&](FPS &f) {
        const int n = f.size();
        while((int)inv.size() <= n) {
          int i = inv.size();
          inv.emplace_back((-inv[MOD % i]) * (MOD / i));
        }
        f.insert(f.begin(), mint(0));
        for(int i = 1; i <= n; i++) { f[i] *= inv[i]; }
      };
      auto internal_diff = [](FPS &f) {
        if(f.empty()) { return; }
        f.erase(f.begin());
        mint c = 1;
        for(int i = 0; i < (int)f.size(); i++, c++) { f[i] *= c; }
      };
      FPS b{1, 1 < (int)this->size() ? (*this)[1] : 0}, c{1}, z1, z2{1, 1};
      for(int m = 2; m <= deg; m <<= 1) {
        auto y = b;
        y.resize(m * 2);
        internal::butterfly(y);
        z1 = z2;
        FPS z(m);
        for(int i = 0; i < m; i++) { z[i] = y[i] * z1[i]; }
        internal::butterfly_inv(z);
        mint si = mint(m).inv();
        for(int i = 0; i < m; i++) { z[i] *= si; }
        fill(z.begin(), z.begin() + m / 2, mint(0));
        internal::butterfly(z);
        for(int i = 0; i < m; i++) { z[i] *= -z1[i]; }
        internal::butterfly_inv(z);
        for(int i = 0; i < m; i++) { z[i] *= si; }
        c.insert(c.end(), z.begin() + m / 2, z.end());
        z2 = c;
        z2.resize(m * 2);
        internal::butterfly(z2);
        FPS x(this->begin(), this->begin() + min((int)this->size(), m));
        x.resize(m);
        internal_diff(x);
        x.emplace_back(mint(0));
        internal::butterfly(x);
        for(int i = 0; i < m; i++) { x[i] *= y[i]; }
        internal::butterfly_inv(x);
        for(int i = 0; i < m; i++) { x[i] *= si; }
        x -= b.diff();
        x.resize(m * 2);
        for(int i = 0; i < m - 1; i++) {
          x[m + i] = x[i];
          x[i] = mint(0);
        }
        internal::butterfly(x);
        for(int i = 0; i < m * 2; i++) { x[i] *= z2[i]; }
        internal::butterfly_inv(x);
        mint si2 = mint(m << 1).inv();
        for(int i = 0; i < m * 2; i++) { x[i] *= si2; }
        x.pop_back();
        internal_integral(x);
        for(int i = m; i < min((int)this->size(), m * 2); i++) { x[i] += (*this)[i]; }
        fill(x.begin(), x.begin() + m, mint(0));
        internal::butterfly(x);
        for(int i = 0; i < m * 2; i++) { x[i] *= y[i]; }
        internal::butterfly_inv(x);
        for(int i = 0; i < m * 2; i++) { x[i] *= si2; }
        b.insert(b.end(), x.begin() + m, x.end());
      }
      return b.pre(deg);
    }
    else {
      FPS r({mint(1)});
      for(int i = 1; i < deg; i <<= 1) { r = (r * (pre(i << 1) + mint(1) - r.log(i << 1))).pre(i << 1); }
      return r.pre(deg);
    }
  }
  FPS pow(ll k) {
    const int n = this->size();
    assert(k >= 0);
    if(k == 0) {
      FPS r(n, mint(0));
      r[0] = mint(1);
      return r;
    }
    for(int i = 0; i < n; i++) {
      if(i * k > n) { return FPS(n, mint(0)); }
      if((*this)[i] != mint(0)) {
        mint rev = (*this)[i].inv();
        FPS r = (((*this * rev) >> i).log() * k).exp() * ((*this)[i].pow(k));
        r = (r << (i * k)).pre(n);
        if((int)r.size() < n) { r.resize(n, mint(0)); }
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
};