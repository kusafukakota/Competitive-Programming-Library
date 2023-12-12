#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve() {
  ll n, x, k;
  cin >> n >> x >> k;
  ll d = 63 - __builtin_clzll(x);
  auto f = [&](ll s, ll t) -> ll {
    if(t < 0) return 0;
    if(t >= 64) return 0;
    __int128_t l = s, r = s;
    for(ll i = 0; i < t; i++) {
      l *= 2;
      r *= 2;
      r++;
    }
    if(n < l) return 0;
    else return min(n - l + 1, r - l + 1);
  };
  ll ans = 0, y = x, le = k;
  while(y > 1) {
    if(y % 2) {
      ans += f(y - 1, le - 2);
    }
    else {
      ans += f(y + 1, le - 2);
    }
    y /= 2;
    le--;
  }
  if(k && d >= k) ans++;
  ans += f(x, k);
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll t;
  cin >> t;
  while(t--) {
    cout << solve() << "\n";
  }
}
