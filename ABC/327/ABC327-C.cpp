#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool solve() {
  vector<vector<ll>> v(9, vector<ll>(9));
  for(auto &i : v) {
    for(auto &j : i) {
      cin >> j;
      j--;
    }
  }
  for(ll i = 0; i < 9; i++) {
    vector<ll> c(9, 0);
    for(ll j = 0; j < 9; j++) {
      c[v[i][j]]++;
    }
    for(ll j = 0; j < 9; j++) {
      if(c[j] != 1) { return false; }
    }
  }
  for(ll i = 0; i < 9; i++) {
    vector<ll> c(9, 0);
    for(ll j = 0; j < 9; j++) {
      c[v[j][i]]++;
    }
    for(ll j = 0; j < 9; j++) {
      if(c[j] != 1) { return false; }
    }
  }
  for(ll i = 0; i < 3; i++) {
    for(ll j = 0; j < 3; j++) {
      vector<ll> c(9, 0);
      for(ll x = 0; x < 3; x++) {
        for(ll y = 0; y < 3; y++) {
          ll p = i * 3 + x, q = j * 3 + y;
          c[v[p][q]]++;
        }
      }
      for(ll k = 0; k < 9; k++) {
        if(c[k] != 1) { return false; }
      }
    }
  }
  return true;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  ll t = 1;
  while(t--) {
    cout << (solve() ? "Yes" : "No") << "\n";
  }
}
