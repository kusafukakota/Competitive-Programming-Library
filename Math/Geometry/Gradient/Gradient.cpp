void grd(ll &dx, ll &dy) {
  ll g = gcd(dx, dy);
  dx /= g, dy /= g;
  if(dx < 0) { dx *= -1, dy *= -1; }
  if(!dx) { dy = 1; }
  if(!dy) { dx = 1; }
}
