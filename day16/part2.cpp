#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> get_next(char dir, int y, int x, int H, int W) {
  if (dir == '>' && x + 1 < W) return {y, x + 1};
  if (dir == '<' && x - 1 >= 0) return {y, x - 1};
  if (dir == 'v' && y + 1 < H) return {y + 1, x};
  if (dir == '^' && y - 1 >= 0) return {y - 1, x};
  return {-1, -1};
}

vector<tuple<int, int, char>> get_next_with_vert(char dir, int y, int x, int H, int W) {
  vector<tuple<int, int, char>> directions;
  if (dir == '>' || dir == '<') {
    if (y - 1 >= 0) directions.push_back({y - 1, x, '^'});
    if (y + 1 < H) directions.push_back({y + 1, x, 'v'});
  } else if (dir == 'v' && y + 1 < H) directions.push_back({y + 1, x, 'v'});
  else if (dir == '^' && y - 1 >= 0) directions.push_back({y - 1, x, '^'});
  return directions;
}

vector<tuple<int, int, char>> get_next_with_hor(char dir, int y, int x, int H, int W) {
  vector<tuple<int, int, char>> directions;
  if (dir == '^' || dir == 'v') {
    if (x - 1 >= 0) directions.push_back({y, x - 1, '<'});
    if (x + 1 < W) directions.push_back({y, x + 1, '>'});
  } else if (dir == '>' && x + 1 < W) directions.push_back({y, x + 1, '>'});
  else if (dir == '<' && x - 1 >= 0) directions.push_back({y, x - 1, '<'});
  return directions;
}

tuple<int, int, char> get_next_with_slash(char dir, int y, int x, int H, int W) {
  if (dir == '>' && y - 1 >= 0) return {y - 1, x, '^'};
  if (dir == '<' && y + 1 < H) return {y + 1, x, 'v'};
  if (dir == 'v' && x - 1 >= 0) return {y, x - 1, '<'};
  if (dir == '^' && x + 1 < W) return {y, x + 1, '>'};
  return {-1, -1, dir};
}

tuple<int, int, char> get_next_with_backslash(char dir, int y, int x, int H, int W) {
  if (dir == '>' && y + 1 < H) return {y + 1, x, 'v'};
  if (dir == '<' && y - 1 >= 0) return {y - 1, x, '^'};
  if (dir == 'v' && x + 1 < W) return {y, x + 1, '>'};
  if (dir == '^' && x - 1 >= 0) return {y, x - 1, '<'};
  return {-1, -1, dir};
}

int count(vector<string> &grid, int start_y, int start_x, char start_dir) {
  const int H = grid.size();
  const int W = grid[0].length();
  vector<vector<string>> seen(H, vector<string>(W, ""));
  queue<tuple<int, int, char, int>> q;
  q.push({start_y, start_x, start_dir, 0});

  while (!q.empty()) {
    auto [y, x, dir, steps] = q.front();
    q.pop();

    if (seen[y][x].find(dir) != std::string::npos) continue;
    seen[y][x].push_back(dir);

    if (grid[y][x] == '.') {
      auto [next_y, next_x] = get_next(dir, y, x, H, W);
      if (next_y != -1) {
        q.push({next_y, next_x, dir, steps + 1});
      }
    } else if (grid[y][x] == '|') {
      auto directions = get_next_with_vert(dir, y, x, H, W);
      for (auto &[next_y, next_x, next_dir] : directions) {
        q.push({next_y, next_x, next_dir, steps + 1});
      }
    } else if (grid[y][x] == '-') {
      auto directions = get_next_with_hor(dir, y, x, H, W);
      for (auto &[next_y, next_x, next_dir] : directions) {
        q.push({next_y, next_x, next_dir, steps + 1});
      }
    } else if (grid[y][x] == '/') {
      auto [next_y, next_x, next_dir] = get_next_with_slash(dir, y, x, H, W);
      if (next_y != -1) {
        q.push({next_y, next_x, next_dir, steps + 1});
      }
    } else if (grid[y][x] == '\\') {
      auto [next_y, next_x, next_dir] =
          get_next_with_backslash(dir, y, x, H, W);
      if (next_y != -1) {
        q.push({next_y, next_x, next_dir, steps + 1});
      }
    }
  }

  int ans = 0;
  for (auto &row : seen) {
    for (auto &s : row) ans += !s.empty();
  }

  return ans;
}

int part2(vector<string> &grid) {
  const int H = grid.size();
  const int W = grid[0].length();
  int ans = 0;

  for (int i = 0; i < W; ++i) ans = max(ans, count(grid, 0, i, 'v'));
  for (int i = 0; i < W; ++i) ans = max(ans, count(grid, H - 1, i, '^'));
  for (int i = 0; i < H; ++i) ans = max(ans, count(grid, i, 0, '>'));
  for (int i = 0; i < H; ++i) ans = max(ans, count(grid, i, W - 1, '<'));

  return ans;
}

int main() {
  vector<string> grid;
  string line;
  while (getline(cin, line)) grid.push_back(line);
  int ans = part2(grid);
  cout << ans << '\n';
  return 0;
}
