#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  vector<pair<ll, ll>> v(n);
  for(auto &[x, y] : v) {
    cin >> x >> y;
    y += x;
  }
  ranges::sort(v);
  auto compare = [](pair<ll, ll> x, pair<ll, ll> y) { return x.second > y.second; };  // yをtopに近い方に入れる条件
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, decltype(compare)> q(compare);
  ll t = v[0].first, idx = 0, r = 0;
  auto in = [&](ll t_) {
    for(; idx < n; idx++) {
      if(v[idx].first <= t_) { q.emplace(v[idx]); }
      else break;
    }
  };
  while(true) {
    in(t);
    while(!q.empty()) {
      auto [x, y] = q.top();
      q.pop();
      if(t <= y) {
        r++;
        t++;
      }
      in(t);
    }
    if(idx == n) { break; }
    t = v[idx].first;
  }
  cout << r << "\n";
}
