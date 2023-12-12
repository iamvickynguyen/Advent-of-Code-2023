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
  ll acc_front = 0LL;
  int sign = 1;
  while (true) {
    int diff = (*cur)[1] - (*cur)[0];
    bool even_spaced = true;
    for (int i = 1; i < cur->size(); ++i) {
      int d = (*cur)[i] - (*cur)[i - 1];
      even_spaced &= (d == diff);
      tmp->push_back(d);
    }

    acc_front += 1LL * cur->front() * sign;
    sign *= -1;

    if (even_spaced) {
      acc_front += 1LL * tmp->front() * sign;
      break;
    }

    cur->clear();
    swap(cur, tmp);
  }

  return acc_front;
}

ll part2() {
  ll ans = 0LL;
  for (auto &row: input) ans += process(row);
  return ans;
} 

int main() {
  init();
  cout << part2() << '\n';
  return 0;
}
