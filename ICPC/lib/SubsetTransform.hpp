#pragma once

struct SubsetTransform {
  template<typename T> static void ZetaTransform(vector<T> &v) {
    const int n = v.size();
    for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
        for(int k = 0; k < i; k++) { v[j + k + i] += v[j + k]; }
      }
    }
  }
  template<typename T> static void MobiusTransform(vector<T> &v) {
    const int n = v.size();
    for(int i = 1; i < n; i <<= 1) {
      for(int j = 0; j < n; j += i << 1) {
        for(int k = 0; k < i; k++) { v[j + k + i] -= v[j + k]; }
      }
    }
  }
};