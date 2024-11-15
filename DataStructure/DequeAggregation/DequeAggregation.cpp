template<typename T, auto op, auto e> struct DequeAggregation {
 private:
  vector<T> a0, a1, r0, r1;
  T get0() const { return r0.empty() ? e() : r0.back(); }
  T get1() const { return r1.empty() ? e() : r1.back(); }
  void push0(const T &x) {
    a0.push_back(x);
    r0.push_back(op(x, get0()));
  }
  void push1(const T &x) {
    a1.push_back(x);
    r1.push_back(op(get1(), x));
  }
  void modify() {
    int n = a0.size() + a1.size();
    int s0 = n / 2 + (a0.empty() ? n % 2 : 0);
    vector<T> a{a0};
    ranges::reverse(a);
    ranges::copy(a1, back_inserter(a));
    a0.clear(), r0.clear();
    a1.clear(), r1.clear();
    for(int i = s0 - 1; i >= 0; i--) { push0(a[i]); }
    for(int i = s0; i < n; i++) { push1(a[i]); }
  }

 public:
  DequeAggregation() = default;
  void push_front(const T &x) { push0(x); }
  void push_back(const T &x) { push1(x); }
  T front() const { return a0.empty() ? a1.front() : a0.back(); }
  T pop() const { return a1.empty() ? a0.front() : a1.back(); }
  void pop_front() {
    if(a0.empty()) { modify(); }
    a0.pop_back(), r0.pop_back();
  }
  void pop_back() {
    if(a1.empty()) { modify(); }
    a1.pop_back(), r1.pop_back();
  }
  T prod() { return op(get0(), get1()); }
};
