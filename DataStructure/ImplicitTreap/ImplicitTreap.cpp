template<typename T0, typename T1> struct ImplicitTreap {
 private:
  virtual T0 f0(T0, T0) = 0;
  const T0 u0;
  virtual T1 f1(T1, T1) = 0;
  const T1 u1;
  virtual T0 g(T0, T1) = 0;
  virtual T1 p(T1, int) = 0;
  struct xorshift {
    uint64_t x;
    xorshift() {
      mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
      x = rnd();
      for(int i = 0; i < 100; i++) { random(); }
    }
    uint64_t random() {
      x = x ^ (x << 7);
      return x = x ^ (x >> 9);
    }
  } rnd;
  struct Node {
    T0 value, acc;
    T1 lazy;
    int priority, cnt;
    bool rev;
    Node *l, *r;
    Node(T0 value_, int priority_, T0 u0_, T1 u1_): value(value_), acc(u0_), lazy(u1_), priority(priority_), cnt(1), rev(false), l(nullptr), r(nullptr) {}
  } *root = nullptr;
  using Tree = Node *;
  int cnt(Tree t) { return t ? t->cnt : 0; }
  T0 acc(Tree t) { return t ? t->acc : u0; }
  void update_cnt(Tree t) {
    if(t) { t->cnt = 1 + cnt(t->l) + cnt(t->r); }
  }
  void update_acc(Tree t) {
    if(t) { t->acc = f0(acc(t->l), f0(t->value, acc(t->r))); }
  }
  void pushup(Tree t) { update_cnt(t), update_acc(t); }
  void pushdown(Tree t) {
    if(t && t->rev) {
      t->rev = false;
      swap(t->l, t->r);
      if(t->l) { t->l->rev ^= 1; }
      if(t->r) { t->r->rev ^= 1; }
    }
    if(t && t->lazy != u1) {
      if(t->l) {
        t->l->lazy = f1(t->l->lazy, t->lazy);
        t->l->acc = g(t->l->acc, p(t->lazy, cnt(t->l)));
      }
      if(t->r) {
        t->r->lazy = f1(t->r->lazy, t->lazy);
        t->r->acc = g(t->r->acc, p(t->lazy, cnt(t->r)));
      }
      t->value = g(t->value, p(t->lazy, 1));
      t->lazy = u1;
    }
    pushup(t);
  }
  void split(Tree t, int key, Tree &l, Tree &r) {
    if(!t) {
      l = r = nullptr;
      return;
    }
    pushdown(t);
    int implicit_key = cnt(t->l) + 1;
    if(key < implicit_key) { split(t->l, key, l, t->l), r = t; }
    else { split(t->r, key - implicit_key, t->r, r), l = t; }
    pushup(t);
  }
  void insert(Tree &t, int key, Tree item) {
    Tree t1, t2;
    split(t, key, t1, t2);
    merge(t1, t1, item);
    merge(t, t1, t2);
  }
  void merge(Tree &t, Tree l, Tree r) {
    pushdown(l);
    pushdown(r);
    if(!l || !r) { t = l ? l : r; }
    else if(l->priority > r->priority) { merge(l->r, l->r, r), t = l; }
    else { merge(r->l, l, r->l), t = r; }
    pushup(t);
  }
  void erase(Tree &t, int key) {
    Tree t1, t2, t3;
    split(t, key + 1, t1, t2);
    split(t1, key, t1, t3);
    merge(t, t1, t2);
  }
  void update(Tree t, int l, int r, T1 x) {
    if(l >= r) return;
    Tree t1, t2, t3;
    split(t, l, t1, t2);
    split(t2, r - l, t2, t3);
    t2->lazy = f1(t2->lazy, x);
    t2->acc = g(t2->acc, p(x, cnt(t2)));
    merge(t2, t2, t3);
    merge(t, t1, t2);
  }
  T0 query(Tree t, int l, int r) {
    if(l == r) return u0;
    Tree t1, t2, t3;
    split(t, l, t1, t2);
    split(t2, r - l, t2, t3);
    T0 ret = t2->acc;
    merge(t2, t2, t3);
    merge(t, t1, t2);
    return ret;
  }
  int find(Tree t, T0 x, int offset, bool left = true) {
    if(f0(t->acc, x) == x) { return -1; }
    else {
      if(left) {
        if(t->l && f0(t->l->acc, x) != x) { return find(t->l, x, offset, left); }
        else { return (f0(t->value, x) != x) ? offset + cnt(t->l) : find(t->r, x, offset + cnt(t->l) + 1, left); }
      }
      else {
        if(t->r && f0(t->r->acc, x) != x) { return find(t->r, x, offset + cnt(t->l) + 1, left); }
        else { return (f0(t->value, x) != x) ? offset + cnt(t->l) : find(t->l, x, offset, left); }
      }
    }
  }
  void reverse(Tree t, int l, int r) {
    if(l > r) { return; }
    Tree t1, t2, t3;
    split(t, l, t1, t2);
    split(t2, r - l, t2, t3);
    t2->rev ^= 1;
    merge(t2, t2, t3);
    merge(t, t1, t2);
  }
  void rotate(Tree t, int l, int m, int r) {
    reverse(t, l, r);
    reverse(t, l, l + r - m);
    reverse(t, l + r - m, r);
  }
  void dump(Tree t) {
    if(!t) return;
    pushdown(t);
    dump(t->l);
    cout << t->value << " ";
    dump(t->r);
  }

 public:
  ImplicitTreap(T0 u0_, T1 u1_): u0(u0_), u1(u1_) {}
  void set_by_vector(const vector<T0> &a) {
    for(int i = 0; i < a.size(); i++) {
      insert(i, a[i]);
    }
  }
  int size() { return cnt(root); }
  void insert(int pos, T0 x) { insert(root, pos, new Node(x, rnd.random(), u0, u1)); }
  void update(int l, int r, T1 x) { update(root, l, r, x); }
  T0 query(int l, int r) { return query(root, l, r); }
  int binary_search(int l, int r, T0 x, bool left = true) {
    if(l >= r) return -1;
    Tree t1, t2, t3;
    split(root, l, t1, t2);
    split(t2, r - l, t2, t3);
    int ret = find(t2, x, l, left);
    merge(t2, t2, t3);
    merge(root, t1, t2);
    return ret;
  }
  void erase(int pos) { erase(root, pos); }
  void reverse(int l, int r) { reverse(root, l, r); }
  void rotate(int l, int m, int r) { rotate(root, l, m, r); }
  void dump() {
    dump(root);
    cout << endl;
  }
  T0 operator[](int pos) { return query(pos, pos + 1); }
};
