struct DynamicConvexHull {
 private:
  static constexpr ll inf = numeric_limits<int>::max();
  struct Point {
    ll x, y;
    Point() = default;
    Point(ll x, ll y): x(x), y(y) {}
    bool operator==(const Point &other) const { return x == other.x && y == other.y; }
    bool operator!=(const Point &other) const { return !(operator==(other)); }
    Point operator+(const Point &other) const { return {x + other.x, y + other.y}; }
    Point operator-(const Point &other) const { return {x - other.x, y - other.y}; }
    operator pair<int, int>() const { return {x, y}; }
    friend ll det(Point p, Point q) { return p.x * q.y - p.y * q.x; }
  };
  struct Node {
    pair<Point, Point> bridge;
    ll min_x;
    Node() = default;
    Node(Point p): bridge(p, p), min_x(p.x) {}
    Node(pair<Point, Point> bridge, ll min_x): bridge(bridge), min_x(min_x) {}
    bool operator==(const Node &other) const { return bridge == other.bridge && min_x == other.min_x; }
    bool operator!=(const Node &other) const { return !(operator==(other)); }
  };
  static inline const Node None{Point{-inf, -inf}};
  int M;
  vector<int> _xs;
  vector<set<int>> points_upper, points_lower;
  vector<Node> seg_upper, seg_lower;
  static int next_branch(int i, const vector<Node> &seg) {
    while(seg[2 * i] == None || seg[2 * i + 1] == None) { i = 2 * i + (seg[2 * i] == None); }
    return i;
  }
  static Node merge(int x, int y, vector<Node> &seg) {
    if(seg[x] == None) { return seg[y]; }
    if(seg[y] == None) { return seg[x]; }
    const ll min_x = seg[x].min_x, sep_x = seg[y].min_x;
    Point a, b, c, d;
    while(true) {
      tie(a, b) = seg[x].bridge;
      tie(c, d) = seg[y].bridge;
      if(a == b && c == d) { break; }
      if(a != b && det(b - a, c - a) > 0) { x = 2 * next_branch(x, seg); }
      else if(c != d && det(c - b, d - b) > 0) { y = 2 * next_branch(y, seg) + 1; }
      else if(a == b) { y = 2 * next_branch(y, seg); }
      else if(c == d) { x = 2 * next_branch(x, seg) + 1; }
      else {
        __int128_t c1 = det(b - a, c - a), c2 = det(a - b, d - b);
        if(c1 + c2 == 0 || c1 * d.x + c2 * c.x < sep_x * (c1 + c2)) { x = 2 * next_branch(x, seg) + 1; }
        else { y = 2 * next_branch(y, seg); }
      }
    }
    return Node({a, c}, min_x);
  }
  void inner_set(int i, const Node &dat, vector<Node> &seg) {
    seg[M + i] = dat;
    for(i = (M + i) >> 1; i > 0; i >>= 1) { seg[i] = merge(2 * i, 2 * i + 1, seg); }
  }
  void insert(int x, int y, vector<Node> &seg, vector<set<int>> &points) {
    int i = index(x);
    int old_y = seg[M + i].bridge.first.y;
    points[i].insert(y);
    if(old_y >= y) { return; }
    inner_set(i, Node{Point{x, y}}, seg);
  }
  void erase(int x, int y, vector<Node> &seg, vector<set<int>> &points) {
    int i = index(x);
    points[i].erase(y);
    int old_y = seg[M + i].bridge.first.y;
    if(old_y != y) { return; }
    inner_set(i, points[i].empty() ? None : Node{Point{x, *points[i].rbegin()}}, seg);
  }
  static int ceil_pow2(int n) {
    int res = 1;
    while(res < n) { res <<= 1; }
    return res;
  }
  int index(int x) const { return lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin(); }
  ll linearMax(int a, int b, const vector<Node> &seg) const {
    ll res = numeric_limits<ll>::min();
    for(int k = 1;;) {
      const auto &[p, q] = seg[k].bridge;
      res = max(res, p.x * a + p.y * b);
      res = max(res, q.x * a + q.y * b);
      if(p == q) { break; }
      k = 2 * next_branch(k, seg) | ((q.y - p.y) * b >= (q.x - p.x) * -a);
    }
    return res;
  }
  void get_upper_hull(int l, int r, int k, const vector<Node> &seg, vector<pair<int, int>> &res) const {
    if(l > r || seg[k] == None) { return; }
    if(k >= M) {
      res.push_back(seg[k].bridge.first);
      return;
    }
    if(seg[2 * k + 0] == None) { return get_upper_hull(l, r, 2 * k + 1, seg, res); }
    if(seg[2 * k + 1] == None) { return get_upper_hull(l, r, 2 * k + 0, seg, res); }
    int bl = seg[k].bridge.first.x, br = seg[k].bridge.second.x;
    if(r <= bl) { return get_upper_hull(l, r, 2 * k + 0, seg, res); }
    if(br <= l) { return get_upper_hull(l, r, 2 * k + 1, seg, res); }
    get_upper_hull(l, bl, 2 * k + 0, seg, res);
    get_upper_hull(br, r, 2 * k + 1, seg, res);
  }

 public:
  DynamicConvexHull() = default;
  template<typename T> DynamicConvexHull(const vector<T> &xs) {
    ranges::copy(xs, back_inserter(_xs));
    ranges::sort(_xs);
    _xs.erase(unique(_xs.begin(), _xs.end()), _xs.end());
    M = ceil_pow2(_xs.size());
    points_upper.resize(M);
    points_lower.resize(M);
    seg_upper = vector<Node>(2 * M, None);
    seg_lower = vector<Node>(2 * M, None);
  }
  void insert(int x, int y) {
    insert(x, +y, seg_upper, points_upper);
    insert(x, -y, seg_lower, points_lower);
  }
  void erase(int x, int y) {
    erase(x, +y, seg_upper, points_upper);
    erase(x, -y, seg_lower, points_lower);
  }
  // returns max { ax + by | (x, y) in S }
  ll linearMax(int a, int b) const { return b >= 0 ? linearMax(a, +b, seg_upper) : linearMax(a, -b, seg_lower); }
  // returns min { ax + by | (x, y) in S }
  ll linearMin(int a, int b) const { return -linearMax(-a, -b); }
  vector<pair<int, int>> get_upper_hull() const {
    vector<pair<int, int>> res;
    get_upper_hull(-inf, inf, 1, seg_upper, res);
    return res;
  }
  vector<pair<int, int>> get_lower_hull() const {
    vector<pair<int, int>> res;
    get_upper_hull(-inf, inf, 1, seg_lower, res);
    for(auto &[x, y] : res) { y = -y; }
    return res;
  }
  vector<pair<int, int>> get_hull() const {
    auto upper = get_upper_hull();
    auto lower = get_lower_hull();
    if(upper.empty()) { return upper; }
    int xl = upper.front().first, xr = upper.back().first;
    int yld = lower.front().second, ylu = upper.front().second;
    int yrd = lower.back().second, yru = upper.back().second;
    lower.erase(set_difference(lower.begin(), lower.end(), upper.begin(), upper.end(), lower.begin()), lower.end());
    for(int y : points_upper[index(xr)]) {
      if(yrd < y && y < yru) { lower.emplace_back(xr, y); }
    }
    ranges::reverse(lower);
    for(auto &p : lower) { upper.push_back(move(p)); }
    if(xl == xr) { return upper; }
    for(int y : points_upper[index(xl)]) {
      if(yld < y && y < ylu) { upper.emplace_back(xl, y); }
    }
    return upper;
  }
};
