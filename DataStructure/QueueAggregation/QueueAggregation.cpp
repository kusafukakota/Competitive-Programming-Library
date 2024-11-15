template<typename T, auto op, auto e> struct QueueAggregation {
 private:
  vector<T> a0, a1, r0, r1;
  T f0, f1;
  void push0(const T &x) {
    a0.push_back(x);
    r0.push_back(f0 = op(x, f0));
  }
  void push1(const T &x) {
    a1.push_back(x);
    r1.push_back(f1 = op(f1, x));
  }
  void transfer() {
    while(!a1.empty()) {
      push0(a1.back());
      a1.pop_back();
    }
    while(!r1.empty()) { r1.pop_back(); }
    f1 = e();
  }

 public:
  QueueAggregation(): f0(e()), f1(e()){};
  void push(const T &x) {
    if(a0.empty()) {
      push0(x);
      transfer();
    }
    else { push1(x); }
  }
  void pop() {
    if(a0.empty()) { transfer(); }
    a0.pop_back();
    r0.pop_back();
    f0 = (r0.empty() ? e() : r0.back());
  }
  T prod() { return op(f0, f1); }
};
