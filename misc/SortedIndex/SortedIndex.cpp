vector<ll> idx(N);
iota(idx.begin(), idx.end(), 0);
ranges::sort(idx, [&](auto i, auto j) { return v[i] < v[j]; });
