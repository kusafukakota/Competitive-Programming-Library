#pragma once

struct SuccinctIndexableDictionary {
  unsigned len, blk;
  vector<unsigned> bit, sum;
  SuccinctIndexableDictionary() = default;
  SuccinctIndexableDictionary(unsigned len): len(len), blk((len + 31) >> 5) {
    bit.assign(blk, 0U);
    sum.assign(blk, 0U);
  }
  void set(int k) { bit[k >> 5] |= 1U << (k & 31); }
  void build() {
    sum[0] = 0U;
    for(unsigned i = 1; i < blk; i++) { sum[i] = sum[i - 1] + __builtin_popcount(bit[i - 1]); }
  }
  bool operator[](ll k) { return (bool((bit[k >> 5] >> (k & 31)) & 1)); }
  int rank(int k) { return (sum[k >> 5] + __builtin_popcount(bit[k >> 5] & ((1U << (k & 31)) - 1))); }
  int rank(bool val, int k) { return (val ? rank(k) : k - rank(k)); }
};