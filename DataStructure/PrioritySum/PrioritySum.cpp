template<typename T, typename Compare = less<T>, typename RCompare = greater<T>> struct PrioritySum {
  ll k;
  T sum;
  priority_queue<T, vector<T>, Compare> in, d_in;
  priority_queue<T, vector<T>, RCompare> out, d_out;
  PrioritySum(int k): k(k), sum(0) {}
  void modify() {
    while(in.size() - d_in.size() < k && !out.empty()) {
      auto p = out.top();
      out.pop();
      if(!d_out.empty() && p == d_out.top()) { d_out.pop(); }
      else {
        sum += p;
        in.emplace(p);
      }
    }
    while(in.size() - d_in.size() > k) {
      auto p = in.top();
      in.pop();
      if(!d_in.empty() && p == d_in.top()) { d_in.pop(); }
      else {
        sum -= p;
        out.emplace(p);
      }
    }
    while(!d_in.empty() && in.top() == d_in.top()) {
      in.pop();
      d_in.pop();
    }
  }
  T query() const { return sum; }
  void insert(T x) {
    in.emplace(x);
    sum += x;
    modify();
  }
  void erase(T x) {
    assert(size());
    if(!in.empty() && in.top() == x) {
      sum -= x;
      in.pop();
    }
    else if(!in.empty() && RCompare()(in.top(), x)) {
      sum -= x;
      d_in.emplace(x);
    }
    else { d_out.emplace(x); }
    modify();
  }
  void set(ll kk) {
    k = kk;
    modify();
  }
  ll get() const { return k; }
  ll size() const { return in.size() + out.size() - d_in.size() - d_out.size(); }
  T operator()() { return query(); }
  void operator>>(T x) { insert(x); }
  void operator<<(T x) { erase(x); }
};

template<typename T> using MaxSum = PrioritySum<T, greater<T>, less<T>>;
template<typename T> using MinSum = PrioritySum<T, less<T>, greater<T>>;