#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;
using ll = long long int;

// Shoelace formula: https://en.wikipedia.org/wiki/Shoelace_formula
ll get_area(vector<pair<int, int>> &points) {
  const int N = points.size();
  double area = 0.0;
  for (int i = 0; i < N; ++i) {
    int j = (i + 1) % N;
    auto &[y, x] = points[i];
    auto &[y1, x1] = points[j];
    area += (1LL * y * x1 - 1LL * y1 * x);
  }
  return (ll)(abs(area) / 2);
}

pair<char, int> parse_instruction(string &code) {
  char dir = 'U';
  int d = code[code.length() - 2] - '0';
  if (d == 0) dir = 'R';
  else if (d == 1) dir = 'D';
  else if (d == 2) dir = 'L';
  
  size_t pos;
  int steps = stoi(code.substr(2, code.length() - 4), &pos, 16);
  return {dir, steps};
}

int main() {
  char tmp; int tmp2; string code;
  vector<pair<int, int>> points;
  int y = 0, x = 0;
  int b = 0;
  while (cin >> tmp >> tmp2 >> code) {
    auto [c, steps] = parse_instruction(code);
    if (c == 'R') x += steps;
    else if (c == 'L') x -= steps;
    else if (c == 'U') y -= steps;
    else y += steps;
    points.push_back({y, x});
    b += steps;
  }

  // Pick's theorem: https://en.wikipedia.org/wiki/Pick%27s_theorem
  ll A = get_area(points);
  ll i = A + 1 - b / 2;
  cout << (i + b) << '\n';
  return 0;
}
