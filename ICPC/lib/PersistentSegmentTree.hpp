#pragma once

template<typename T, auto op, auto e> struct PersistentSegmentTree {
  struct Node {
    T d;
    Node *l, *r;
  };
  using NP = Node *;

 private:
  int N{};
  NP merge(NP l, NP r) { return new Node{op(l->d, r->d), l, r}; }
  NP build(int l, int r, const vector<T> &v) const {
    if(l + 1 == r) { return new Node{v[l], nullptr, nullptr}; }
    return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
  }
  NP set(int a, const T &x, NP k, int l, int r) const {
    if(r <= a || a + 1 <= l) { return k; }
    else if(a <= l && r <= a + 1) { return new Node{x, nullptr, nullptr}; }
    else { return merge(set(a, x, k->l, l, (l + r) >> 1), set(a, x, k->r, (l + r) >> 1, r)); }
  }
  NP apply(int a, const T &x, NP k, int l, int r) const {
    if(r <= a || a + 1 <= l) { return k; }
    else if(a <= l && r <= a + 1) { return new Node{op(k->d, x), nullptr, nullptr}; }
    else { return merge(apply(a, x, k->l, l, (l + r) >> 1), apply(a, x, k->r, (l + r) >> 1, r)); }
  }
  T prod(int a, int b, NP k, int l, int r) const {
    if(r <= a || b <= l) { return e(); }
    else if(a <= l && r <= b) { return k->d; }
    else { return op(prod(a, b, k->l, l, (l + r) >> 1), prod(a, b, k->r, (l + r) >> 1, r)); }
  }

 public:
  PersistentSegmentTree() = default;
  PersistentSegmentTree(int N): N(N) {}
  NP build(const vector<T> &v) const {
    assert(N == (int)v.size());
    return build(0, N, v);
  }
  NP set(NP t, int k, const T &x) const { return set(k, x, t, 0, N); }
  T get(NP t, int k) const {
    for(int l = 0, r = N; l + 1 < r;) {
      int p = (l + r) >> 1;
      if(k < p) {
        t = t->l;
        r = p;
      }
      else {
        t = t->r;
        l = p;
      }
    }
    return t->d;
  }
  NP apply(NP t, int k, const T &x) { return apply(k, x, t, 0, N); }
  T prod(NP t, int a, int b) const { return prod(a, b, t, 0, N); }
  T all_prod(NP t) const { return t->d; }
};
