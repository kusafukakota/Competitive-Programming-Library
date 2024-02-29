int ShortestRepetition(const string &s) {
  vector<int> z = z_algorithm(s);
  int sz = s.size();
  for(int i = 1; i < sz; i++) {
    if(z[i] == sz - i && sz % i == 0) { return i; }
  }
  return sz;
}

template<typename T> int ShortestRepetition(const vector<T> &v) {
  vector<int> z = z_algorithm(v);
  int sz = v.size();
  for(int i = 1; i < sz; i++) {
    if(z[i] == sz - i && sz % i == 0) { return i; }
  }
  return sz;
}
