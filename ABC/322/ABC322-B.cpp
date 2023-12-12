#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n, m;
  cin >> n >> m;
  string s, t;
  cin >> s >> t;
  bool pre = t.starts_with(s), suf = t.ends_with(s);
  if(pre) {
    if(suf) { cout << 0 << "\n"; }
    else { cout << 1 << "\n"; }
  }
  else {
    if(suf) { cout << 2 << "\n"; }
    else { cout << 3 << "\n"; }
  }
}
