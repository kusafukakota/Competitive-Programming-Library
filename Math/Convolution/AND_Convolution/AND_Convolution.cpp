struct SupersetTransform {
  template<typename T> static void zeta_transform(vector<T> &v) {
    ll n = ssize(v);
    for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j++) {
        if((j & i) == 0) { v[j] += v[j | i]; }
      }
    }
  }
  template<typename T> static void mobius_transform(vector<T> &v) {
    ll n = ssize(v);
    for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j++) {
        if((j & i) == 0) { v[j] -= v[j | i]; }
      }
    }
  }
};

template<typename T> vector<T> AND_convolution(vector<T> a, vector<T> b) {
  const int n = a.size();
  assert(a.size() == b.size());
  assert((n & (n - 1)) == 0);
  SupersetTransform::zeta_transform(a);
  SupersetTransform::zeta_transform(b);
  for(int i = 0; i < n; i++) { a[i] *= b[i]; }
  SupersetTransform::mobius_transform(a);
  return a;
}
