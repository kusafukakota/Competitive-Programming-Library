#include <atcoder/internal_math>
template<typename T> vector<mint> MultiplicativeConvolution(const vector<T> &a, const vector<T> &b, int P) {
  int r = internal::primitive_root_constexpr(P);
  vector<ll> p(P), ip(P);
  p[0] = 1;
  for(int i = 0; i < P - 1; i++) {
    p[i + 1] = p[i] * r % P;
    ip[p[i]] = i;
  }
  vector<mint> s(P - 1), t(P - 1);
  for(int i = 0; i < P - 1; i++) {
    s[i] = a[p[i]];
    t[i] = b[p[i]];
  }
  auto u = convolution(s, t);
  for(int i = P - 1; i < (int)u.size(); i++) { u[i % (P - 1)] += u[i]; }
  vector<mint> ret(P);
  mint sa = accumulate(a.begin(), a.end(), mint{}), sb = accumulate(b.begin(), b.end(), mint{});
  ret[0] = sa * b[0] + sb * a[0] - a[0] * b[0];
  for(int i = 1; i < P; i++) { ret[i] = u[ip[i]]; }
  return ret;
}
