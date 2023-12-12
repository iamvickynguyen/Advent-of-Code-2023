#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
using ll = long long int;

vector<vector<int>> input;

void init() {
  string line;
  while (getline(cin, line)) {
    istringstream ss(line);
    string num;
    vector<int> row;
    while (getline(ss, num, ' ')) {
      row.push_back(stoi(num));
    }
    input.push_back(row);
  }
}

ll process(vector<int> &row) {
  vector<int> v1 = row, v2;
  vector<int> *cur = &v1, *tmp = &v2;
  ll acc_last = 0LL;
  while (true) {
    int diff = (*cur)[1] - (*cur)[0];
    bool even_spaced = true;
    for (int i = 1; i < cur->size(); ++i) {
      int d = (*cur)[i] - (*cur)[i - 1];
      even_spaced &= (d == diff);
      tmp->push_back(d);
    }

    acc_last += cur->back();

    if (even_spaced) {
      acc_last += tmp->back();
      break;
    }

    cur->clear();
    swap(cur, tmp);
  }

  return acc_last;
}

ll part1() {
  ll ans = 0LL;
  for (auto &row: input) ans += process(row);
  return ans;
} 

int main() {
  init();
  cout << part1() << '\n';
  return 0;
}
