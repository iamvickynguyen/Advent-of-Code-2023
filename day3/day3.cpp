#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;
using ll = long long int;

bool is_adjacent(int i, int j, int H, int W, vector<string> &grid) {
  pair<int, int> neighbors[8] = {{i-1, j-1}, {i-1, j}, {i-1, j+1}, {i, j+1}, {i+1, j+1}, {i+1, j}, {i+1, j-1}, {i, j-1}};
  for (auto &[r, c]: neighbors) {
    if (r < H && r >= 0 && c < W && c >= 0 && !isdigit(grid[r][c]) && (grid[r][c] != '.')) {
      return true;
    }
  }
  return false;
}

int main() {
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
        bool adj = is_adjacent(i, j, H, W, grid);
        grid[i][j] = '.';

        for (int k = j + 1; k < W; ++k) {
          if (!isdigit(grid[i][k])) {
            if (adj) ans += val;
            break;
          }
          val = val * 10 + (grid[i][k] - '0');
          adj |= is_adjacent(i, k, H, W, grid);
          grid[i][k] = '.';
        }        
      }
    }
  }

  cout << ans << '\n';
  return 0;
}
