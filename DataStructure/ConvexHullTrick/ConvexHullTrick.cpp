template<typename T, bool isMin> struct ConvexHullTrick {
  deque<pair<T, T>> H;
  ConvexHullTrick() = default;
  bool empty() const { return H.empty(); }
  void clear() { H.clear(); }
  inline int sgn(T x) { return x == 0 ? 0 : (x < 0 ? -1 : 1); }
  inline bool check(const pair<T, T> &a, const pair<T, T> &b, const pair<T, T> &c) {
    if(b.second == a.second || c.second == b.second) {return sgn(b.first - a.first) * sgn(c.second - b.second) >= sgn(c.first - b.first) * sgn(b.second - a.second);}
    if(is_integral<T>::value) {return (b.second - a.second) / (a.first - b.first) >= (c.second - b.second) / (b.first - c.first);}
    else {return (b.first - a.first) * sgn(c.second - b.second) / abs(b.second - a.second) >= (c.first - b.first) * sgn(b.second - a.second) / abs(c.second - b.second);}
  }
  void add(T a, T b) {
    if(!isMin) {a *= -1, b *= -1;}
    pair<T, T> line(a, b);
    if(empty()) {
      H.emplace_front(line);
      return;
    }
    if(H.front().first <= a) {
      if(H.front().first == a) {
        if(H.front().second <= b) {return;}
        H.pop_front();
      }
      while(H.size() >= 2 && check(line, H.front(), H[1])) {H.pop_front();}
      H.emplace_front(line);
    }
    else {
      assert(a <= H.back().first);
      if(H.back().first == a) {
        if(H.back().second <= b) {return;}
        H.pop_back();
      }
      while(H.size() >= 2 && check(H[H.size() - 2], H.back(), line)) {H.pop_back();}
      H.emplace_back(line);
    }
  }
  inline T get_y(const pair<T, T> &a, const T &x) { return a.first * x + a.second; }
  T query(T x) {  
    assert(!empty());
    int l = -1, r = H.size() - 1;
    while(l + 1 < r) {
      int m = (l + r) >> 1;
      if(get_y(H[m], x) >= get_y(H[m + 1], x)) {l = m;}
      else {r = m;}
    }
    if(isMin) {return get_y(H[r], x);}
    return -get_y(H[r], x);
  }
  T query_inc(T x) {
    assert(!empty());
    while(H.size() >= 2 && get_y(H.front(), x) >= get_y(H[1], x)) {H.pop_front();}
    if(isMin) {return get_y(H.front(), x);}
    return -get_y(H.front(), x);
  }
  T query_dec(T x) {
    assert(!empty());
    while(H.size() >= 2 && get_y(H.back(), x) >= get_y(H[H.size() - 2], x)) {H.pop_back();}
    if(isMin) {return get_y(H.back(), x);}
    return -get_y(H.back(), x);
  }
};
template<typename T> using ConvexHullTrick_min = ConvexHullTrick<T, 1>;
template<typename T> using ConvexHullTrick_max = ConvexHullTrick<T, 0>;
