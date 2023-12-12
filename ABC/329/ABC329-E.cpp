#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, m;
  string s, t;
  cin >> n >> m >> s >> t;

  vector<bool> used(n - m + 1, false);
  queue<ll> q;

  auto check = [&](ll i) {
    if(used[i]) { return; }
    bool flag = true;
    for(ll j = 0; j < m; j++) {
      if(s[i + j] != '#' && s[i + j] != t[j]) { flag = false; }
    }
    if(flag) {
      used[i] = true;
      q.emplace(i);
    }
  };

  for(ll i = 0; i < n - m + 1; i++) { check(i); }

  while(!q.empty()) {
    auto i = q.front();
    q.pop();
    for(ll j = 0; j < m; j++) { s[i + j] = '#'; }
    for(ll j = max(i - m + 1, 0LL); j <= min(i + m - 1, n - m); j++) { check(j); }
  }

  cout << (ranges::all_of(s, [](auto x) { return x == '#'; }) ? "Yes" : "No") << "\n";
}
