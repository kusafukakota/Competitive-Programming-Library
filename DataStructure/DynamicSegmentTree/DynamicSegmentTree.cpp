template<typename S, auto op, auto e, int n> struct DynamicSegTree {
 private:
  struct Node;
  using Node_ptr = unique_ptr<Node>;
  struct Node {
    int idx;
    S val, prod;
    Node_ptr l, r;
    Node(int idx, S val): idx(idx), val(val), prod(val), l(nullptr), r(nullptr) {}
    void update() { prod = op(op(l ? l->prod : e(), val), r ? r->prod : e()); }
  };
  Node_ptr root;
  void set(Node_ptr &t, int a, int b, int p, S x) const {
    if(!t) {
      t = make_unique<Node>(p, x);
      return;
    }
    if(t->idx == p) {
      t->val = x;
      t->update();
      return;
    }
    int c = (a + b) >> 1;
    if(p < c) {
      if(t->idx < p) {
        swap(t->idx, p);
        swap(t->val, x);
      }
      set(t->l, a, c, p, x);
    }
    else {
      if(t->idx > p) {
        swap(t->idx, p);
        swap(t->val, x);
      }
      set(t->r, c, b, p, x);
    }
    t->update();
  }
  S get(const Node_ptr &t, int a, int b, int p) const {
    if(!t) { return e(); }
    if(t->idx == p) { return t->val; }
    int c = (a + b) >> 1;
    if(p < c) { return get(t->l, a, c, p); }
    else { return get(t->r, c, b, p); }
  }
  S prod(const Node_ptr &t, int a, int b, int l, int r) const {
    if(!t || b <= l || r <= a) { return e(); }
    if(l <= a && b <= r) { return t->prod; }
    int c = (a + b) >> 1;
    S res = prod(t->l, a, c, l, r);
    if(l <= t->idx && t->idx < r) { res = op(res, t->val); }
    return op(res, prod(t->r, c, b, l, r));
  }
  void reset(Node_ptr &t, int a, int b, int l, int r) const {
    if(!t || b <= l || r <= a) { return; }
    if(l <= a && b <= r) {
      t->reset();
      return;
    }
    int c = (a + b) >> 1;
    reset(t->l, a, c, l, r);
    reset(t->r, c, b, l, r);
    t->update();
  }
  template<typename F> int max_right(const Node_ptr &t, int a, int b, int l, const F &f, S &p) const {
    if(!t || b <= l) { return n; }
    if(f(op(p, t->prod))) {
      p = op(p, t->prod);
      return n;
    }
    int c = (a + b) >> 1;
    int res = max_right(t->l, a, c, l, f, p);
    if(res != n) { return res; }
    if(l <= t->idx) {
      p = op(p, t->val);
      if(!f(p)) { return t->idx; }
    }
    return max_right(t->r, c, b, l, f, p);
  }
  template<typename F> int min_left(const Node_ptr &t, int a, int b, int r, const F &f, S &p) const {
    if(!t || r <= a) { return 0; }
    if(f(op(p, t->prod))) {
      p = op(p, t->prod);
      return 0;
    }
    int c = (a + b) >> 1;
    int res = min_left(t->r, c, b, r, f, p);
    if(res) { return res; }
    if(t->idx < r) {
      p = op(p, t->val);
      if(!f(p)) { return t->idx + 1; }
    }
    return min_left(t->l, a, c, r, f, p);
  }

 public:
  DynamicSegTree(): root(nullptr) {}
  void set(int i, S x) { set(root, 0, n, i, x); }
  S get(int i) const { return get(root, 0, n, i); }
  S prod(int l, int r) const { return prod(root, 0, n, l, r); }
  S all_prod() const { return root ? root->prod : e(); }
  void reset(int l, int r) { reset(root, 0, n, l, r); }
  template<auto f> int max_right(int l) const {
    return max_right(l, [](S x) { return f(x); });
  }
  template<typename F> int max_right(int l, const F &f) const {
    S p = e();
    return max_right(root, 0, n, l, f, p);
  }
  template<auto f> int min_left(int r) const {
    return min_left(r, [](S x) { return f(x); });
  }
  template<typename F> int min_left(int r, const F &f) const {
    S p = e();
    return min_left(root, 0, n, r, f, p);
  }
};
