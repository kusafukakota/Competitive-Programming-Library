#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using namespace atcoder;
using ll = long long;
using mint = modint998244353;

vector<vector<mint>> COMTable(ll n) {
  vector<vector<mint>> r(n + 1, vector<mint>(n + 1, 0));
  for(ll i = 0; i <= n; i++) {
    for(ll j = 0; j <= i; j++) {
      if(j == 0 || j == i) { r[i][j] = 1; }
      else { r[i][j] = r[i - 1][j - 1] + r[i - 1][j]; }
    }
  }
  return r;
}

const mint inv = mint(2).inv();

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, m;
  cin >> n >> m;

  auto C = COMTable(230);
  ll mx = n / 2 * ((n + 1) / 2);

  vector<vector<mint>> color(n + 1, vector<mint>(mx + 1, 0));
  for(ll i = 0; i <= n; i++) {
    for(ll j = 0; j <= mx; j++) {
      for(ll k = 0; k <= i; k++) {
        color[i][j] += C[i][k] * C[k * (i - k)][j];
      }
    }
  }

  vector<vector<mint>> connected(n + 1, vector<mint>(mx + 1));
  for(ll i = 0; i <= n; i++) {
    for(ll j = 0; j <= mx; j++) {
      connected[i][j] = color[i][j];
      for(ll v = 1; v < i; v++) {
        for(ll e = 0; e <= j; e++) {
          connected[i][j] -= C[i - 1][v - 1] * connected[v][e] * color[i - v][j - e] * 2;
        }
      }
      connected[i][j] *= inv;  // colored -> colorless
    }
  }

  vector<vector<mint>> colorless(n + 1, vector<mint>(mx + 1));
  for(ll i = 0; i <= n; i++) {
    for(ll j = 0; j <= mx; j++) {
      colorless[i][j] = connected[i][j];
      for(ll v = 1; v < i; v++) {
        for(ll e = 0; e <= j; e++) {
          colorless[i][j] += C[i - 1][v - 1] * connected[v][e] * colorless[i - v][j - e];
        }
      }
    }
  }

  mint ans = 0;
  for(ll i = 0; i <= mx; i++) {
    mint tmp = 0;
    for(ll j = 1; j <= i; j++) {
      tmp += C[i][j] * mint(j).pow(m) * ((i - j) & 1 ? -1 : 1);
    }
    ans += tmp * colorless[n][i];
  }
  ans *= mint(2).pow(m);
  cout << ans.val() << "\n";
}
