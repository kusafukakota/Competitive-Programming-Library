#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n;
  string A, B;
  cin >> n >> A >> B;

  vector<ll> o(n);
  iota(o.begin(), o.end(), 0);
  vector<vector<ll>> p;
  do { p.emplace_back(o); } while(next_permutation(o.begin(), o.end()));
  ll s = ssize(p);

  vector<vector<char>> f(n, vector<char>(n, '.'));

  auto uni = [&]() {
    for(ll i = 0; i < n; i++) {
      ll c[3] = {};
      for(ll j = 0; j < n; j++) {
        if(f[i][j] != '.') { c[f[i][j] - 'A']++; }
      }
      if(c[0] != 1 || c[1] != 1 || c[2] != 1) { return false; }
    }
    for(ll i = 0; i < n; i++) {
      ll c[3] = {};
      for(ll j = 0; j < n; j++) {
        if(f[j][i] != '.') { c[f[j][i] - 'A']++; }
      }
      if(c[0] != 1 || c[1] != 1 || c[2] != 1) { return false; }
    }
    return true;
  };

  auto R = [&]() {
    for(ll i = 0; i < n; i++) {
      for(ll j = 0; j < n; j++) {
        if(f[i][j] != '.') {
          if(f[i][j] != A[i]) { return false; }
          else { break; }
        }
      }
    }
    return true;
  };

  auto C = [&]() {
    for(ll i = 0; i < n; i++) {
      for(ll j = 0; j < n; j++) {
        if(f[j][i] != '.') {
          if(f[j][i] != B[i]) { return false; }
          else { break; }
        }
      }
    }
    return true;
  };

  for(ll i = 0; i < s; i++) {
    for(ll j = 0; j < s; j++) {
      for(ll k = 0; k < s; k++) {
        for(ll x = 0; x < n; x++) {
          for(ll y = 0; y < n; y++) { f[x][y] = '.'; }
        }
        for(ll x = 0; x < n; x++) {
          ll a = p[i][x], b = p[j][x], c = p[k][x];
          f[x][a] = 'A', f[x][b] = 'B', f[x][c] = 'C';
        }
        if(!uni()) { continue; }
        if(R() && C()) {
          cout << "Yes\n";
          for(ll x = 0; x < n; x++) {
            for(ll y = 0; y < n; y++) { cout << f[x][y]; }
            cout << "\n";
          }
          return 0;
        }
      }
    }
  }
  cout << "No\n";
}
