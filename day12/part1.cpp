#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int count(string &s, vector<int> &nums, int i, int j) {
  if (i >= s.length())
    return j == nums.size();

  if (j == nums.size()) {
    for (int k = i; k < s.length(); ++k) {
      if (s[k] == '#')
        return 0;
    }

    return 1;
  }

  int ans = 0;

  // treat as '.'
  if (s[i] == '.' || s[i] == '?') {
    char c = s[i];
    s[i] = '.';
    ans += count(s, nums, i + 1, j);
    s[i] = c;
  }

  // treat as '#'
  if (s[i] == '#' || s[i] == '?') {
    if (nums[j] <= (s.length() - i)) {
      for (int k = 0; k < nums[j]; ++k) {
        if (s[i + k] == '.') {
          return ans; // not enough damaged springs
        }
      }

      // the next spring after the group mustn't be operational
      if ((i + nums[j]) < s.length() && s[i + nums[j]] == '#')
        return ans;

      ans += count(s, nums, i + nums[j] + 1, j + 1);
    }
  }

  return ans;
}

int part1() {
  int ans = 0;
  string pattern, record;
  while (cin >> pattern >> record) {
    istringstream ss(record);
    string num;
    vector<int> nums;
    while (getline(ss, num, ','))
      nums.push_back(stoi(num));

    ans += count(pattern, nums, 0, 0);
  }
  return ans;
}

int main() {
  cout << part1() << '\n';
  return 0;
}
