#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
using ll = long long int;

ll count(string &s, vector<int> &nums, int i, int j,
         unordered_map<string, ll> &memo) {
  if (i >= s.length()) {
    return j == nums.size();
  }

  if (j == nums.size()) {
    for (int k = i; k < s.length(); ++k) {
      if (s[k] == '#') {
        return 0;
      }
    }

    return 1;
  }

  string encode = to_string(i) + "|" + to_string(j);
  if (memo.find(encode) != memo.end())
    return memo[encode];

  ll ans = 0LL;

  // treat as '.'
  if (s[i] == '.' || s[i] == '?') {
    char c = s[i];
    s[i] = '.';
    ans += count(s, nums, i + 1, j, memo);
    s[i] = c;
  }

  // treat as '#'
  if (s[i] == '#' || s[i] == '?') {
    if (nums[j] <= (s.length() - i)) {
      for (int k = 0; k < nums[j]; ++k) {
        if (s[i + k] == '.') {
          memo[encode] = ans;
          return ans; // not enough damaged springs
        }
      }

      // the next spring after the group mustn't be operational
      if ((i + nums[j]) < s.length() && s[i + nums[j]] == '#') {
        memo[encode] = ans;
        return ans;
      }

      ans += count(s, nums, i + nums[j] + 1, j + 1, memo);
    }
  }

  memo[encode] = ans;
  return ans;
}

ll part2() {
  ll ans = 0LL;
  string pattern, record;
  while (cin >> pattern >> record) {
    istringstream ss(record);
    string num;
    vector<int> nums;
    while (getline(ss, num, ','))
      nums.push_back(stoi(num));

    string dup = pattern;
    vector<int> dupnums = nums;
    for (int i = 0; i < 4; ++i) {
      dup.push_back('?');
      dup.append(pattern);
      for (int j = 0; j < nums.size(); ++j)
        dupnums.push_back(nums[j]);
    }

    unordered_map<string, ll> memo;
    ans += count(dup, dupnums, 0, 0, memo);
  }

  return ans;
}

int main() {
  cout << part2() << '\n';
  return 0;
}
