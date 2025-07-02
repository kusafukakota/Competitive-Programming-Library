#pragma once

template<typename T, typename Compare> struct ErasablePriorityQueue {
  priority_queue<T, vector<T>, Compare> q1, q2;
  ErasablePriorityQueue() {}
  ErasablePriorityQueue(initializer_list<T> ini): q1(ini.begin(), ini.end()) {}
  void push(T x) { q1.emplace(x); }
  void erase(T x) {
    if(!q1.empty() && q1.top() == x) {
      q1.pop();
      while(!q2.empty() && q1.top() == q2.top()) {
        q1.pop();
        q2.pop();
      }
    }
    else { q2.emplace(x); }
  }
  T top() const { return q1.top(); }
  void pop() { erase(top()); }
  int size() const { return q1.size() - q2.size(); }
  bool empty() const { return q1.empty(); }
};
