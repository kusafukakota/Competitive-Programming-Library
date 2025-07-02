#pragma once

struct SternBrocotTree {
  using Node = SternBrocotTree;
  ll lx, ly, x, y, rx, ry;
  vector<ll> seq;
  SternBrocotTree(): lx(0), ly(1), x(1), y(1), rx(1), ry(0) {}
  SternBrocotTree(ll X, ll Y): SternBrocotTree() {
    assert(X >= 1 && Y >= 1);
    ll g = gcd(X, Y);
    X /= g, Y /= g;
    while(min(X, Y) > 0) {
      if(X > Y) {
        ll d = X / Y;
        X -= d * Y;
        go_right(d - (X == 0 ? 1 : 0));
      }
      else {
        ll d = Y / X;
        Y -= d * X;
        go_left(d - (Y == 0 ? 1 : 0));
      }
    }
  }
  SternBrocotTree(const pair<ll, ll> &xy): SternBrocotTree(xy.first, xy.second) {}
  SternBrocotTree(const vector<ll> &_seq): SternBrocotTree() {
    for(const ll &d : _seq) {
      assert(d != 0);
      if(d > 0) { go_right(d); }
      if(d < 0) { go_left(d); }
    }
    assert(seq == _seq);
  }

  pair<ll, ll> get() const { return make_pair(x, y); }
  pair<ll, ll> lower_bound() const { return make_pair(lx, ly); }
  pair<ll, ll> upper_bound() const { return make_pair(rx, ry); }
  ll depth() const {
    ll r = 0;
    for(auto &s : seq) { r += abs(s); }
    return r;
  }
  void go_left(ll d = 1) {
    if(d <= 0) { return; }
    if(seq.empty() || seq.back() > 0) { seq.emplace_back(0); }
    seq.back() -= d;
    rx += lx * d, ry += ly * d;
    x = rx + lx, y = ry + ly;
  }
  void go_right(ll d = 1) {
    if(d <= 0) { return; }
    if(seq.empty() || seq.back() < 0) { seq.emplace_back(0); }
    seq.back() += d;
    lx += rx * d, ly += ry * d;
    x = rx + lx, y = ry + ly;
  }
  bool go_parent(ll d = 1) {
    if(d <= 0) { return true; }
    while(d != 0) {
      if(seq.empty()) { return false; }
      ll d2 = min(d, abs(seq.back()));
      if(seq.back() > 0) {
        x -= rx * d2, y -= ry * d2;
        lx = x - rx, ly = y - ry;
        seq.back() -= d2;
      }
      else {
        x -= lx * d2, y -= ly * d2;
        rx = x - lx, ry = y - ly;
        seq.back() += d2;
      }
      d -= d2;
      if(seq.back() == 0) { seq.pop_back(); }
      if(d2 == 0) { break; }
    }
    return true;
  }
  static Node lca(const Node &lhs, const Node &rhs) {
    Node n;
    for(int i = 0; i < min<int>(lhs.seq.size(), rhs.seq.size()); i++) {
      ll val1 = lhs.seq[i], val2 = rhs.seq[i];
      if((val1 < 0) != (val2 < 0)) { break; }
      if(val1 < 0) { n.go_left(min(-val1, -val2)); }
      if(val1 > 0) { n.go_right(min(val1, val2)); }
      if(val1 != val2) { break; }
    }
    return n;
  }
  friend ostream &operator<<(ostream &os, const Node &rhs) {
    os << "\n";
    os << "L : (" << rhs.lx << ", " << rhs.ly << " )\n";
    os << "M : (" << rhs.x << ", " << rhs.y << " )\n";
    os << "R : (" << rhs.rx << ", " << rhs.ry << " )\n";
    os << "seq : {";
    for(auto &x : rhs.seq) { os << x << ", "; }
    os << "}\n";
    return os;
  }
  friend bool operator<(const Node &lhs, const Node &rhs) { return lhs.x * rhs.y < rhs.x * lhs.y; }
  friend bool operator==(const Node &lhs, const Node &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
};