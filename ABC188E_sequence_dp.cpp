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

void solve() {
    long N, M;
    cin >> N >> M;
    vector<long> val;
    vector<unordered_set<long>> visit;
    rep(i, N) {
        long num;
        cin >> num;
        val.push_back(num);
        auto v = unordered_set<long>();
        visit.push_back(v);
    }
    rep(i, M) {
        long l, r;
        cin >> l >> r;
        visit[l - 1].emplace(r - 1);
    }
    // lowest price possible before reaching city i.
    vector<long> dp(N, LONG_MAX);
    // dp[0] = 0;

    rep(l, N) {
        for (auto v: visit[l]) {
            // new min price from pre-cur cities
            dp[v] = min(dp[v], dp[l]);
            // new min price from cur city
            dp[v] = min(dp[v], val[l]);
        }
    }
    long ret = LONG_MIN;
    rep (i, N) {
        //cout << dp[i] << endl;
        if (dp[i] == LONG_MAX) continue;
        ret = max(ret, val[i] - dp[i]);
    }
    cout << ret << endl;
    return;
}

int main() {
    bootstrap
    solve();
}
