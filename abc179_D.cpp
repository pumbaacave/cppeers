#include <iostream>
#include <vector> #include <string>
#include <algorithm> #include <numeric> #include <functional>
#include <unordered_map>
#include <unordered_set>
#include <array>

#define rep(i, n) for (auto i = 0; i < (n); i++)

using namespace std;

#define ll long long
#define all(v) v.begin(),v.end()
#define bootstrap ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

// custom hash can be a standalone function object:
struct MyHash {
    std::size_t operator()(pair<long, long> const &p) const noexcept {
        std::size_t h1 = std::hash<long>{}(p.first);
        std::size_t h2 = std::hash<long>{}(p.second);
        return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
    }
};

struct MyComp {
    template<typename T>
    std::size_t operator()(T &l, T &r) const noexcept {
        return l < r;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> l(k), r(k);
    rep(i, k) { cin >> l[i] >> r[i]; }
    vector<ll> dp(n + 1), dpsum(n + 1);
    dp[1] = 1;
    dpsum[1] = 1;
    long CON = 998244353;
    for (int i = 2; i <= n; i++) {
        rep(j, k) {
            int idx_r = i - l[j];
            int idx_l = i - r[j];
            if (idx_r < 1) {
                continue;
            }
            idx_l = max(1, idx_l);
            dp[i] += (dpsum[idx_r] - dpsum[idx_l - 1]);
            dp[i] %= CON;
        }
        dpsum[i] = (dpsum[i - 1] + dp[i]) % CON;
    }
    //rep(i, n) {
    //    cout << dp[i] << " ";
    //}
    //cout << endl;
    //rep(i, n) {
    //    cout << dpsum[i] << " ";
    //}
    //cout << endl;
    cout << (dp[n] >= 0? dp[n]:dp[n] + CON)<< endl;
}

int main() {
    bootstrap
    solve();
}
