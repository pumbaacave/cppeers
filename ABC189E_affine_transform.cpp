#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits.h>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <array>
#include <math.h>
#include <assert.h>

#define rep(i, n) for (int i = 0; i < (n); i++)

using namespace std;

#define ll long long
#define all(v) v.begin(),v.end()
#define bootstrap ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

static vector<vector<int>> clock90, counter90;


vector<vector<int>> mul(vector<vector<int>> left, vector<vector<int>> right) {
    assert(left[0].size() == right.size());
    vector<vector<int>> ret;
    int num = left[0].size();
    for (auto l_row: left) {
        vector<int> row;
        rep(i, right[0].size()) {
            int cur = 0;
            rep(j, num) {
                cur += l_row[j] * right[num][i];
            }
            row.push_back(cur);
        }
        ret.push_back(row);
    }
}

vector<vector<int>> reflect_x(int num) {
    vector<vector<int>> ret;
    ret.push_back(vector<int>{-1, 0, 2 * num});
    ret.push_back(vector<int>{0, 1, 0});
    ret.push_back(vector<int>{0, 0, 1});
    return ret;
}

vector<vector<int>> reflect_y(int num) {
    vector<vector<int>> ret;
    ret.push_back(vector<int>{1, 0, 0});
    ret.push_back(vector<int>{0, -1, 2 * num});
    ret.push_back(vector<int>{0, 0, 1});
    return ret;
}

vector<vector<int>> compute(char code, int op, vector<vector<int>> last) {
    if (code == '1') {
        return mul(clock90, last);
    } else if (code == '2') {
        return mul(counter90, last);
    } else if (code == '3') {
        return mul(reflect_x(op), last);
    } else {
        return mul(reflect_y(op), last);
    }
}

void solve() {
    counter90.push_back(vector<int>{0, -1, 0});
    counter90.push_back(vector<int>{1, 0, 0});
    counter90.push_back(vector<int>{0, 0, 1});

    clock90.push_back(vector<int>{0, 1, 0});
    clock90.push_back(vector<int>{-1, 0, 0});
    clock90.push_back(vector<int>{0, 0, 1});


    int N;
    cin >> N;
    vector<vector<int>> pos;
    long x, y;
    rep(i, N) {
        cin >> x >> y;
        // bug?
        pos.emplace_back(x, y);
    }
    int M;
    cin >> M;
    string op;
    vector<vector<vector<int>>> trans;
    vector<vector<int>> cur;
    cur.push_back(vector<int>{1, 0, 0});
    cur.push_back(vector<int>{0, 1, 0});
    cur.push_back(vector<int>{0, 0, 1});
    rep(i, M) {
        cin >> op;
        char code = op[0];
        if (op.size() == 1) {
            cur = compute(code, 0, cur);
        } else {
            int idx = op.find(' ');
            string remain = op.substr(idx + 1);
            int num = std::stoi(remain);
            cur = compute(code, num, cur);
        }
        trans.push_back(cur);
    }

    int Q;
    cin >> Q;
    int a, b;
    rep(i, Q) {
        cin >> a >> b;
        vector<int> target = vector<int>(pos[b]);
        target.push_back(1);
        vector<vector<int>> temp;
        temp.push_back(target);
        temp = mul(trans[a], temp);
        cout << temp[0][0] << ' ' << temp[0][1] << endl;
    }


    return;
}

int main() {
    bootstrap
    solve();
}
