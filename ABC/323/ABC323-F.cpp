#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct C {
  ll x, y;
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  C a, b, c;
  cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
  b.x -= a.x, b.y -= a.y;
  c.x -= a.x, c.y -= a.y;
}
