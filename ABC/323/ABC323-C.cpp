#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, m;
  cin >> n >> m;
  vector<ll> a(m);
  for(auto &i : a) { cin >> i; }
  vector<string> v(n);
  for(auto &i : v) { cin >> i; }
  vector<ll> cur(n, 0);
  vector<vector<ll>> yet(n);
  multiset<ll> pts;
  for(ll i = 0; i < n; i++) {
    cur[i] = i + 1;
    for(ll j = 0; j < m; j++) {
      if(v[i][j] == 'o') { cur[i] += a[j]; }
      else { yet[i].emplace_back(a[j]); }
    }
    ranges::sort(yet[i], ranges::greater());
    pts.insert(cur[i]);
  }
  for(ll i = 0; i < n; i++) {
    pts.erase(pts.find(cur[i]));
    ll mx = *pts.rbegin(), tmp = cur[i];
    bool flag = false;
    for(ll j = 0; j < ssize(yet[i]); j++) {
      if(tmp > mx) {
        cout << j << "\n";
        flag = true;
        break;
      }
      tmp += yet[i][j];
    }
    if(!flag) { cout << ssize(yet[i]) << "\n"; }
    pts.insert(cur[i]);
  }
}
