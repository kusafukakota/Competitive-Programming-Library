struct SubsetTransform {
  template<typename T> static void zeta_transform(vector<T> &v) {
    ll n = ssize(v);
    for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
        for(int k = 0; k < i; k++) { v[j + k + i] += v[j + k]; }
      }
    }
  }
  template<typename T> static void mobius_transform(vector<T> &v) {
    ll n = ssize(v);
    for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
        for(int k = 0; k < i; k++) { v[j + k + i] -= v[j + k]; }
      }
    }
  }
};

template<typename T> vector<T> OR_convolution(vector<T> a, vector<T> b) {
  const int n = a.size();
  assert(a.size() == b.size());
  assert((n & (n - 1)) == 0);
  SubsetTransform::zeta_transform(a);
  SubsetTransform::zeta_transform(b);
  for(int i = 0; i < n; i++) { a[i] *= b[i]; }
  SubsetTransform::mobius_transform(a);
  return a;
}
