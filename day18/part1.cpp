#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

// Shoelace formula: https://en.wikipedia.org/wiki/Shoelace_formula
int get_area(vector<pair<int, int>> &points) {
  const int N = points.size();
  double area = 0.0;
  for (int i = 0; i < N; ++i) {
    int j = (i + 1) % N;
    auto &[y, x] = points[i];
    auto &[y1, x1] = points[j];
    area += (y * x1 - y1 * x);
  }
  return (int)(abs(area) / 2);
}

int main() {
  char c; int steps; string code;
  vector<pair<int, int>> points;
  int y = 0, x = 0;
  int b = 0;
  while (cin >> c >> steps >> code) {
    if (c == 'R') x += steps;
    else if (c == 'L') x -= steps;
    else if (c == 'U') y -= steps;
    else y += steps;
    points.push_back({y, x});
    b += steps;
  }

  // Pick's theorem: https://en.wikipedia.org/wiki/Pick%27s_theorem
  int A = get_area(points);
  int i = A + 1 - b / 2;
  cout << (i + b) << '\n';
  return 0;
}
