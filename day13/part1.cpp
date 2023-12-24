#include <iostream>
#include <string>
#include <vector>
using namespace std;

int get_vertical_line(vector<string> &pattern) {
  const int N = pattern[0].length();
  for (int i = 1; i < N; ++i) {
    bool ok = true;

    // scan to the left and right
    int left = i - 1, right = i;
    while (left >= 0 && right < N) {
      ok = true;

      // compare columns
      for (int j = 0; j < pattern.size(); ++j) {
        if (pattern[j][left] != pattern[j][right]) {
          ok = false;
          break;
        }
      }

      if (!ok)
        break;
      --left;
      ++right;
    }

    if (ok)
      return i;
  }

  return -1;
}

int get_horizonal_line(vector<string> &pattern) {
  const int N = pattern[0].length();
  for (int j = 1; j < pattern.size(); ++j) {
    bool ok = true;

    // scan up and down
    int up = j - 1, down = j;
    while (up >= 0 && down < pattern.size()) {
      ok = true;

      // compare rows
      if (pattern[up] != pattern[down]) {
        ok = false;
        break;
      }

      --up;
      ++down;
    }

    if (ok)
      return j;
  }

  return -1;
}

int find_reflection(vector<string> &pattern) {
  int vert = get_vertical_line(pattern);
  if (vert != -1)
    return vert;
  return 100 * get_horizonal_line(pattern);
}

int main() {
  int ans = 0;
  string line;
  vector<string> pattern;
  while (getline(cin, line)) {
    if (line.empty()) {
      ans += find_reflection(pattern);
      pattern.clear();
    } else {
      pattern.push_back(line);
    }
  }

  ans += find_reflection(pattern);
  cout << ans << '\n';
  return 0;
}
