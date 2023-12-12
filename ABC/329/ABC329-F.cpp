#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, q;
  cin >> n >> q;
  vector<set<ll>> s(n);
  for(ll i = 0; i < n; i++) {
    ll c;
    cin >> c;
    s[i].insert(c);
  }

  while(q--) {
    ll a, b;
    cin >> a >> b;
    a--, b--;
    if(ssize(s[a]) <= ssize(s[b])) {
      for(auto &i : s[a]) { s[b].insert(i); }
      s[a].clear();
    }
    else {
      for(auto &i : s[b]) { s[a].insert(i); }
      s[b].clear();
      swap(s[a], s[b]);
    }
    cout << ssize(s[b]) << "\n";
  }
}
