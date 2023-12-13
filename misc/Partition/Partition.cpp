vector<vector<ll>> Partition;
function<void(vector<ll>)> DFS = [&](vector<ll> v) {
  Partition.emplace_back(v);
  ll s = v.size();
  if(s == 1) {
    for(ll i = 1; i <= v[0] / 2; i++) {
      vector<ll> nv = {i, v[0] - i};
      DFS(nv);
    }
  }
  else {
    for(ll i = v[s - 2]; i <= v[s - 1] / 2; i++) {
      vector<ll> nv = v;
      nv.pop_back();
      nv.emplace_back(i);
      nv.emplace_back(v[s - 1] - i);
      DFS(nv);
    }
  }
};
DFS({n});
