template<typename T> struct Matrix : vector<vector<T>> {
  using vector<vector<T>>::vector;
  using vector<vector<T>>::operator=;
  Matrix() {}
  Matrix(int n) {
    this->assign(n, vector<T>(n, 0));
    for(ll i = 0; i < n; i++) {(*this)[i][i] = 1;}
  }
  Matrix(ll n, ll m, T x = 0) {
    for(ll i = 0; i < n; i++) {this->push_back(vector<T>(m, x));}
  }
  Matrix(vector<vector<T>> v) { *this = v; }
  Matrix operator+(const Matrix &m) const { return Matrix(*this) += m; }
  Matrix operator+(const T &x) const { return Matrix(*this) += x; }
  Matrix operator-(const Matrix &m) const { return Matrix(*this) -= m; }
  Matrix operator-(const T &x) const { return Matrix(*this) -= x; }
  Matrix operator*(const Matrix &m) const { return Matrix(*this) *= m; }
  Matrix operator*(const T &x) const { return Matrix(*this) *= x; }
  Matrix operator^(ll n) const { return Matrix(*this) ^= n; }
  Matrix operator+=(const Matrix &m) const {
    ll h = this->size(), w = (*this)[0].size();
    assert(h == m.size() && w == m[0].size());
    for(ll i = 0; i < h; i++) {
      for(ll j = 0; j < w; j++) { *this[i][j] += m[i][j]; }
    }
    return *this;
  }
  Matrix operator+=(const T &x) {
    ll h = this->size(), w = (*this)[0].size();
    for(ll i = 0; i < h; i++) {
      for(ll j = 0; j < w; j++) { *this[i][j] += x; }
    }
    return *this;
  }
  Matrix operator-=(const Matrix &m) {
    ll h = this->size(), w = (*this)[0].size();
    assert(h == m.size() && w == m[0].size());
    for(ll i = 0; i < h; i++) {
      for(ll j = 0; j < w; j++) { *this[i][j] -= m[i][j]; }
    }
    return *this;
  }
  Matrix operator-=(const T &x) {
    ll h = this->size(), w = (*this)[0].size();
    for(ll i = 0; i < h; i++) {
      for(ll j = 0; j < w; j++) { *this[i][j] -= x; }
    }
    return *this;
  }
  Matrix operator*=(const Matrix &m) {
    ll h = this->size(), w = (*this)[0].size();
    assert(w == (ll)m.size());
    vector<vector<T>> r(h, vector<T>(m[0].size(), T(0)));
    for(ll i = 0; i < h; i++) {
      for(ll j = 0; j < (ll)m[0].size(); j++) {
        for(ll k = 0; k < w; k++) { r[i][j] += (*this)[i][k] * m[k][j]; }
      }
    }
    this->swap(r);
    return *this;
  }
  Matrix operator*=(const T &x) {
    ll h = this->size(), w = (*this)[0].size();
    for(ll i = 0; i < h; i++) {
      for(ll j = 0; j < w; j++) { *this[i][j] *= x; }
    }
    return *this;
  }
  Matrix operator^=(ll n) {
    int h = this->size();
    Matrix m(h);
    while(n) {
      if(n & 1) {m *= *this;}
      *this *= *this;
      n >>= 1LL;
    }
    this->swap(m);
    return *this;
  }
};
