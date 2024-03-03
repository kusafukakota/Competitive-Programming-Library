template<typename T> void WalshHadamardTransform(vector<T> &v, bool inv) {
  const int n = v.size();
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
