#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>
using namespace std;

vector<string> grid;

int count() {
  int ans = 0;
  for (auto &row: grid) {
    for (auto &x: row) {
      if (x == 'O') ++ans;
    }
  }
  return ans;
}

int bfs(int i, int j) {
  const int H = grid.size();
  const int W = grid[0].size();
  queue<tuple<int, int, int>> q;
  q.push({i, j, 0});

  while (!q.empty()) {
    auto [y, x, steps] = q.front();
    q.pop();

    if (steps == 64) continue;

    grid[y][x] = '.';
    pair<int, int> neighbors[4] = {{y - 1, x}, {y + 1, x}, {y, x - 1}, {y, x + 1}};
    for (auto &[row, col]: neighbors) {
      if (row < H && row >= 0 && col < W && col >= 0 && grid[row][col] == '.') {
        grid[row][col] = 'O';
        q.push({row, col, steps + 1});
      }
    }
  }

  return count();
}

int part1() {
  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].length(); ++j) {
      if (grid[i][j] == 'S') return bfs(i, j);
    }
  }
  return 0;
}

int main() {
  string line;
  while (cin >> line) grid.push_back(line);
  cout << part1() << '\n';
  return 0; 
}
