#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long int;

unordered_map<char, int> order = {
    {'A', 14}, {'K', 13}, {'Q', 12}, {'T', 10}, {'9', 9}, {'8', 8}, {'7', 7},
    {'6', 6},  {'5', 5},  {'4', 4},  {'3', 3},  {'2', 2}, {'J', 1}};

int get_type(const string &hand) {
  unordered_map<char, int> counter;
  int count3 = 0, count2 = 0;
  for (auto &c : hand)
    ++counter[c];

  for (auto &[k, v] : counter) {
    if (v == 5)
      return 6;
    if (v == 4) {
      if (counter['J'] > 0)
        return 6;
      return 5;
    }
    if (v == 3)
      ++count3;
    else if (v == 2)
      ++count2;
  }

  if (count3 > 0) {
    if (count2 > 0) {
      if (counter['J'] > 0)
        return 6;
      return 4;
    } else if (counter['J'] > 0) {
      return 5;
    } else {
      return 3;
    }
  } else if (count2 > 0) {
    if (count2 > 1) {
      if (counter['J'] > 1)
        return 5;
      else if (counter['J'] > 0)
        return 4;
      return 2;
    } else {
      if (counter['J'] > 0)
        return 3;
      return 1;
    }
    return 1;
  } else if (counter['J'] > 0) {
    return 1;
  }

  return 0;
}

bool strengthfunc(const pair<string, int> &hand1,
                  const pair<string, int> &hand2) {
  auto &[s1, v1] = hand1;
  auto &[s2, v2] = hand2;
  int type1 = get_type(s1);
  int type2 = get_type(s2);
  if (type1 != type2)
    return type1 < type2;

  for (int i = 0; i < s1.length(); ++i) {
    int a = order[s1[i]];
    int b = order[s2[i]];
    if (a != b)
      return a < b;
  }
  return true;
}

ll part2(vector<pair<string, int>> &hands) {
  sort(hands.begin(), hands.end(), strengthfunc);
  ll ans = 0LL;
  for (int i = 0; i < hands.size(); ++i) {
    ans += 1LL * (i + 1) * hands[i].second;
  }
  return ans;
}

int main() {
  vector<pair<string, int>> hands;
  string line;
  while (getline(cin, line)) {
    istringstream ss(line);
    string cards, val;
    getline(ss, cards, ' ');
    getline(ss, val, ' ');
    hands.push_back({cards, stoi(val)});
  }

  cout << part2(hands) << '\n';
  return 0;
}
