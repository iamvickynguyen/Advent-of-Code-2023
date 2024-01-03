#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <queue>
using namespace std;

// need to shift the point based on the top left point
void dig_path(vector<vector<char>> &grid, vector<tuple<char, int, string>> &data, const int H, const int W, const int left, const int up) {
  int cur_y = abs(up);
  int cur_x = abs(left);
  grid[cur_y][cur_x] = '#';

  for (auto &[dir, steps, code]: data) {
    if (dir == 'R') {
       for (int i = 1; i <= steps; ++i) grid[cur_y][cur_x + i] = '#';
       cur_x += steps;
    } else if (dir == 'L') {
       for (int i = 1; i <= steps; ++i) grid[cur_y][cur_x - i] = '#';
       cur_x -= steps;
    } else if (dir == 'U') {
       for (int i = 1; i <= steps; ++i) grid[cur_y - i][cur_x] = '#';
       cur_y -= steps;
    } else {
       for (int i = 1; i <= steps; ++i) grid[cur_y + i][cur_x] = '#';
       cur_y += steps;
    }
  }
}

int bfs(vector<vector<char>> &grid, const int i, const int j) {
  int count = 0;
  queue<pair<int, int>> q;
  q.push({i, j});
  grid[i][j] = '#';

  while (!q.empty()) {
    auto [y, x] = q.front();
    q.pop();
    ++count;

    pair<int, int> neighbors[4] = {{y - 1, x}, {y + 1, x}, {y, x - 1}, {y, x + 1}};
    for (auto &[row, col]: neighbors) {
      if (row >= 0 && row < grid.size() && col >= 0 && col < grid[0].size() && grid[row][col] == '.') {
        grid[row][col] = '#';
        q.push({row, col});
      }
    }
  }

  return count;
}

int count_exterior(vector<vector<char>> &grid, const int H, const int W) {
  int count = 0;
  for (int i = 0; i < H; ++i) {
    if (grid[i][0] == '.') count += bfs(grid, i, 0);
    if (grid[i][W - 1] == '.') count += bfs(grid, i, W - 1);
  }

  for (int j = 0; j < W; ++j) {
    if (grid[0][j] == '.') count += bfs(grid, 0, j);
    if (grid[H - 1][j] == '.') count += bfs(grid, H - 1, j);
  }

  return count;
}


int main() {
  vector<tuple<char, int, string>> data;
  char dir;
  int steps;
  string code;

  // find boundaries to initialize the grid
  int left = 0, right = 0, up = 0, down = 0;
  int cur_y = 0, cur_x = 0;
  while (cin >> dir >> steps >> code) {
    data.push_back({dir, steps, code});

    if (dir == 'R') {
      cur_x += steps;
      right = max(right, cur_x);
    } else if (dir == 'L') {
      cur_x -= steps;
      left = min(left, cur_x);
     } else if (dir == 'U') {
       cur_y -= steps;
       up = min(up, cur_y);
     } else {
        cur_y += steps;
        down = max(down, cur_y);
     }
  }

  const int H = down - up + 1;
  const int W = right - left + 1;
  vector<vector<char>> grid(H, vector<char>(W, '.'));
  dig_path(grid, data, H, W, left, up);
  cout << (H * W - count_exterior(grid, H, W)) << '\n';
  return 0;
}
