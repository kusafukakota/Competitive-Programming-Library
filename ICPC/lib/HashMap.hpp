#pragma once

template<typename Key = ll, typename Val = ll, Val DefaultValue = Val(), Key UnusedKey = numeric_limits<Key>::max()> struct HashMap {
  using ull = unsigned long long;

 private:
  unsigned N, shift;
  vector<Key> keys;
  vector<Val> vals;
  vector<char> flag;
  static constexpr ull rng() {
    ull m = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    m ^= m >> 16;
    m ^= m << 32;
    return m;
  }

 public:
  HashMap(unsigned N_ = 1 << 20): N(1U << bit_width(N_ - 1)), shift(64 - __lg(N)), keys(N, UnusedKey), vals(N, DefaultValue), flag(N) { assert(!(N & (N - 1)) && N > 0); }
  Val &operator[](const Key &i) {
    static ull r = rng();
    unsigned hash = (ull(i) * r) >> shift;
    while(true) {
      if(!flag[hash]) {
        keys[hash] = i;
        flag[hash] = 1;
        return vals[hash];
      }
      if(keys[hash] == i) { return vals[hash]; }
      hash = (hash + 1) & (N - 1);
    }
  }
  // vector<pair<Key, Val>> enumerate() {
  //   vector<pair<Key, Val>> res;
  //   for(ll i = 0; i < N; i++) {
  //     if(flag[i]) { res.emplace_back(keys[i], vals[i]); }
  //   }
  //   return res;
  // }
};