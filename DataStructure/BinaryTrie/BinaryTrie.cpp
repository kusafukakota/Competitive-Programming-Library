template<int MAX_LOG = 32, typename T = int> struct BinaryTrie {
 private:
  struct node {
    int cnt;
    T lazy;
    node *ch[2];
    node(): cnt(0), lazy(0), ch{nullptr, nullptr} {}
  };
  void push(node *t, int b) {
    if((t->lazy >> (T)b) & (T)1) { swap(t->ch[0], t->ch[1]); }
    if(t->ch[0]) { t->ch[0]->lazy ^= t->lazy; }
    if(t->ch[1]) { t->ch[1]->lazy ^= t->lazy; }
    t->lazy = 0;
  }
  node *add(node *t, T val, int b = MAX_LOG - 1) {
    if(!t) { t = new node; }
    t->cnt += 1;
    if(b < 0) { return t; }
    push(t, b);
    bool f = (val >> (T)b) & (T)1;
    t->ch[f] = add(t->ch[f], val, b - 1);
    return t;
  }
  node *sub(node *t, T val, int b = MAX_LOG - 1) {
    assert(t);
    t->cnt -= 1;
    if(t->cnt == 0) { return nullptr; }
    if(b < 0) { return t; }
    push(t, b);
    bool f = (val >> (T)b) & (T)1;
    t->ch[f] = sub(t->ch[f], val, b - 1);
    return t;
  }
  T get_min(node *t, T val, int b = MAX_LOG - 1) {
    assert(t);
    if(b < 0) { return 0; }
    push(t, b);
    bool f = (val >> (T)b) & (T)1;
    f ^= !t->ch[f];
    return get_min(t->ch[f], val, b - 1) | ((T)f << (T)b);
  }
  T get(node *t, int k, int b = MAX_LOG - 1) {
    if(b < 0) { return 0; }
    push(t, b);
    int m = t->ch[0] ? t->ch[0]->cnt : 0;
    return k < m ? get(t->ch[0], k, b - 1) : get(t->ch[1], k - m, b - 1) | ((T)1 << (T)b);
  }
  int count_lower(node *t, T val, int b = MAX_LOG - 1) {
    if(!t || b < 0) { return 0; }
    push(t, b);
    bool f = (val >> (T)b) & (T)1;
    return (f && t->ch[0] ? t->ch[0]->cnt : 0) + count_lower(t->ch[f], val, b - 1);
  }
  node *root;

 public:
  BinaryTrie(): root(nullptr) {}
  int size() const { return root ? root->cnt : 0; }
  bool empty() const { return !root; }
  void insert(T val) { root = add(root, val); }
  void erase(T val) {
    if(!count(val)) { return; }
    root = sub(root, val);
  }
  void xor_all(T val) {
    if(root) { root->lazy ^= val; }
  }
  T max_element(T xor_val = 0) {
    xor_all(xor_val);
    T r = get_min(root, -1);
    xor_all(xor_val);
    return r;
  }
  T min_element(T xor_val = 0) {
    xor_all(xor_val);
    T r = get_min(root, 0);
    xor_all(xor_val);
    return r;
  }
  T kth_smallest(int k, T xor_val = 0) {
    assert(0 <= k && k < size());
    xor_all(xor_val);
    T r = get(root, k);
    xor_all(xor_val);
    return r;
  }
  int lower_bound(T val, T xor_val = 0) {
    xor_all(xor_val);
    int r = count_lower(root, val);
    xor_all(xor_val);
    return r;
  }
  int upper_bound(T val, T xor_val = 0) {
    xor_all(xor_val);
    int r = count_lower(root, val + 1);
    xor_all(xor_val);
    return r;
  }
  int count(T val) {
    if(!root) { return 0; }
    node *t = root;
    for(int i = MAX_LOG - 1; i >= 0; i--) {
      push(t, i);
      t = t->ch[(val >> (T)i) & (T)1];
      if(!t) { return 0; }
    }
    return t->cnt;
  }
};
