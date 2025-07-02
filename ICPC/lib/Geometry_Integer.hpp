#pragma once

using Real = double;
constexpr double PI = 3.141592653589793238462643383279L;
Real rtod(Real r) { return r * 180.0 / PI; }
Real dtor(Real d) { return d * PI / 180.0; }

struct Point {
  ll x, y;
  Point(): x(0), y(0) {}
  Point(ll x, ll y): x(x), y(y) {}
  template<typename T, typename U> Point(const pair<T, U> &p): x(p.first), y(p.second) {}
  Point operator+(const Point &p) const { return {x + p.x, y + p.y}; }
  Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }
  Point operator*(ll r) const { return {x * r, y * r}; }
  Point operator/(ll r) const { return {x / r, y / r}; }
  Point &operator+=(const Point &p) { return *this = *this + p; }
  Point &operator-=(const Point &p) { return *this = *this - p; }
  Point &operator*=(ll r) { return *this = *this * r; }
  Point &operator/=(ll r) { return *this = *this / r; }
  bool operator<(const Point &p) const { return x != p.x ? x < p.x : y < p.y; }
  bool operator==(const Point &p) const { return x == p.x && y == p.y; }
  bool operator!=(const Point &p) const { return !(*this == p); }
  Point rotate90() const { return {-y, x}; }
  Point rotaet180() const { return {-x, -y}; }
  Point rotate270() const { return {y, -x}; }
  friend ll dot(const Point &l, const Point &r) { return l.x * r.x + l.y * r.y; }
  friend ll cross(const Point &l, const Point &r) { return l.x * r.y - l.y * r.x; }
  friend Real abs(const Point &p) { return sqrt(p.x * p.x + p.y * p.y); }
  friend ll norm(const Point &p) { return p.x * p.x + p.y * p.y; }
  friend Real distance(const Point &l, const Point &r) { return abs(l - r); }
  friend Real arg(const Point &p) { return atan2(p.y, p.x); }
  friend istream &operator>>(istream &is, Point &p) {
    ll a, b;
    cin >> a >> b;
    p = Point(a, b);
    return is;
  }
  friend ostream &operator<<(ostream &os, const Point &p) { return os << p.x << " " << p.y; }
};
using Points = vector<Point>;

Real angle(const Point &a, const Point &b, const Point &c) {
  const Point x = a - b, y = c - b;
  Real t1 = arg(x), t2 = arg(y);
  if(t1 > t2) { swap(t1, t2); }
  Real t = t2 - t1;
  return min(t, 2 * PI - t);
}

int ccw(const Point &a, const Point &b, const Point &c) {
  const Point x = b - a, y = c - a;
  if(cross(x, y) > 0) { return +1; }  // a,b,c counterclockwise
  if(cross(x, y) < 0) { return -1; }  // a,b,c clockwise
  if(min(norm(x), norm(y)) == 0) { return 0; }  // c=a or c=b
  if(dot(x, y) < 0) { return 2; }  // c-a-b
  if(norm(x) < norm(y)) { return -2; }  // a-b-c
  return 0;  // a-c-b
}

using Polygon = vector<Point>;
using Polygons = vector<Polygon>;

int Contains(const Polygon &P, const Point &p) {  // 0:out, 1:on, 2:in
  bool in = false;
  const int N = P.size();
  for(int i = 0; i < N; i++) {
    Point a = P[i] - p, b = P[(i + 1) % N] - p;
    if(a.y > b.y) { swap(a, b); }
    if(a.y < 0 && b.y > 0 && cross(a, b) < 0) { in = !in; }
    if(cross(a, b) == 0 && dot(a, b) < 0) { return 1; }
  }
  return in ? 2 : 0;
}

int ConvexContains(const Polygon &C, const Point &p) {  // 0:out, 1:on, 2:in
  const int N = C.size();
  if(N == 0) { return 0; }
  if(N == 1) { return C[0] == p; }
  ll b1 = cross(C[1] - C[0], p - C[0]), b2 = cross(C[N - 1] - C[0], p - C[0]);
  if(b1 < 0 || b2 > 0) { return 0; }
  int L = 1, R = N - 1;
  while(R - L > 1) {
    int M = (L + R) >> 1;
    (cross(p - C[0], C[M] - C[0]) >= 0 ? R : L) = M;
  }
  ll v = cross(C[L] - p, C[R] - p);
  if(!v) { return 1; }
  else if(v > 0) { return !b1 || !b2 ? 1 : 2; }
  return 0;
}

bool isConvex(const Polygon &P) {
  const int N = P.size();
  for(int i = 0; i < N; i++) {
    if(ccw(P[(i + N - 1) % N], P[i], P[(i + 1) % N]) == -1) { return false; }
  }
  return true;
}

template<bool boundary = false> Polygon ConvexHull(Polygon P, bool sorted = false) {
  if(!sorted) {
    sort(P.begin(), P.end());
    P.erase(unique(P.begin(), P.end()), P.end());
  }
  const int N = P.size();
  int k = 0;
  if(N <= 2) { return P; }
  Polygon C(2 * N);
  for(int i = 0; i < N; C[k++] = P[i++]) {
    while(k >= 2 && cross(C[k - 1] - C[k - 2], P[i] - C[k - 1]) < !boundary) { k--; }
  }
  for(int i = N - 2, t = k + 1; i >= 0; C[k++] = P[i--]) {
    while(k >= t && cross(C[k - 1] - C[k - 2], P[i] - C[k - 1]) < !boundary) { k--; }
  }
  C.resize(k - 1);
  return C;
}

Real Area(const Polygon &P) {
  const int N = P.size();
  Real A = 0;
  for(int i = 0; i < N; i++) { A += cross(P[i], P[(i + 1) % N]); }
  return A * 0.5;
}

pair<int, int> ConvexDiameter(const Polygon &P) {
  const int N = P.size();
  int i = 0, j = 0;
  for(int k = 1; k < N; k++) {
    if(P[k].y < P[i].y) { i = k; }
    if(P[k].y > P[j].y) { j = k; }
  }
  ll maxdis = norm(P[i] - P[j]);
  int maxi = i, maxj = j, is = i, js = j;
  do {
    if(cross(P[(i + 1) % N] - P[i], P[(j + 1) % N] - P[j]) >= 0) { j = (j + 1) % N; }
    else { i = (i + 1) % N; }
    if(norm(P[i] - P[j]) > maxdis) {
      maxdis = norm(P[i] - P[j]);
      maxi = i, maxj = j;
    }
  } while(i != is || j != js);
  return minmax(maxi, maxj);
}

pair<Point, Point> ClosestPair(Points P) {
  const int N = P.size();
  assert(N >= 2);
  sort(P.begin(), P.end());
  ll d = 9e18;
  Point a, b;
  auto f = [&](auto &&f, int l, int r) -> void {
    const int m = (l + r) >> 1;
    if(r - l <= 1) { return; }
    const ll x = P[m].x;
    f(f, l, m);
    f(f, m, r);
    inplace_merge(P.begin() + l, P.begin() + m, P.begin() + r, [](const auto &a, const auto &b) { return a.y < b.y; });
    vector<int> B;
    for(int i = l; i < r; i++) {
      if((P[i].x - x) * (P[i].x - x) >= d) { continue; }
      for(int j = (int)B.size() - 1; j >= 0; j--) {
        if((P[i].y - P[B[j]].y) * (P[i].y - P[B[j]].y) >= d) { break; }
        if(d > norm(P[i] - P[B[j]])) {
          d = norm(P[i] - P[B[j]]);
          a = P[i], b = P[B[j]];
        }
      }
      B.emplace_back(i);
    }
  };
  f(f, 0, N);
  return {a, b};
}