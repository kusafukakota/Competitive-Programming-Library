template<typename T> void Walsh_Hadamard_Transform(vector<T> &v, bool inv) {
  ll n = ssize(v);
  for(int i = 1; i < n; i <<= 1) {
    for(int j = 0; j < n; j += i << 1) {
      for(int k = 0; k < i; k++) {
        T s = v[j + k], t = v[j + k + i];
        v[j + k] = s + t;
        v[j + k + i] = s - t;
      }
    }
  }
  if(inv) {
    T inv_n = T(1) / n;
    for(auto &x : v) { x *= inv_n; }
  }
}

template<typename T> vector<T> XOR_convolution(vector<T> a, vector<T> b) {
  const int n = a.size();
  assert(a.size() == b.size());
  assert((n & (n - 1)) == 0);
  Walsh_Hadamard_Transform(a, false);
  Walsh_Hadamard_Transform(b, false);
  for(int i = 0; i < n; i++) { a[i] *= b[i]; }
  Walsh_Hadamard_Transform(a, true);
  return a;
}
