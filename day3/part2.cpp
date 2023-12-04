#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using ll = long long int;

unordered_set<string> is_adjacent(int i, int j, int H, int W, vector<string> &grid) {
  unordered_set<string> stars;
  pair<int, int> neighbors[8] = {{i-1, j-1}, {i-1, j}, {i-1, j+1}, {i, j+1}, {i+1, j+1}, {i+1, j}, {i+1, j-1}, {i, j-1}};
  for (auto &[r, c]: neighbors) {
    if (r < H && r >= 0 && c < W && c >= 0 && grid[r][c] == '*') {
      stars.insert(to_string(r) + "@" + to_string(c));
    }
  }
  return stars;
}

int main() {
  unordered_map<string, vector<int>> components;
  vector<string> grid;
  grid.reserve(145);
  string line;
  while (cin >> line) grid.push_back(line);

  ll ans = 0LL;
  int H = grid.size();
  int W = grid[0].length();
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      if (isdigit(grid[i][j])) {
        int val = grid[i][j] - '0';
        auto adj = is_adjacent(i, j, H, W, grid);
        grid[i][j] = '.';

        for (int k = j + 1; k < W; ++k) {
          if (!isdigit(grid[i][k])) {
            if (!adj.empty()) {
              for (auto &star : adj) components[star].push_back(val);
              adj.clear();
            }
            break;
          }
          val = val * 10 + (grid[i][k] - '0');
          auto tmp = is_adjacent(i, k, H, W, grid);
          adj.insert(tmp.begin(), tmp.end());
          grid[i][k] = '.';
        }

        if (!adj.empty()) {
          for (auto &star : adj) components[star].push_back(val);
        }
      }
    }
  }

  for (auto &[star, vals]: components) {
    if (vals.size() == 2) {
      ans += vals[0] * vals[1];
    }
  }

  cout << ans << '\n';
  return 0;
}
