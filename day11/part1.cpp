#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

vector<vector<char>> graph;

unordered_set<int> get_empty_rows() {
  unordered_set<int> rows;
  for (int i = 0; i < graph.size(); ++i) {
    bool ok = true;
    for (int j = 0; j < graph[0].size(); ++j) {
      if (graph[i][j] != '.') {
        ok = false;
        break;
      }
    }

    if (ok)
      rows.insert(i);
  }
  return rows;
}

unordered_set<int> get_empty_cols() {
  unordered_set<int> cols;
  for (int i = 0; i < graph[0].size(); ++i) {
    bool ok = true;
    for (int j = 0; j < graph.size(); ++j) {
      if (graph[j][i] != '.') {
        ok = false;
        break;
      }
    }

    if (ok)
      cols.insert(i);
  }
  return cols;
}

void create_new_graph(unordered_set<int> &rows, unordered_set<int> &cols) {
  vector<vector<char>> expandcol_graph;
  for (int i = 0; i < graph.size(); ++i) {
    vector<char> row;
    for (int j = 0; j < graph[0].size(); ++j) {
      row.push_back(graph[i][j]);
      if (cols.find(j) != cols.end()) {
        row.push_back('.');
      }
    }
    expandcol_graph.push_back(row);
  }

  vector<vector<char>> newgraph;
  for (int i = 0; i < graph.size(); ++i) {
    newgraph.push_back(expandcol_graph[i]);
    if (rows.find(i) != rows.end()) {
      newgraph.push_back(expandcol_graph[i]);
    }
  }

  graph = std::move(newgraph);
}

vector<pair<int, int>> get_galaxies() {
  vector<pair<int, int>> galaxies;
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[0].size(); ++j) {
      if (graph[i][j] == '#')
        galaxies.push_back({i, j});
    }
  }
  return galaxies;
}

int part1() {
  unordered_set<int> rows = get_empty_rows();
  unordered_set<int> cols = get_empty_cols();
  create_new_graph(rows, cols);
  vector<pair<int, int>> galaxies = get_galaxies();

  int ans = 0;
  for (int i = 0; i < galaxies.size(); ++i) {
    auto &[y1, x1] = galaxies[i];
    for (int j = i + 1; j < galaxies.size(); ++j) {
      auto &[y2, x2] = galaxies[j];
      ans += abs(y1 - y2) + abs(x1 - x2);
    }
  }

  return ans;
}

int main() {
  string line;
  while (getline(cin, line)) {
    vector<char> row = vector<char>(line.begin(), line.end());
    graph.push_back(std::move(row));
  }
  cout << part1() << '\n';
  return 0;
}
