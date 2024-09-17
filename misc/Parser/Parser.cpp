template<typename T> struct Parser {
 private:
  T exp(const string &s, int &p) {
    T r = term(s, p);
    while(s[p] == '+' || s[p] == '-') {
      if(s[p] == '+') { r += term(s, ++p); }
      else { r -= term(s, ++p); }
    }
    return r;
  }
  T term(const string &s, int &p) {
    T r = fac(s, p);
    while(s[p] == '*' || s[p] == '/') {
      if(s[p] == '*') { r *= fac(s, ++p); }
      else { r /= fac(s, ++p); }
    }
    return r;
  }
  T fac(const string &s, int &p) {
    if(isdigit(s[p])) { return num(s, p); }
    T r = exp(s, ++p);
    p++;
    return r;
  }
  T num(const string &s, int &p) {
    T r = 0;
    do {
      r *= 10;
      r += s[p++] - '0';
    } while(isdigit(s[p]));
    return r;
  }

 public:
  Parser() {}
  T solve(const string &s) {
    int p = 0;
    return exp(s, p);
  }
};
