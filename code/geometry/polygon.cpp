#include "lines.cpp"
typedef vector<point> polygon;
double polygon_area_signed(polygon p) {
  double area = 0; int cnt = size(p);
  rep(i,1,cnt-1) area += cross(p[i] - p[0], p[i + 1] - p[0]);
  return area / 2; }
double polygon_area(polygon p) {
  return abs(polygon_area_signed(p)); }
#define CHK(f,a,b,c) \
    (f(a) < f(b) && f(b) <= f(c) && ccw(a,c,b) < 0)
int point_in_polygon(polygon p, point q) {
  int n = size(p); bool in = false; double d;
  for (int i = 0, j = n - 1; i < n; j = i++)
    if (collinear(p[i], q, p[j]) &&
      0 <= (d = progress(q, p[i], p[j])) && d <= 1)
      return 0;
  for (int i = 0, j = n - 1; i < n; j = i++)
    if (CHK(real, p[i], q, p[j]) || CHK(real, p[j], q, p[i]))
      in = !in;
  return in ? -1 : 1; }
pair<polygon, polygon> cut_polygon(const polygon &poly,
                                   point a, point b) {
  polygon left, right; point it;
  for (int i = 0, cnt = poly.size(); i < cnt; i++) {
    point p = poly[i], q = poly[i == cnt-1 ? 0 : i + 1];
    if (ccw(a, b, p) < EPS) left.push_back(p);
    if (ccw(a, b, p) > -EPS) right.push_back(p);
    if (intersect(a, b, p, q, it, false, true))
      left.push_back(it), right.push_back(it); }
  return {left,right}; }
// vim: cc=60 ts=2 sts=2 sw=2:
