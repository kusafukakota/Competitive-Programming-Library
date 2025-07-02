#pragma once

template<typename T> vector<int> Manacher(const T &S) {
  const int N = S.size();
  vector<int> r(N);
  int i = 0, j = 0;
  while(i < N) {
    while(i - j >= 0 && i + j < N && S[i - j] == S[i + j]) { j++; }
    r[i] = j;
    int k = 1;
    while(i - k >= 0 && i + k < N && k + r[i - k] < j) {
      r[i + k] = r[i - k];
      k++;
    }
    i += k;
    j -= k;
  }
  return r;
}

template<typename T> vector<pair<int, int>> WidestPalindrome(const T &vec) {
  using U = typename T::value_type;
  vector<U> v;
  const int N = vec.size();
  for(int i = 0; i < N - 1; i++) {
    v.emplace_back(vec[i]);
    v.emplace_back(-1);
  }
  v.emplace_back(vec.back());
  const auto m = Manacher(v);
  vector<pair<int, int>> r;
  for(int i = 0; i < N * 2 - 1; i++) {
    if(i & 1) {
      int w = m[i] / 2;
      r.emplace_back((i + 1) / 2 - w, (i + 1) / 2 + w);
    }
    else {
      int w = (m[i] - 1) / 2;
      r.emplace_back(i / 2 - w, i / 2 + w + 1);
    }
  }
  return r;
}

template<typename T> vector<int> LeftmostPalindrome(const T &vec) {
  const int N = vec.size();
  vector<int> v(N, -1);
  for(auto &[l, r] : WidestPalindrome(vec)) { v[r - 1] = max(v[r - 1], r - l); }
  for(int i = N - 2; i >= 0; i--) { v[i] = max(v[i], v[i + 1] - 2); }
  vector<int> r(N);
  for(int i = 0; i < N; i++) { r[i] = i + 1 - v[i]; }
  return r;
}