#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll N, S, K;
  cin >> N >> S >> K;

  ll r = 0;
  for(ll i = 0, p, q; i < N; i++) {
    cin >> p >> q;
    r += p * q;
  }
  if(r < S) { r += K; }
  cout << r << "\n";
}
