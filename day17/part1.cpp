#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <utility>
#include <unordered_set>

using namespace std;
constexpr int INF = 2e9;

struct state {
  int y;
  int x;
  int dy;
  int dx;
  int steps;
  state(int y, int x, int dy, int dx, int steps): y(y), x(x), dy(dy), dx(dx), steps(steps) {}
};

string encode(int y, int x, int dy, int dx, int steps) {
  string result = to_string(y);
  result.push_back('#');
  result.append(to_string(x));
  result.push_back('#');
  result.append(to_string(dy));
  result.push_back('#');
  result.append(to_string(dx));
  result.push_back('#');
  result.append(to_string(steps));
  return result;
}

int dijkstra(vector<vector<int>> &graph) {
  const int H = graph.size();
  const int W = graph[0].size();
  unordered_set<string> seen;

  auto cmp = [](const pair<int, state> &a, const pair<int, state> &b) {
    return a.first > b.first;
  };

  priority_queue<pair<int, state>, vector<pair<int, state>>, decltype(cmp)> pq(cmp);
  pq.push({0, state(0, 0, 0, 0, 0)});

  while (!pq.empty()) {
    auto [d, obj] = pq.top();
    pq.pop();

    if (obj.y == H - 1 && obj.x == W - 1)
      return d;

    if (obj.steps < 3 && (obj.dy != 0 || obj.dx != 0)) {
      int i = obj.y + obj.dy;
      int j = obj.x + obj.dx;
      string id = encode(i, j, obj.dy, obj.dx, obj.steps + 1);
      if (i >= 0 && i < H && j >= 0 && j < W && seen.find(id) == seen.end()) {
        seen.insert(id);
        pq.push({d + graph[i][j], state(i, j, obj.dy, obj.dx, obj.steps + 1)});
      }
    }

    pair<int, int> dirs[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (auto &[dy, dx] : dirs) {
      if (!(dy == -obj.dy && dx == -obj.dx) && !(dy == obj.dy && dx == obj.dx)) {
        int i = obj.y + dy;
        int j = obj.x + dx;
        string id = encode(i, j, dy, dx, 1);
        if (i >= 0 && i < H && j >= 0 && j < W && seen.find(id) == seen.end()) {
          seen.insert(id);
          pq.push({d + graph[i][j], state(i, j, dy, dx, 1)});
        }
      }
    }
  }

  return INF;
}

int main() {
  vector<vector<int>> graph;
  string line;
  while (getline(cin, line)) {
    vector<int> row;
    for (auto &c: line) row.push_back(c - '0'); 
    graph.push_back(row);
  }

  cout << dijkstra(graph) << '\n';
  return 0;
}
