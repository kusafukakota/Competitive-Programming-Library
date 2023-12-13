auto floor(auto a, auto b) {
  assert(b != 0);
  if(b < 0) { a = -a, b = -b; }
  return a / b - (a % b < 0);
}

auto under(auto a, auto b) {
  assert(b != 0);
  if(b < 0) { a = -a, b = -b; }
  return a / b - (a % b <= 0);
}

auto ceil(auto a, auto b) {
  assert(b != 0);
  if(b < 0) { a = -a, b = -b; }
  return a / b + (a % b > 0);
}

auto over(auto a, auto b) {
  assert(b != 0);
  if(b < 0) { a = -a, b = -b; }
  return a / b + (a % b >= 0);
}
