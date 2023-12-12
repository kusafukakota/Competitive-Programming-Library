#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  ll n, x, y;
  cin >> n >> x >> y;
  vector<ll> X, Y;
  for(ll i = 0, a; i < n; i++) {
    cin >> a;
    if(i % 2) { X.emplace_back(a); }
    else { Y.emplace_back(a); }
  }

  ll sx = ssize(X), sy = ssize(Y), sfx = (sx + 1) / 2, slx = sx - sfx, sfy = (sy + 1) / 2, sly = sy - sfy;
  vector<ll> fx(1 << sfx), lx(1 << slx), fy(1 << sfy), ly(1 << sly);

  fx[0] = 0;
  for(ll l = 1; l <= sfx; l++) {
    for(ll i = (1 << l) - 1; i >= 0; i--) {
      if(i & (1 << l - 1)) { fx[i] = fx[i ^ (1 << l - 1)] + X[l - 1]; }
      else { fx[i] -= X[l - 1]; }
    }
  }

  lx[0] = x;
  for(ll l = 1; l <= slx; l++) {
    for(ll i = (1 << l) - 1; i >= 0; i--) {
      if(i & (1 << l - 1)) { lx[i] = lx[i ^ (1 << l - 1)] - X[sx - l]; }
      else { lx[i] += X[sx - l]; }
    }
  }

  fy[0] = 0;
  for(ll l = 1; l <= sfy; l++) {
    for(ll i = (1 << l) - 1; i >= 0; i--) {
      if(i & (1 << l - 1)) { fy[i] = fy[i ^ (1 << l - 1)] + Y[l - 1]; }
      else { fy[i] -= Y[l - 1]; }
    }
  }

  ly[0] = y;
  for(ll l = 1; l <= sly; l++) {
    for(ll i = (1 << l) - 1; i >= 0; i--) {
      if(i & (1 << l - 1)) { ly[i] = ly[i ^ (1 << l - 1)] - Y[sy - l]; }
      else { ly[i] += Y[sy - l]; }
    }
  }

  map<ll, ll> mx, my;
  for(ll i = 0; i < 1 << slx; i++) { mx[lx[i]] = i; }
  for(ll i = 0; i < 1 << sly; i++) { my[ly[i]] = i; }

  string d = "R";
  d.resize(n + 1);
  bool flx = false, fly = false;
  for(ll i = 0; i < 1 << sfx && !flx; i++) {
    if(!mx.contains(fx[i])) { continue; }
    for(ll j = 0; j < sfx; j++) { d[j * 2 + 2] = i & (1 << j) ? 'R' : 'L'; }
    for(ll j = 0; j < slx; j++) { d[sfx * 2 + j * 2 + 2] = mx[fx[i]] & (1 << slx - j - 1) ? 'R' : 'L'; }
    flx = true;
  }
  for(ll i = 0; i < 1 << sfy && !fly; i++) {
    if(!my.contains(fy[i])) { continue; }
    for(ll j = 0; j < sfy; j++) { d[j * 2 + 1] = i & (1 << j) ? 'U' : 'D'; }
    for(ll j = 0; j < sly; j++) { d[sfy * 2 + j * 2 + 1] = my[fy[i]] & (1 << sly - j - 1) ? 'U' : 'D'; }
    fly = true;
  }
  if(!flx || !fly) {
    cout << "No\n";
    return 0;
  }

  cout << "Yes\n";
  string r;
  r.resize(n);
  for(ll i = 0; i < n; i++) {
    if(d[i] == 'R') { r[i] = d[i + 1] == 'D' ? 'R' : 'L'; }
    if(d[i] == 'L') { r[i] = d[i + 1] == 'U' ? 'R' : 'L'; }
    if(d[i] == 'U') { r[i] = d[i + 1] == 'R' ? 'R' : 'L'; }
    if(d[i] == 'D') { r[i] = d[i + 1] == 'L' ? 'R' : 'L'; }
  }
  cout << r << "\n";
}
