#pragma once

#include <lib/Geometry_Line.hpp>

struct Segment : Line {
  Segment() = default;
  using Line::Line;
};
using Segments = vector<Segment>;

bool intersect(const Segment &s, const Point &p) { return ccw(s.a, s.b, p) == 0; }
bool intersect(const Line &l, const Segment &s) { return sign(cross(l.b - l.a, s.a - l.a)) * sign(cross(l.b - l.a, s.b - l.a)) <= 0; }
bool intersect(const Segment &l, const Segment &r) { return ccw(l.a, l.b, r.a) * ccw(l.a, l.b, r.b) <= 0 && ccw(r.a, r.b, l.a) * ccw(r.a, r.b, l.b) <= 0; }
Real distance(const Segment &s, const Point &p) { return intersect(s, projection(s, p)) ? distance(p, projection(s, p)) : min(distance(s.a, p), distance(s.b, p)); }
Real distance(const Line &l, const Segment &s) { return intersect(l, s) ? 0 : min(distance(l, s.a), distance(l, s.b)); }
Real distance(const Segment &l, const Segment &r) { return intersect(l, r) ? 0 : min({distance(l, r.a), distance(l, r.b), distance(r, l.a), distance(r, l.b)}); }

void MergeSegments(Segments &S) {
  auto merge_if_able = [](Segment &s1, const Segment &s2) {
    if(sign(cross(s1.b - s1.a, s2.b - s2.a)) == 1) { return 0; }
    if(ccw(s1.a, s2.a, s1.b) == 1 || ccw(s1.a, s2.a, s1.b) == -1) { return 0; }
    if(ccw(s1.a, s1.b, s2.a) == -2 || ccw(s2.a, s2.b, s1.a) == -2) { return 0; }
    s1 = Segment(min(s1.a, s2.a), max(s1.b, s2.b));
    return 1;
  };
  for(int i = 0; i < (int)S.size(); i++) {
    if(S[i].b < S[i].a) { swap(S[i].a, S[i].b); }
  }
  for(int i = 0; i < (int)S.size(); i++) {
    for(int j = i + 1; j < (int)S.size(); j++) {
      if(merge_if_able(S[i], S[j])) {
        S[j--] = S.back();
        S.pop_back();
      }
    }
  }
}

vector<vector<int>> SegmentArrangement(Segments &S, Points &P) {
  vector<vector<int>> g;
  const int N = S.size();
  for(int i = 0; i < N; i++) {
    P.push_back(S[i].a);
    P.push_back(S[i].b);
    for(int j = i + 1; j < N; j++) {
      const Point p1 = S[i].b - S[i].a, p2 = S[j].b - S[j].a;
      if(eq(cross(p1, p2))) { continue; }
      if(intersect(S[i], S[j])) { P.push_back(crosspoint(S[i], S[j])); }
    }
  }
  sort(P.begin(), P.end());
  P.erase(unique(P.begin(), P.end()), P.end());
  const int M = P.size();
  g.resize(M);
  for(int i = 0; i < N; i++) {
    vector<int> v;
    for(int j = 0; j < M; j++) {
      if(intersect(S[i], P[j])) { v.push_back(j); }
    }
    for(int j = 1; j < (int)v.size(); j++) {
      g[v[j - 1]].push_back(v[j]);
      g[v[j]].push_back(v[j - 1]);
    }
  }
  return g;
}