#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T> struct Sum2D {
  int H, W;
  vector<vector<T>> v;
  Sum2D(int h, int w): H(h), W(w), v(H + 3, vector<T>(W + 3, 0)) {}
  Sum2D(vector<vector<T>> &ini): H(ini.size()), W(ini[0].size()), v(H + 3, vector<T>(W + 3, 0)) {
    for(int i = 0; i < H; i++) {
      for(int j = 0; j < W; j++) { v[i + 1][j + 1] += ini[i][j]; }
    }
    build();
  }
  void add(int h, int w, T z = 1) {
    assert(0 <= h && h < H && 0 <= w && w < W);
    v[h + 1][w + 1] += z;
  }
  void imos_add(int h1, int w1, int h2, int w2, T z = 1) { add(h1, w1, z), add(h1, w2, -z), add(h2, w1, -z), add(h2, w2, z); }
  void build() {
    for(int i = 1; i < (int)v.size(); i++) {
      for(int j = 1; j < (int)v[i].size(); j++) { v[i][j] += v[i][j - 1] + v[i - 1][j] - v[i - 1][j - 1]; }
    }
  }
  T sum(int h1, int w1, int h2, int w2) const { return v[h2][w2] - v[h1][w2] - v[h2][w1] + v[h1][w1]; }
  T operator()(int h, int w) const { return v[h][w]; }
  T operator()(int h1, int w1, int h2, int w2) const { return v[h2][w2] - v[h1][w2] - v[h2][w1] + v[h1][w1]; }
  T imos_get(int h, int w) { return v[h + 1][w + 1]; }
  vector<vector<T>> imos() const { return v; }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, q;
  cin >> n >> q;

  vector<vector<ll>> v(n, vector<ll>(n, 0));
  for(ll i = 0; i < n; i++) {
    for(ll j = 0; j < n; j++) {
      char c;
      cin >> c;
      if(c == 'B') { v[i][j] = 1; }
    }
  }

  Sum2D<ll> S(v);

  while(q--) {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    c++, d++;
    ll x = c / n - a / n - 1, y = d / n - b / n - 1;
    a %= n, b %= n, c %= n, d %= n;
    ll ans = 0;
    if(x == -1 && y == -1) {
      cout << S(a, b, c, d) << "\n";
      continue;
    }
    else if(x == -1) {
      ans += S(a, b, c, n);
      ans += S(a, 0, c, d);
      ans += S(a, 0, c, n) * y;
      cout << ans << "\n";
      continue;
    }
    else if(y == -1) {
      ans += S(a, b, n, d);
      ans += S(0, b, c, d);
      ans += S(0, b, n, d) * x;
      cout << ans << "\n";
      continue;
    }
    ans += S(a, b, n, n);
    if(x >= 0) { ans += S(0, b, c, n); }
    if(y >= 0) { ans += S(a, 0, n, d); }
    if(x >= 0 && y >= 0) { ans += S(0, 0, c, d); }
    if(x < 0) { x = 0; }
    if(y < 0) { y = 0; }
    ans += S(0, 0, n, n) * x * y;
    ans += S(0, b, n, n) * x;
    ans += S(0, 0, n, d) * x;
    ans += S(a, 0, n, n) * y;
    ans += S(0, 0, c, n) * y;
    cout << ans << "\n";
  }
}
