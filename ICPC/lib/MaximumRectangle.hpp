#pragma once

// min l[i], max r[i] s.t. [l[i], r[i]] <= H[i], 0-indexed
pair<vector<ll>, vector<ll>> MaximumRectangle(vector<ll> &h) {
  ll n = h.size();
  vector<ll> l(n, 0), r(n, n - 1);
  stack<pair<ll, ll>> sl, sr;
  for(ll i = 0; i < n; i++) {
    while(!sl.empty() && h[i] <= sl.top().first) { sl.pop(); }
    if(!sl.empty()) { l[i] = sl.top().second + 1; }
    sl.emplace(h[i], i);
  }
  for(ll i = n - 1; i >= 0; i--) {
    while(!sr.empty() && h[i] <= sr.top().first) { sr.pop(); }
    if(!sr.empty()) { r[i] = sr.top().second - 1; }
    sr.emplace(h[i], i);
  }
  return {l, r};
}