#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

void north(vector<string> &puzzle) {
  for (int i = 1; i < puzzle.size(); ++i) {
    for (int j = 0; j < puzzle[0].length(); ++j) {
      if (puzzle[i][j] == 'O') {
        int row = i - 1;
        while (row >= 0 && puzzle[row][j] == '.') --row;
        swap(puzzle[row + 1][j], puzzle[i][j]);
      }
    }
  }
}

void west(vector<string> &puzzle) {
  for (int j = 1; j < puzzle[0].length(); ++j) {
    for (int i = 0; i < puzzle.size(); ++i) {
      if (puzzle[i][j] == 'O') {
        int col = j - 1;
        while (col >= 0 && puzzle[i][col] == '.') --col;
        swap(puzzle[i][col + 1], puzzle[i][j]);
      }
    }
  }
}

void south(vector<string> &puzzle) {
  for (int i = puzzle.size() - 2; i >= 0; --i) {
    for (int j = 0; j < puzzle[0].length(); ++j) {
      if (puzzle[i][j] == 'O') {
        int row = i + 1;
        while (row < puzzle.size() && puzzle[row][j] == '.') ++row;
        swap(puzzle[row - 1][j], puzzle[i][j]);
      }
    }
  }
}

void east(vector<string> &puzzle) {
  for (int j = puzzle[0].length() - 2; j >= 0; --j) {
    for (int i = 0; i < puzzle.size(); ++i) {
      if (puzzle[i][j] == 'O') {
        int col = j + 1;
        while (col < puzzle[0].length() && puzzle[i][col] == '.') ++col;
        swap(puzzle[i][col - 1], puzzle[i][j]);
      }
    }
  }
}

void print(vector<string> &puzzle) {
  for (auto &row: puzzle) {
    for (auto &x: row) cout << x;
    cout << '\n';
  }
}

string encode(vector<string> &puzzle) {
  string code = "";
  for (auto &s: puzzle) {
    code.push_back('@');
    code.append(s);
  }
  return code;
}

int cal(vector<string> &puzzle) {
  int ans = 0;
  for (int i = 0; i < puzzle.size(); ++i) {
    int count = 0;
    for (int j = 0; j < puzzle[0].length(); ++j) {
      count += (puzzle[i][j] == 'O');
    }
    ans += count * (puzzle.size() - i);
  }

  return ans;
}

// pattern will repeat after some cycles
int part2(vector<string> &puzzle) {
  unordered_map<string, int> seen;
  vector<int> calculation;

  int i = 0;
  int first_seen = 0;
  while (true) {
    north(puzzle);
    west(puzzle);
    south(puzzle);
    east(puzzle);
    
    string code = encode(puzzle);
    if (seen.find(code) != seen.end()) {
      first_seen = seen[code];
      break;
    }

    seen[code] = ++i;
    calculation.push_back(cal(puzzle));
  }

  int p = (1000000000 - first_seen) % (i - first_seen + 1) + first_seen;
  return calculation[p - 1];
}

int main() {
  vector<string> puzzle;
  string line;
  while (cin >> line) puzzle.push_back(line);
  cout << part2(puzzle) << '\n';
  return 0;
}
