#pragma once

#if __cplusplus <= 201703L
#define ssize(v) ((int)(v).size())
template<typename T> ll bit_ceil(T n) {
  ll r = 1;
  while(r < n) { r <<= 1; }
  return r;
}
template<typename T> ll bit_width(T n) { return 64 - __builtin_clzll(n); }
template<typename T> ll countr_zero(T n) { return __builtin_ctzll(n); }
template<typename T> ll popcount(T n) { return __builtin_popcountll(n); }
namespace ranges {
template<typename T> void sort(vector<T> &v) { sort(v.begin(), v.end()); }
template<typename T> void stable_sort(vector<T> &v) { stable_sort(v.begin(), v.end()); }
template<typename T, typename F> void sort(vector<T> &v, const F &f) { sort(v.begin(), v.end(), f); }
template<typename T> void reverse(vector<T> &v) { reverse(v.begin(), v.end()); }
template<typename T> T max(const vector<T> &v) { return *max_element(v.begin(), v.end()); }
template<typename T> T min(const vector<T> &v) { return *min_element(v.begin(), v.end()); }
template<typename T, typename U> bool binary_search(const vector<T> &v, U x) { return binary_search(v.begin(), v.end(), x); }
template<typename T, typename F> bool all_of(const vector<T> &v, const F &f) { return all_of(v.begin(), v.end(), f); }
template<typename T, typename F> bool any_of(const vector<T> &v, const F &f) { return any_of(v.begin(), v.end(), f); }
template<typename T, typename F> bool none_of(const vector<T> &v, const F &f) { return none_of(v.begin(), v.end(), f); }
template<typename T, typename F> int count_if(const vector<T> &v, const F &f) { return count_if(v.begin(), v.end(), f); }
template<typename T, typename U> auto lower_bound(const vector<T> &v, U x) { return lower_bound(v.begin(), v.end(), x); }
template<typename T, typename U> auto upper_bound(const vector<T> &v, U x) { return upper_bound(v.begin(), v.end(), x); }
template<typename T, typename U, typename F> auto lower_bound(const vector<T> &v, U x, const F &f) { return lower_bound(v.begin(), v.end(), x, f); }
template<typename T, typename U, typename F> auto upper_bound(const vector<T> &v, U x, const F &f) { return upper_bound(v.begin(), v.end(), x, f); }
template<typename T> auto max_element(const vector<T> &v) { return max_element(v.begin(), v.end()); }
template<typename T> auto min_element(const vector<T> &v) { return min_element(v.begin(), v.end()); }
template<typename T, typename U> void fill(vector<T> &v, U x) { fill(v.begin(), v.end(), x); }
}  // namespace ranges
#endif