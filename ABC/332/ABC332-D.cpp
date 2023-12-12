#include <bits/stdc++.h>
using namespace std;
#include <atcoder/fenwicktree>
using namespace atcoder;
using ll = long long;

ll Inversion(vector<ll> &v) {
  ll r = 0, n = v.size();
  // Compress(v);
  fenwick_tree<ll> b(n + 1);
  for(ll i = 0; i < n; i++) {
    r += b.sum(v[i] + 1, n + 1);
    b.add(v[i], 1);
  }
  return r;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll H, W;
  cin >> H >> W;

  vector<vector<ll>> A(H, vector<ll>(W)), B(H, vector<ll>(W));
  for(auto &i : A) {
    for(auto &j : i) { cin >> j; }
  }
  for(auto &i : B) {
    for(auto &j : i) { cin >> j; }
  }

  vector<ll> h(H), w(W);
  iota(h.begin(), h.end(), 0);
  iota(w.begin(), w.end(), 0);

  ll r = 1e18;
  vector<vector<ll>> v(H, vector<ll>(W));
  do {
    do {
      for(ll i = 0; i < H; i++) {
        for(ll j = 0; j < W; j++) {
          v[i][j] = A[h[i]][w[j]];
        }
      }
      if(v == B) {
        ll t = Inversion(w) + Inversion(h);
        r = min(r, t);
      }
    } while(next_permutation(w.begin(), w.end()));
  } while(next_permutation(h.begin(), h.end()));

  cout << (r == 1e18 ? -1 : r) << "\n";
}
