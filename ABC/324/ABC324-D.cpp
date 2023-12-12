#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll N = 10000000;
  vector<vector<int>> v(N, vector<int>(10, 0));
  for(ll i = 0; i < N; i++) {
    ll j = i * i;
    while(j) {
      v[i][j % 10]++;
      j /= 10;
    }
  }
  ll n;
  string s;
  cin >> n >> s;
  vector<int> t(10, 0);
  for(ll i = 0; i < n; i++) { t[s[i] - '0']++; }
  ll r = 0;
  for(ll i = 0; i < N; i++) {
    ll f = 1;
    for(ll j = 0; j < 10; j++) {
      if(j == 0) {
        if(v[i][j] > t[j]) {
          f = 0;
          break;
        }
      }
      else {
        if(v[i][j] != t[j]) {
          f = 0;
          break;
        }
      }
    }
    r += f;
  }
  cout << r << "\n";
}
