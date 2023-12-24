#include <iostream>
#include <string>
#include <vector>
using namespace std;

int get_vertical_line(vector<string> &pattern) {
  const int N = pattern[0].length();
  for (int i = 1; i < N; ++i) {
    int fix_count = 0;

    // scan to the left and right
    int left = i - 1, right = i;
    while (left >= 0 && right < N) {
      // compare columns
      for (int j = 0; j < pattern.size(); ++j) {
        if (pattern[j][left] != pattern[j][right]) {
          ++fix_count;
          if (fix_count > 1)
            break;
        }
      }

      if (fix_count > 1)
        break;
      --left;
      ++right;
    }

    if (fix_count == 1)
      return i;
  }

  return 0;
}

int get_horizonal_line(vector<string> &pattern) {
  const int N = pattern[0].length();
  for (int j = 1; j < pattern.size(); ++j) {
    int fix_count = 0;

    // scan up and down
    int up = j - 1, down = j;
    while (up >= 0 && down < pattern.size()) {
      // compare rows
      for (int i = 0; i < N; ++i) {
        if (pattern[up][i] != pattern[down][i]) {
          ++fix_count;
          if (fix_count > 1)
            break;
        }
      }

      if (fix_count > 1)
        break;
      --up;
      ++down;
    }

    if (fix_count == 1)
      return j;
  }

  return 0;
}

int find_reflection(vector<string> &pattern) {
  int vert = get_vertical_line(pattern);
  if (vert != 0)
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
