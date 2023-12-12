#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, m, l;
  cin >> n >> m >> l;

  vector<ll> a(n), b(m);
  for(auto &i : a) { cin >> i; }
  for(auto &i : b) { cin >> i; }
  vector<ll> ng;
  for(ll i = 0; i < l; i++) {
    ll c, d;
    cin >> c >> d;
    c--, d--;
    ng.emplace_back(a[c] + b[d]);
  }

  ranges::sort(a);
  ranges::sort(b);

  auto p = [&]() {
    for(ll L = 0, R = 3e9;;) {
      if(R - L <= 1) { return L; }
      ll M = (L + R) / 2;
      ll c = 0;
      for(ll i = 0; i < n; i++) {
        ll idx = b.end() - ranges::lower_bound(b, M - a[i]);
        c += idx;
      }
      c > l ? L = M : R = M;
    }
  }();

  multiset<ll> s;
  for(ll i = 0; i < n; i++) {
    ll idx = ranges::lower_bound(b, p - a[i]) - b.begin();
    for(ll j = idx; j < m; j++) {
      s.insert(a[i] + b[j]);
    }
  }

  for(auto &i : ng) {
    if(i >= p) { s.erase(s.find(i)); }
  }
  cout << *s.rbegin() << "\n";
}
