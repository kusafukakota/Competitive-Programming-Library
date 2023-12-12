#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, s, m, l;
  cin >> n >> s >> m >> l;


  ll r = 1e18;
  for(ll i = 0; i < 50; i++) {
    for(ll j = 0; j < 50; j++) {
      for(ll k = 0; k < 50; k++) {
        if(i * 6 + j * 8 + k * 12 >= n) {
          r = min(r, i * s + j * m + k * l);
        }
      }
    }
  }
  cout << r << "\n";
}
