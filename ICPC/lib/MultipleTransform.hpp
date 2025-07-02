#pragma once

#include <lib/PrimeEnum.hpp>

struct MultipleTransform {
  template<typename T> static void ZetaTransform(vector<T> &v) {
    const int n = v.size() - 1;
    for(auto &p : PrimeEnum(n)) {
      for(ll i = n / p; i > 0; i--) { v[i] += v[i * p]; }
    }
  }
  template<typename T> static void MobiusTransform(vector<T> &v) {
    const int n = v.size() - 1;
    for(auto &p : PrimeEnum(n)) {
      for(ll i = 1; i * p <= n; i++) { v[i] -= v[i * p]; }
    }
  }
  template<typename I, typename T> static void ZetaTransform(map<I, T> &m) {
    for(auto &x : m) {
      for(auto p = m.rbegin(); p->first != x.first; p++) {
        if(p->first % x.first == 0) { x.second += p->second; }
      }
    }
  }
  template<typename I, typename T> static void MobiusTransform(map<I, T> &m) {
    for(auto p1 = m.rbegin(); p1 != m.rend(); p1++) {
      for(auto p2 = m.rbegin(); p2 != p1; p2++) {
        if(p2->first % p1->first == 0) { p1->second -= p2->second; }
      }
    }
  }
};