#pragma once

vector<vector<int>> DivisorTable(int N) {
  vector<vector<int>> div(N + 1);
  for(int i = 1; i <= N; i++) {
    for(int j = i; j <= N; j += i) { div[j].emplace_back(i); }
  }
  return div;
}