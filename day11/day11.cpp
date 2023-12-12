#include <iostream>
#include <string>
#include <vector>

using namespace std;
using ll = long long int;

vector<vector<char>> graph;

// dummy first item
vector<int> count_empty_rows_before() {
  vector<int> rows = {0};
  for (int i = 0; i < graph.size(); ++i) {
    int ok = 1;
    for (int j = 0; j < graph[0].size(); ++j) {
      if (graph[i][j] != '.') {
        ok = 0;
        break;
      }
    }

    rows.push_back(rows[i] + ok);
  }
  return rows;
}

// dummy first item
vector<int> count_empty_cols_before() {
  vector<int> cols = {0};
  for (int i = 0; i < graph[0].size(); ++i) {
    int ok = 1;
    for (int j = 0; j < graph.size(); ++j) {
      if (graph[j][i] != '.') {
        ok = 0;
        break;
      }
    }

    cols.push_back(cols[i] + ok);
  }
  return cols;
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

ll solve(int N) {
  vector<int> rows = count_empty_rows_before();
  vector<int> cols = count_empty_cols_before();
  vector<pair<int, int>> galaxies = get_galaxies();

  ll ans = 0LL;
  for (int i = 0; i < galaxies.size(); ++i) {
    auto &[y1, x1] = galaxies[i];
    for (int j = i + 1; j < galaxies.size(); ++j) {
      auto &[y2, x2] = galaxies[j];
      int empty_rows_in_between = abs(rows[y2] - rows[y1]);
      int empty_cols_in_between = abs(cols[x2] - cols[x1]);
      ans += 1LL * abs(y1 - y2) + abs(x1 - x2) - empty_rows_in_between +
             empty_rows_in_between * N - empty_cols_in_between +
             empty_cols_in_between * N;
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

  // cout << solve(2) << '\n'; // part 1
  cout << solve(1000000) << '\n'; // part 2
  return 0;
}
