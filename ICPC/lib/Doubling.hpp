#pragma once

struct Doubling {
 private:
  int n = 0;
  vector<vector<ll>> nxts;
  void build() {
    vector<ll> nxt(n);
    for(int i = 0; i < n; i++) {
      if(int j = nxts.back()[i]; in(j)) { nxt[i] = nxts.back()[j]; }
      else { nxt[i] = j; }
    }
    nxts.emplace_back(move(nxt));
  }
  inline bool in(int i) const noexcept { return 0 <= i && i < n; }
  int pow_next(int s, int d) {
    assert(in(s));
    while(ssize(nxts) <= d) { build(); }
    return nxts[d][s];
  }

 public:
  Doubling() = default;
  Doubling(const vector<ll> &nxt): n(ssize(nxt)), nxts(1, nxt) { build(); }
  int next(int s, ll k) {
    for(int d = 0; k > 0 && in(s); d++, k >>= 1) {
      if(k & 1) { s = pow_next(s, d); }
    }
    return s;
  }
};