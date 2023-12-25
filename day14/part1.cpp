#include <iostream>
#include <string>
#include <vector>
using namespace std;

int part1(vector<string> &puzzle) {
  const int H = puzzle.size();
  const int W = puzzle[0].length();

  for (int i = 1; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      if (puzzle[i][j] == 'O') {
        int row = i - 1;
        while (row >= 0 && puzzle[row][j] == '.')
          --row;
        swap(puzzle[row + 1][j], puzzle[i][j]);
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < H; ++i) {
    int count = 0;
    for (int j = 0; j < W; ++j) {
      count += (puzzle[i][j] == 'O');
    }
    ans += count * (H - i);
  }

  return ans;
}

int main() {
  vector<string> puzzle;
  string line;
  while (cin >> line)
    puzzle.push_back(line);
  cout << part1(puzzle) << '\n';
  return 0;
}
