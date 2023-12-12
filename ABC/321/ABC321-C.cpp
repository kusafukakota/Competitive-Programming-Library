#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll n;
  cin >> n;
  priority_queue<ll, vector<ll>, greater<ll>> q;
  for(ll i = 1; i <= 9; i++) q.emplace(i);
  ll t;
  for(ll i = 0; i < n; i++) {
    t = q.top();
    q.pop();
    ll r = t % 10;
    for(ll j = 0; j < r; j++) { q.emplace(t * 10 + j); }
  }
  cout << t << "\n";
}
