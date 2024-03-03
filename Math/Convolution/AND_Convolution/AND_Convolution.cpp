struct SupersetTransform {
  template<typename T> static void ZetaTransform(vector<T> &v) {
    const int n = v.size();
    for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
        for(int k = 0; k < i; k++) { v[j + k] += v[j + k + i]; }
      }
    }
  }
  template<typename T> static void MobiusTransform(vector<T> &v) {
    const int n = v.size();
    for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
        for(int k = 0; k < i; k++) { v[j + k] -= v[j + k + i]; }
      }
    }
  }
};

template<typename T> vector<T> AND_convolution(vector<T> a, vector<T> b) {
  const int n = a.size();
  assert(a.size() == b.size());
  assert(!(n & (n - 1)));
  SupersetTransform::ZetaTransform(a);
  SupersetTransform::ZetaTransform(b);
  for(int i = 0; i < n; i++) { a[i] *= b[i]; }
  SupersetTransform::MobiusTransform(a);
  return a;
}
