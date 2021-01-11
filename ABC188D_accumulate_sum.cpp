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

#define rep(i, n) for (int i = 0; i < (n); i++)

using namespace std;

#define ll long long
#define all(v) v.begin(),v.end()
#define bootstrap ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
static long mod = 20201227;

void solve() {
    map<long, long> start;
    long N, C;
    cin >> N >> C;
    long end_day = 0;
    rep(i, N) {
        long a, b, c;
        cin >> a >> b >> c;
        if (start.count(a)) {
            start[a] += c;
        } else {
            start.emplace(a, c);
        }
        if (start.count(b+1)) {
            start[b+1] -= c;
        } else {
            start.emplace(b+1, -c);
        }
        end_day = max(end_day, b+2);
    }
    start.emplace(end_day+1, 0);
    ll total = 0;
    long cost = 0;
    int last = 0;
    for (auto &s: start) {
        total += (s.first - last) * min(cost, C);
        cost += s.second;
        last = s.first;
    }
    cout << total << endl;
    return;
}

int main() {
    bootstrap
    solve();
}
