#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  vector<string> sa(4), sb(4), sc(4);
  for(auto &i : sa) { cin >> i; }
  for(auto &i : sb) { cin >> i; }
  for(auto &i : sc) { cin >> i; }
  vector<vector<ll>> A(4, vector<ll>(4, 0));
  vector<vector<ll>> B(4, vector<ll>(4, 0));
  vector<vector<ll>> C(4, vector<ll>(4, 0));
  for(ll i = 0; i < 4; i++) {
    for(ll j = 0; j < 4; j++) {
      if(sa[i][j] == '#') { A[i][j] = 1; }
      if(sb[i][j] == '#') { B[i][j] = 1; }
      if(sc[i][j] == '#') { C[i][j] = 1; }
    }
  }
  ll cnt = 0;
  for(ll i = 0; i < 4; i++) {
    for(ll j = 0; j < 4; j++) {
      if(A[i][j] == 1) { cnt++; }
      if(B[i][j] == 1) { cnt++; }
      if(C[i][j] == 1) { cnt++; }
    }
  }
  if(cnt != 16) {
    cout << "No\n";
    return 0;
  }
  vector<vector<int>> f(10, vector<int>(10, 0));
  auto F = [&](vector<vector<ll>> a, vector<vector<ll>> b, vector<vector<ll>> c) {
    for(ll AX = 0; AX < 7; AX++) {
      for(ll AY = 0; AY < 7; AY++) {
        for(ll BX = 0; BX < 7; BX++) {
          for(ll BY = 0; BY < 7; BY++) {
            for(ll CX = 0; CX < 7; CX++) {
              for(ll CY = 0; CY < 7; CY++) {
                bool flag = 1;
                for(ll x = 0; x < 4; x++) {
                  for(ll y = 0; y < 4; y++) {
                    if(a[x][y] && (AX + x < 3 || AX + x > 6 || AY + y < 3 || AY + y > 6)) {
                      flag = 0;
                      x = 5;
                      break;
                    }
                    if(b[x][y] && (BX + x < 3 || BX + x > 6 || BY + y < 3 || BY + y > 6)) {
                      flag = 0;
                      x = 5;
                      break;
                    }
                    if(c[x][y] && (CX + x < 3 || CX + x > 6 || CY + y < 3 || CY + y > 6)) {
                      flag = 0;
                      x = 5;
                      break;
                    }
                  }
                }
                if(!flag) { continue; }
                for(ll x = 0; x < 10; x++) {
                  for(ll y = 0; y < 10; y++) { f[x][y] = 0; }
                }
                for(ll x = 0; x < 4; x++) {
                  for(ll y = 0; y < 4; y++) {
                    f[AX + x][AY + y] |= a[x][y];
                    f[BX + x][BY + y] |= b[x][y];
                    f[CX + x][CY + y] |= c[x][y];
                  }
                }
                ll t = 0;
                for(ll x = 3; x < 7; x++) {
                  for(ll y = 3; y < 7; y++) {
                    if(f[x][y]) { t++; }
                  }
                }
                if(t == 16) {
                  return true;
                }
              }
            }
          }
        }
      }
    }
    return false;
  };
  ll n = 4;
  auto rotate = [&n]<typename T>(vector<vector<T>> &v) {
    vector<vector<T>> u(n, vector<T>(n));
    for(ll i = 0; i < n; i++) {
      for(ll j = 0; j < n; j++) {
        u[j][n - 1 - i] = v[i][j];
      }
    }
    v = u;
    return;
  };
  for(ll i = 0; i < 4; i++) {
    rotate(A);
    for(ll j = 0; j < 4; j++) {
      rotate(B);
      for(ll k = 0; k < 4; k++) {
        rotate(C);
        if(F(A, B, C)) {
          cout << "Yes\n";
          return 0;
        }
      }
    }
  }
  cout << "No\n";
}
