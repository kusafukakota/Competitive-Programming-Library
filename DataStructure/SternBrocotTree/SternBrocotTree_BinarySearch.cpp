pair<pair<ll, ll>, pair<ll, ll>> SternBrocotTree_BinarySearch(function<bool(pair<ll, ll>)> f, const ll &INF) {
  assert(INF >= 0);
  SternBrocotTree m;
  if(INF == 0) { return {m.lower_bound(), m.upper_bound()}; }
  auto over = [&](bool return_value) {
    return max(m.x, m.y) > INF || f(m.get()) == return_value;
  };
  if(f(make_pair(0, 1))) { return {m.lower_bound(), m.upper_bound()}; }
  ll go_left = over(true);
  for(; true; go_left ^= 1) {
    if(go_left) {
      ll a = 1;
      for(; true; a *= 2) {
        m.go_left(a);
        if(over(false)) {
          m.go_parent(a);
          break;
        }
      }
      for(a /= 2; a != 0; a /= 2) {
        m.go_left(a);
        if(over(false)) { m.go_parent(a); }
      }
      m.go_left();
      if(max(m.get().first, m.get().second) > INF) { return {m.lower_bound(), m.upper_bound()}; }
    }
    else {
      ll a = 1;
      for(; true; a *= 2) {
        m.go_right(a);
        if(over(true)) {
          m.go_parent(a);
          break;
        }
      }
      for(a /= 2; a != 0; a /= 2) {
        m.go_right(a);
        if(over(true)) { m.go_parent(a); }
      }
      m.go_right();
      if(max(m.get().first, m.get().second) > INF) { return {m.lower_bound(), m.upper_bound()}; }
    }
  }
}
