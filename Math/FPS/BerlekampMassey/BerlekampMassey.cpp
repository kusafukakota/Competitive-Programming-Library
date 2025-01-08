template<typename T> vector<mint> BerlekampMassey(const vector<T> &v) {
  const int N = v.size();
  vector<mint> b, c;
  b.reserve(N + 1);
  c.reserve(N + 1);
  b.push_back(1);
  c.push_back(1);
  mint y = 1;
  for(int ed = 1; ed <= N; ed++) {
    int l = c.size(), m = b.size();
    mint x = 0;
    for(int i = 0; i < l; i++) { x += c[i] * v[ed - l + i]; }
    b.emplace_back(0);
    m++;
    if(x == 0) { continue; }
    mint freq = x / y;
    if(l < m) {
      auto tmp = c;
      c.insert(begin(c), m - l, 0);
      for(int i = 0; i < m; i++) { c[m - i - 1] -= freq * b[m - i - 1]; }
      b = tmp;
      y = x;
    }
    else {
      for(int i = 0; i < m; i++) { c[l - i - 1] -= freq * b[m - i - 1]; }
    }
  }
  c.pop_back();
  for(auto &i : c) { i = -i; }
  ranges::reverse(c);
  return c;
}

template<typename T> mint BMBM(const vector<T> &v, ll n) {
  auto bm = BerlekampMassey(v);
  return LinearRecurrence(v, bm, n);
}
