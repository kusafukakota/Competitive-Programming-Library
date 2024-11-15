template<typename T> struct DualPriorityQueue {
 private:
  inline int par(int i) { return (i - 4 + (i & 3)) / 2; }
  void down(int i) {
    int n = dat.size();
    if(i % 2 == 0) {
      while(true) {
        if(i + 1 < n && dat[i] > dat[i + 1]) { swap(dat[i], dat[i + 1]); }
        int j = i, l = 2 * i + 2, r = 2 * i + 4;
        if(l < n && dat[l] < dat[j]) { j = l; }
        if(r < n && dat[r] < dat[j]) { j = r; }
        if(i == j) { break; }
        swap(dat[i], dat[j]);
        i = j;
      }
    }
    else {
      while(true) {
        if(dat[i - 1] > dat[i]) { swap(dat[i - 1], dat[i]); }
        int j = i, l = 2 * i + 1, r = 2 * i + 3;
        if(r >= n) { --r; }
        if(l >= n) { --l; }
        if(l < n && dat[l] > dat[j]) { j = l; }
        if(r < n && dat[r] > dat[j]) { j = r; }
        if(i == j) { break; }
        swap(dat[i], dat[j]);
        i = j;
        if(i % 2 == 0) { break; }
      }
    }
  }
  void up() {
    int i = dat.size() - 1;
    if(2 <= i && i % 2 == 0) {
      int p = par(i) ^ 1;
      if(dat[p] < dat[i]) { swap(dat[i], dat[p]), i = p; }
    }
    if(i % 2 == 1 && dat[i - 1] > dat[i]) { swap(dat[i - 1], dat[i]), --i; }
    if(i % 2 == 0) {
      while(i >= 2) {
        int p = par(i);
        if(dat[p] <= dat[i]) { break; }
        swap(dat[p], dat[i]);
        i = p;
      }
      return;
    }
    while(i >= 3) {
      int p = par(i);
      if(dat[p] >= dat[i]) { break; }
      swap(dat[p], dat[i]);
      i = p;
    }
  }

 public:
  vector<T> dat;
  DualPriorityQueue() {}
  DualPriorityQueue(vector<T> &A) {
    dat = A;
    int n = dat.size();
    for(int i = n - 1; i >= 0; i--) { down(i); }
  }
  int size() { return dat.size(); }
  bool empty() { return dat.empty(); }
  T min() { return dat[0]; }
  T max() { return dat.size() == 1 ? dat[0] : dat[1]; }
  void push(T x) {
    dat.emplace_back(x);
    up();
  }
  T pop_min() {
    assert(!dat.empty());
    swap(dat[0], dat.back());
    T res = dat.back();
    dat.pop_back();
    down(0);
    return res;
  }
  T pop_max() {
    assert(!dat.empty());
    if(dat.size() <= 2) {
      T res = dat.back();
      dat.pop_back();
      return res;
    }
    swap(dat[1], dat.back());
    T res = dat.back();
    dat.pop_back();
    down(1);
    return res;
  }
};
