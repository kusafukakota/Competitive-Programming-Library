template<typename T, typename SequenceType> struct SuffixAutomatonBase {
  struct Node {
    map<T, int> nxt;
    int link, len;
    bool cloned;
    int index;
  };

  vector<Node> nodes;
  int last;

  SuffixAutomatonBase() {
    nodes.push_back({{}, -1, 0, false, -1});
    last = 0;
  }
  SuffixAutomatonBase(const SequenceType &s): SuffixAutomatonBase() {
    for(const T &c : s) { append(c); }
  }

  void append(const T &c) {
    const int new_node = nodes.size();
    const int new_node_index = nodes[last].index + 1;
    nodes.push_back({{}, -1, nodes[last].len + 1, false, new_node_index});
    int p = last;
    for(; p != -1 && !nodes[p].nxt.count(c); p = nodes[p].link) { nodes[p].nxt[c] = new_node; }
    const int q = p == -1 ? 0 : nodes[p].nxt[c];
    if(p == -1 || nodes[p].len + 1 == nodes[q].len) { nodes[new_node].link = q; }
    else {
      const int clone_node = nodes.size();
      nodes.push_back({nodes[q].nxt, nodes[q].link, nodes[p].len + 1, true, new_node_index});
      for(; p != -1 && nodes[p].nxt[c] == q; p = nodes[p].link) { nodes[p].nxt[c] = clone_node; }
      nodes[new_node].link = nodes[q].link = clone_node;
    }
    last = new_node;
  }
  SuffixAutomatonBase &operator+=(const T &c) {
    append(c);
    return *this;
  }

  int transition(const SequenceType &t, int invalid_state = -1) const {
    int cur = 0;
    for(const auto &c : t) {
      auto it = nodes[cur].nxt.find(c);
      if(it == nodes[cur].nxt.end()) { return invalid_state; }
      cur = it->second;
    }
    return cur;
  }

  bool accept(const SequenceType &t) const { return transition(t) != -1; }

  struct SubstringCounter {
   public:
    SubstringCounter(const SuffixAutomatonBase *sa): sa(sa), n(sa->nodes.size()), dp(n, 0) {
      const vector<Node> &nodes = sa->nodes;
      for(const int u : sa->topological_order(true)) {
        dp[u] += !nodes[u].cloned;
        const int p = nodes[u].link;
        if(p >= 0) { dp[p] += dp[u]; }
      }
    }
    long long count(const SequenceType &t) const {
      const int state = sa->transition(t);
      return state == -1 ? 0 : dp[state];
    }

   private:
    const SuffixAutomatonBase *sa;
    int n;
    vector<long long> dp;
  };

  SubstringCounter substring_counter() const & { return SubstringCounter{this}; }
  SubstringCounter substring_counter() const && = delete;

  struct SuffixLinkTree {
   public:
    SuffixLinkTree(const SuffixAutomatonBase *sa): sa(sa), g(sa->nodes.size()) {
      const int n = g.size();
      for(int i = 1; i < n; i++) { g[sa->nodes[i].link].push_back(i); }
    }
    int size() const { return g.size(); }
    const vector<int> &operator[](int i) const { return g[i]; }

   private:
    const SuffixAutomatonBase *sa;
    vector<vector<int>> g;
  };

  SuffixLinkTree suffix_link_tree() const & { return SuffixLinkTree(this); }
  SuffixLinkTree suffix_link_tree() const && = delete;

  struct OccurrenceEnumerator {
   public:
    OccurrenceEnumerator(const SuffixAutomatonBase *sa): sa(sa), t(sa->suffix_link_tree()) {}

    // returns vector of i s.t. S[i:i+|t|] = t
    vector<int> enumerate_all_occurrence(const SequenceType &pattern) const {
      const int state = sa->transition(pattern);
      if(state == -1) { return {}; }
      const vector<Node> &nodes = sa->nodes;
      const int l = pattern.size();
      vector<int> res;
      auto dfs = [&](auto self, int u) -> void {
        if(!nodes[u].cloned) { res.push_back(nodes[u].len - l); }
        for(const int v : t[u]) { self(self, v); }
      };
      dfs(dfs, state);
      return res;
    }

   private:
    const SuffixAutomatonBase *sa;
    SuffixLinkTree t;
  };

  OccurrenceEnumerator occurrence_enumerator() const & { return OccurrenceEnumerator(this); }
  OccurrenceEnumerator occurrence_enumerator() const && = delete;

  struct FirstOccurenceSearcher {
   public:
    FirstOccurenceSearcher(const SuffixAutomatonBase *sa): sa(sa) {
      const vector<Node> &nodes = sa->nodes;
      dp.resize(nodes.size(), numeric_limits<int>::max());
      for(const int u : sa->topological_order(true)) {
        if(!nodes[u].cloned) { dp[u] = nodes[u].len; }
        const int p = nodes[u].link;
        if(p >= 0 && nodes[p].cloned) { dp[p] = min(dp[p], dp[u]); }
      }
    }

    // returns min { i | S[i:i+|t|] = t }. if such i does !exist, returns -1.
    int first_occurrence(const SequenceType &t) const {
      const int state = sa->transition(t);
      if(state == -1) { return -1; }
      return dp[state] - t.size();
    }

   private:
    const SuffixAutomatonBase *sa;
    vector<int> dp;
  };

  FirstOccurenceSearcher first_occurence_searcher() const & { return FirstOccurenceSearcher(this); }
  FirstOccurenceSearcher first_occurence_searcher() const && = delete;

  // returns { start_s, start_t, len } s.t. lcs = s[start_s: start_s+len] t[start_t: start_t+len]
  tuple<int, int, int> longest_common_substring(const SequenceType &t) const {
    if(t.size() == 0) { return {0, 0, 0}; }
    const Node *v = &nodes[0];
    int l = 0, max_len = 0, s_end_pos = 0, t_end_pos = 0;
    for(int i = 0; i < (int)t.size(); i++) {
      while(v->link != -1 && !v->nxt.count(t[i])) {
        v = &nodes[v->link];
        l = v->len;
      }
      auto it = v->nxt.find(t[i]);
      if(it != v->nxt.end()) {
        v = &nodes[it->second];
        l++;
      }
      if(l > max_len) {
        max_len = l;
        t_end_pos = i;
        s_end_pos = v->index;
      }
    }
    if(max_len == 0) { return {0, 0, 0}; }
    return {s_end_pos - max_len + 1, t_end_pos - max_len + 1, max_len};
  }

  vector<int> topological_order(bool reversed = false) const {
    const int n = nodes.size();
    vector<int> in(n, 0);
    for(const auto &node : nodes) {
      for(const auto &p : node.nxt) { in[p.second]++; }
    }
    deque<int> dq;
    for(int i = 0; i < n; i++) {
      if(!in[i]) { dq.push_back(i); }
    }
    vector<int> res;
    while(dq.size()) {
      int u = dq.front();
      dq.pop_front();
      res.push_back(u);
      for(const auto &p : nodes[u].nxt) {
        if(!--in[p.second]) { dq.push_back(p.second); }
      }
    }
    if(reversed) { ranges::reverse(res); }
    assert((int)res.size() == n);
    return res;
  }
};

template<typename T> struct SuffixAutomaton : public SuffixAutomatonBase<T, vector<T>> {
  using SuffixAutomatonBase<T, vector<T>>::SuffixAutomatonBase;
  using value_type = T;
  using sequence_type = vector<T>;
};

template<typename T> SuffixAutomaton(vector<T>) -> SuffixAutomaton<T>;

template<> struct SuffixAutomaton<char> : public SuffixAutomatonBase<char, string> {
  using SuffixAutomatonBase<char, string>::SuffixAutomatonBase;
  using value_type = char;
  using sequence_type = string;
};

SuffixAutomaton(string) -> SuffixAutomaton<char>;

template<typename T> struct SubstringSet {
 public:
  using value_type = typename SuffixAutomaton<T>::sequence_type;
  using size_type = long long;
  using difference_type = size_type;

  // create empty set
  SubstringSet(): SubstringSet(value_type{}) {}
  // create set of all substrings in `s`
  SubstringSet(const value_type &s) { build(s); }
  // build set of all substrings in `s`
  void build(const value_type &s) {
    sa = SuffixAutomaton(s);
    dp.resize(sa.nodes.size(), size_type(1));
    for(const int u : sa.topological_order(true)) {
      for(const auto &p : sa.nodes[u].nxt) { dp[u] += dp[p.second]; }
    }
  }
  size_type size() const { return dp[0]; }
  bool contains(const value_type &t) const { return sa.accept(t); }
  // the k'th lexicographically smallest substring, O(|return value|).
  value_type operator[](size_type k) const {
    assert(0 <= k && k < dp[0]);
    int cur = 0;
    value_type res;
    while(k--) {
      for(const auto &[e, v] : sa.nodes[cur].nxt) {
        if(k < dp[v]) {
          res.push_back(e);
          cur = v;
          break;
        }
        else { k -= dp[v]; }
      }
    }
    return res;
  }
  // the k'th lexicographically smallest substring, O(|return value|).
  value_type kth_element(size_type k) const { return (*this)[k]; }
  // number of { s | s < t, s is in this set }, O(|min(t, max_substr_len)|).
  size_type count_lt(const value_type &t) const {
    size_type res = 0;
    int cur = 0;
    for(const T &c : t) {
      res++;
      auto it_r = sa.nodes[cur].nxt.lower_bound(c);
      for(auto it_l = sa.nodes[cur].nxt.begin(); it_l != it_r; it_l++) { res += dp[it_l->second]; }
      if(it_r == sa.nodes[cur].nxt.end() || it_r->first != c) { break; }
      cur = it_r->second;
    }
    return res;
  }
  // number of { s | s <= t, s is in this set }, O(min(|t|, max_substr_len)).
  size_type count_leq(const value_type &t) const { return count_lt(t) + contains(t); }
  // number of { s | s > t, s is in this set }, O(min(|t|, max_substr_len)).
  size_type count_gt(const value_type &t) const { return size() - count_leq(t); }
  // number of { s | s >= t, s is in this set }, O(min(|t|, max_substr_len)).
  size_type count_geq(const value_type &t) const { return size() - count_lt(t); }
  // number of { s | l <= s <= r, s is in this set }, O(min(|t|, max_substr_len)).
  size_type count_range(const value_type &l, const value_type &r) const { return l >= r ? 0 : count_lt(r) - count_lt(l); }

  // min { s | s >= t, s is in this set }, O(|return value| + min(|t|, max_substr_len))
  value_type min_geq(const value_type &t) const { return (*this)[count_lt(t)]; }
  // min { s | s > t, s is in this set }, O(|return value| + min(|t|, max_substr_len))
  value_type min_gt(const value_type &t) const { return (*this)[count_leq(t)]; }
  // max { s | s < t, s is in this set }, O(|return value| + min(|t|, max_substr_len))
  value_type max_lt(const value_type &t) const { return (*this)[count_lt(t) - 1]; }
  // max { s | s <= t, s is in this set }, O(|return value| + min(|t|, max_substr_len))
  value_type max_leq(const value_type &t) const { return (*this)[count_leq(t) - 1]; }

  // iterator

  // operator*: O(|return value|), other operations: O(1).
  struct SubstringSetIterator {
   public:
    SubstringSetIterator(const SubstringSet *st, size_type k): st(st), k(k) {}
    value_type operator*() const { return st->kth_substring(k); }
    auto &operator=(const SubstringSetIterator &other) {
      st = other.st;
      k = other.k;
      return *this;
    }
    auto &operator++() {
      k++;
      return *this;
    }
    auto &operator--() {
      k--;
      return *this;
    }
    auto &operator+=(difference_type d) {
      k += d;
      return *this;
    }
    auto &operator-=(difference_type d) {
      k -= d;
      return *this;
    }
    auto operator+(difference_type d) { return SubstringSetIterator{st, k + d}; }
    auto operator-(difference_type d) { return SubstringSetIterator{st, k - d}; }
    difference_type operator-(const SubstringSetIterator &other) { return k - other.k; }
    bool operator==(const SubstringSetIterator &other) const { return k == other.k; }
    bool operator!=(const SubstringSetIterator &other) const { return k != other.k; }
    bool operator<(const SubstringSetIterator &other) const { return k < other.k; }
    bool operator<=(const SubstringSetIterator &other) const { return k <= other.k; }
    bool operator>(const SubstringSetIterator &other) const { return k > other.k; }
    bool operator>=(const SubstringSetIterator &other) const { return k >= other.k; }

   protected:
    const SubstringSet *st;
    size_type k;
  };

  // operator*: O(|return value|), other operations: O(1).
  struct ReversedSubstringSetIterator : public SubstringSetIterator {
    using SubstringSetIterator::SubstringSetIterator;
    value_type operator*() const { return this->st->kth_element(this->st->size() - this->k - 1); }
  };
  using iterator = SubstringSetIterator;
  using reverse_iterator = ReversedSubstringSetIterator;
  using const_iterator = iterator;
  using const_reverse_iterator = reverse_iterator;
  auto begin() const { return iterator{this, 0LL}; }
  auto end() const { return iterator{this, size()}; }
  auto cbegin() const { return begin(); }
  auto cend() const { return end(); }
  auto rbegin() const { return reverse_iterator{this, 0LL}; }
  auto rend() const { return reverse_iterator{this, size()}; }
  auto crbegin() const { return rbegin(); }
  auto crend() const { return rend(); }
  // O(|min(t, max_substr_len)|).
  auto lower_bound(const value_type &t) const { return iterator{this, count_lt(t)}; }
  // O(|min(t, max_substr_len)|).
  auto upper_bound(const value_type &t) const { return iterator{this, count_leq(t)}; }
  // O(|min(t, max_substr_len)|).
  auto find(const value_type &t) const {
    auto it = lower_bound(t);
    if(it == end() || t != *it) { return end(); }
    return it;
  }

 private:
  SuffixAutomaton<T> sa;
  std::vector<size_type> dp;
};

template<typename T> SubstringSet(std::vector<T>) -> SubstringSet<T>;

SubstringSet(std::string) -> SubstringSet<char>;
