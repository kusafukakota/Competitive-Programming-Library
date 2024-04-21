template<typename T, auto op, auto e> struct DequeAggregation {
 private:
  struct Itr {
    vector<pair<T, T>>::const_reverse_iterator it_l;
    vector<pair<T, T>>::const_reverse_iterator it_l_end;
    vector<pair<T, T>>::const_iterator it_r;
    vector<pair<T, T>>::const_iterator it_r_begin;
    Itr &operator++() {
      it_l == it_l_end ? it_r++ : it_l++;
      return *this;
    }
    Itr operator++(int) {
      Itr ret = *this;
      ++(*this);
      return ret;
    }
    Itr &operator--() {
      it_r == it_r_begin ? it_l-- : it_r--;
      return *this;
    }
    Itr operator--(int) {
      Itr ret = *this;
      --(*this);
      return ret;
    }
    Itr &operator+=(int diff) {
      if(diff < 0) { return *this -= -diff; }
      if(int d = it_l_end - it_l; d < diff) {
        it_l = it_l_end;
        it_r += diff - d;
      }
      else { it_l += diff; }
      return *this;
    }
    friend Itr operator+(Itr it, int diff) {
      it += diff;
      return it;
    }
    friend Itr operator+(int diff, Itr it) {
      it += diff;
      return it;
    }
    Itr &operator-=(int diff) {
      if(diff < 0) { return *this += -diff; }
      if(int d = it_r - it_r_begin; d < diff) {
        it_r = it_r_begin;
        it_l -= diff - d;
      }
      else { it_r -= diff; }
      return *this;
    }
    friend Itr operator-(Itr it, int diff) {
      it -= diff;
      return it;
    }
    int operator-(const Itr &r) const {
      int d1 = it_l == it_l_end ? it_r - it_r_begin : it_l - it_l_end;
      int d2 = r.it_l == r.it_l_end ? r.it_r - r.it_r_begin : r.it_l - r.it_l_end;
      return d1 - d2;
    }
    const T &operator[](int i) const { return *((*this) + i); }
    const T &operator*() const { return it_l == it_l_end ? it_r->first : it_l->first; }
    bool operator!=(const Itr &r) const { return it_l != r.it_l || it_r != r.it_r; }
    bool operator==(const Itr &r) const { return !(*this != r); }
    bool operator<(const Itr &r) const { return (*this) - r < 0; }
    bool operator<=(const Itr &r) const { return (*this) - r <= 0; }
    bool operator>(const Itr &r) const { return (*this) - r > 0; }
    bool operator>=(const Itr &r) const { return (*this) - r >= 0; }
  };

  vector<pair<T, T>> st_l, st_r;
  T prod(const vector<pair<T, T>> &st) const { return st.empty() ? e() : st.back().second; }

 public:
  DequeAggregation() = default;
  template<typename InputItr, enable_if_t<is_constructible_v<T, typename InputItr::T>, nullptr_t> = nullptr>
  DequeAggregation(InputItr first, InputItr last) {
    for(; first != last; first++) { push_back(*first); }
  }
  template<typename Container, enable_if_t<is_constructible_v<T, typename Container::T>, nullptr_t> = nullptr>
  DequeAggregation(const Container &c): DequeAggregation(begin(c), end(c)) {}
  T prod() const { return op(prod(st_l), prod(st_r)); }
  void push_back(const T &val) { st_r.emplace_back(val, op(prod(st_r), val)); }
  void push_front(const T &val) { st_l.emplace_back(val, op(val, prod(st_l))); }
  void pop_back() {
    if(st_r.size()) { return st_r.pop_back(); }
    const int sz = st_l.size();
    const int l = sz >> 1, r = sz - l;
    for(int i = r - 1; i; i--) { push_back(move(st_l[i].first)); }
    st_l.erase(st_l.begin(), st_l.begin() + r);
    if(!l) { return; }
    st_l[0].second = st_l[0].first;
    for(int i = 1; i < l; i++) { st_l[i].second = op(st_l[i].first, st_l[i - 1].second); }
  }
  void pop_front() {
    if(st_l.size()) { return st_l.pop_back(); }
    const int sz = st_r.size();
    const int r = sz >> 1, l = sz - r;
    for(int i = l - 1; i; i--) { push_front(move(st_r[i].first)); }
    st_r.erase(st_r.begin(), st_r.begin() + l);
    if(!r) { return; }
    st_r[0].second = st_r[0].first;
    for(int i = 1; i < r; i++) { st_r[i].second = op(st_r[i - 1].second, st_r[i].first); }
  }
  const T &front() const { return st_l.size() ? st_l.back().first : st_r.front().first; }
  const T &back() const { return st_r.size() ? st_r.back().first : st_l.front().first; }
  const T &operator[](int i) const {
    const int k = i - st_l.size();
    return k < 0 ? st_l[~k].first : st_r[k].first;
  }
  int size() const { return st_l.size() + st_r.size(); }
  void clear() {
    st_l.clear();
    st_r.clear();
  }
  void shrink() {
    st_l.shrink_to_fit();
    st_r.shrink_to_fit();
  }
  Itr begin() const { return Itr{st_l.rbegin(), st_l.rend(), st_r.begin(), st_r.begin()}; }
  Itr end() const { return Itr{st_l.rend(), st_l.rend(), st_r.begin(), st_r.end()}; }
  Itr cbegin() const { return begin(); }
  Itr cend() const { return end(); }
};
