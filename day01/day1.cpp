#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ll = long long int;

ll part1() {
  ll ans = 0LL;

  string line;
  int first, last;
  while (cin >> line) {
    for (int i = 0; i < line.length(); ++i) {
      if (isdigit(line[i])) {
        first = line[i] - '0';
        break;
      }
    }

    for (int i = line.length() - 1; i >= 0; --i) {
      if (isdigit(line[i])) {
        last = line[i] - '0';
        break;
      }
    }

    ans += first * 10 + last;
  }

  return ans;
}

int is_valid(string &number) {
  vector<pair<string, int>> nums = {{"one", 1},   {"two", 2},   {"three", 3},
                                    {"four", 4},  {"five", 5},  {"six", 6},
                                    {"seven", 7}, {"eight", 8}, {"nine", 9}};

  int result = 0, index = number.length();
  for (auto &[word, val] : nums) {
    auto pos = number.find(word);
    if (pos != string::npos) {
      if (pos < index) {
        result = val;
        index = pos;
      }
    }
  }

  return result;
}

int get_first_num(string &line, bool rev = false) {
  for (int i = 0; i < line.length(); ++i) {
    if (isdigit(line[i]))
      return line[i] - '0';

    string number = "";
    for (int j = i; j < min((int)line.length(), i + 6); ++j) {
      if (isdigit(line[j])) {
        string num = number;
        if (rev)
          reverse(num.begin(), num.end());
        if (int val = is_valid(num))
          return val;
        return line[j] - '0';
      } else
        number.push_back(line[j]);
    }

    if (rev)
      reverse(number.begin(), number.end());
    if (int val = is_valid(number))
      return val;
  }

  return 0;
}

ll part2() {
  ll ans = 0LL;

  string line;
  while (cin >> line) {
    int first = get_first_num(line);
    reverse(line.begin(), line.end());
    int last = get_first_num(line, true);
    ans += first * 10 + last;
  }

  return ans;
}

int main() {
  // cout << part1() << '\n';
  cout << part2() << '\n';
  return 0;
}
