#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <unordered_map>
#include <queue>

using namespace std;

unordered_map<string, pair<string, string>> graph;
string instructions;

void init() {
  getline(cin, instructions);

  string line;
  getline(cin, line); // blank
  while (getline(cin, line)) {
    istringstream ss(line);
    string key, equal, left, right;
    getline(ss, key, ' ');
    getline(ss, equal, ' ');
    getline(ss, left, ' ');
    getline(ss, right, ' ');
    left = left.substr(1, left.length() - 2);
    right = right.substr(0, right.length() - 1);
    graph[key] = {left, right};
  }
}

int part1() {
  int ans = 0;
  string node = "AAA";
  int cur = 0;
  while (node != "ZZZ") {
    if (instructions[cur] == 'L') node = graph[node].first;
    else node = graph[node].second;
    ++ans;
    cur = (cur + 1) % (int)(instructions.length());
  }

  return ans;
}

// TODO: the current code is too slow. Maybe need to cache?
int part2() {
  int ans = 0;
  queue<pair<string, int>> q1, q2; // {node, instruction index}
  for (auto &[u, v]: graph) {
     if (u.back() == 'A') q1.push({u, 0});
  }
  
  queue<pair<string, int>> *q = &q1, *otherq = &q2;

  while (true) {
    bool end = true;
    while (!q->empty()) {
      auto [node, i] = q->front();
      q->pop();

      int nexti = (i + 1) % (int)(instructions.length());
      string nextnode = (instructions[i] == 'L') ? graph[node].first : graph[node].second;
      otherq->push({nextnode, nexti});
      
      if (nextnode.back() != 'Z') end = false;
    }

    ++ans;

    if (end) break;
    
    swap(q, otherq);
  }

  return ans;
}

int main() {
  init();
  // cout << part1() << '\n';
  cout << part2() << '\n';
  return 0;
}
