#include <atcoder/internal_math>
int RPG(int l, int r = 2e9) {
  int p = rng(l, r);
  if(atcoder::internal::is_prime_constexpr(p)) { return p; }
  return RPG(l, r);
}
