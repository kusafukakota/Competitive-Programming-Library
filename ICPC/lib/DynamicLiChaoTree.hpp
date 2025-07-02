#pragma once

// https://ei1333.github.io/library/structure/convex-hull-trick/dynamic-li-chao-tree.hpp
// x_low, x_high : query で与える x の最小/最大値, id : 単位元（十分大きい値）
template<typename T, T x_low, T x_high, T id> struct DynamicLiChaoTree {
 private:
  struct Line {
    T a, b;
    Line(T a, T b): a(a), b(b) {}
    inline T get(T x) const { return a * x + b; }
  };
  struct Node {
    Line x;
    Node *l, *r;
    Node(const Line &x): x{x}, l{nullptr}, r{nullptr} {}
  };
  Node *root;
  Node *add_line(Node *t, Line &x, const T &l, const T &r, const T &x_l, const T &x_r) {
    if(!t) return new Node(x);
    T t_l = t->x.get(l), t_r = t->x.get(r);
    if(t_l <= x_l && t_r <= x_r) { return t; }
    else if(t_l >= x_l && t_r >= x_r) {
      t->x = x;
      return t;
    }
    else {
      T m = (l + r) / 2;
      if(m == r) { --m; }
      T t_m = t->x.get(m), x_m = x.get(m);
      if(t_m > x_m) {
        swap(t->x, x);
        if(x_l >= t_l) { t->l = add_line(t->l, x, l, m, t_l, t_m); }
        else { t->r = add_line(t->r, x, m + 1, r, t_m + x.a, t_r); }
      }
      else {
        if(t_l >= x_l) { t->l = add_line(t->l, x, l, m, x_l, x_m); }
        else { t->r = add_line(t->r, x, m + 1, r, x_m + x.a, x_r); }
      }
      return t;
    }
  }
  Node *add_segment(Node *t, Line &x, const T &a, const T &b, const T &l, const T &r, const T &x_l, const T &x_r) {
    if(r < a || b < l) { return t; }
    if(a <= l && r <= b) {
      Line y{x};
      return add_line(t, y, l, r, x_l, x_r);
    }
    if(t) {
      T t_l = t->x.get(l), t_r = t->x.get(r);
      if(t_l <= x_l && t_r <= x_r) { return t; }
    }
    else { t = new Node(Line(0, id)); }
    T m = (l + r) / 2;
    if(m == r) { --m; }
    T x_m = x.get(m);
    t->l = add_segment(t->l, x, a, b, l, m, x_l, x_m);
    t->r = add_segment(t->r, x, a, b, m + 1, r, x_m + x.a, x_r);
    return t;
  }
  T query(const Node *t, const T &l, const T &r, const T &x) const {
    if(!t) { return id; }
    if(l == r) { return t->x.get(x); }
    T m = (l + r) / 2;
    if(m == r) { --m; }
    if(x <= m) { return min(t->x.get(x), query(t->l, l, m, x)); }
    else { return min(t->x.get(x), query(t->r, m + 1, r, x)); }
  }

 public:
  DynamicLiChaoTree(): root{nullptr} {}
  // 直線 y = ax + b を追加 O(log N)
  // 最大値クエリの場合は add_line(-a,-b) とする
  void add_line(const T &a, const T &b) {
    Line x(a, b);
    root = add_line(root, x, x_low, x_high, x.get(x_low), x.get(x_high));
  }
  // 線分 y = ax + b (l <= x <= r) を追加 O(log^2 N)
  // 最大値クエリの場合は add_segment(l,r,-a,-b) とする
  void add_segment(const T &l, const T &r, const T &a, const T &b) {
    Line x(a, b);
    root = add_segment(root, x, l, r - 1, x_low, x_high, x.get(x_low), x.get(x_high));
  }
  // ax + b の最小値を返す O(log N)
  // 最大値クエリの場合は -query(x) とする
  T query(const T &x) const { return query(root, x_low, x_high, x); }
};
