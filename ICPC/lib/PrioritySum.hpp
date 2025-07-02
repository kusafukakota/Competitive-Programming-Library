#pragma once

template<typename T, typename Compare = less<T>, typename RCompare = greater<T>> struct PrioritySum {
 private:
  ll k;
  T sum;
  priority_queue<T, vector<T>, Compare> in, d_in;
  priority_queue<T, vector<T>, RCompare> out, d_out;
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

 public:
  // 昇順/降順 k 個の和
  PrioritySum(int k): k(k), sum(0) {}
  // x を追加 O(log N)
  void insert(T x) {
    in.emplace(x);
    sum += x;
    modify();
  }
  // x を削除 O(log N)
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
  // 昇順/降順 k 個の和 O(1)
  T query() const { return sum; }
  // k を nk に変更 O(|k - nk| log N)
  void set(ll nk) {
    k = nk;
    modify();
  }
  // k を返す O(1)
  ll get() const { return k; }
  // 要素数を返す O(1)
  ll size() const { return in.size() + out.size() - d_in.size() - d_out.size(); }
  T operator()() { return query(); }
};