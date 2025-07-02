#pragma once

#include <atcoder/convolution>
using namespace atcoder;

struct MultiDimensionalConvolution {
 private:
  ll N, K, M;
  vector<int> chi;
  static constexpr int ceil_pow2(int m) {
    int r = 1;
    while(r < m) { r <<= 1; }
    return r << 1;
  }
  auto ranked(const vector<mint> &f) const {
    vector rf(K, vector<mint>(M, mint{}));
    for(int i = 0; i < N; i++) { rf[chi[i]][i] = f[i]; }
    return rf;
  }

 public:
  MultiDimensionalConvolution(): MultiDimensionalConvolution(vector<ll>{}) {}
  MultiDimensionalConvolution(const vector<ll> &dim): N(accumulate(dim.begin(), dim.end(), 1, multiplies<int>())), K(dim.size()), M(ceil_pow2(N)), chi(N, 0) {
    for(int i = 0; i < N; i++) {
      int den = 1;
      for(auto e : dim) {
        den *= e;
        chi[i] += i / den;
      }
      if(K) { chi[i] %= K; }
    }
  }
  int size() const { return N; }
  int dum_sum() const { return K; }
  vector<mint> convolution(vector<mint> f, vector<mint> g) const {
    assert((int)f.size() == N && (int)g.size() == N);
    if(!K) { return {f[0] * g[0]}; }
    auto rf = ranked(f), rg = ranked(g);
    for(auto &v : rf) { internal::butterfly(v); }
    for(auto &v : rg) { internal::butterfly(v); }
    vector rh(K, vector<mint>(M, mint{}));
    for(int i = 0; i < K; i++)
      for(int j = 0; j < K; j++) {
        int r = i + j < K ? i + j : i + j - K;
        for(int p = 0; p < M; ++p) { rh[r][p] += rf[i][p] * rg[j][p]; }
      }
    for(auto &v : rh) { internal::butterfly_inv(v); }
    const mint isz = mint(M).inv();
    vector<mint> h(N);
    for(int i = 0; i < N; i++) { h[i] = rh[chi[i]][i] * isz; }
    return h;
  }
};