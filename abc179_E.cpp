#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <array>

#define rep(i, n) for (ll i = 0; i < (n); i++)

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
    ll n, x, m;
    cin >> n >> x >> m;
    ll total = 0;
    vector<ll> his;
    unordered_map<ll,ll> seen;
    long cycle = 0, cur = 0;
    rep(i, m+1) {
        if(i == n) {
            cout << total << endl;
            return;
        }
        if(seen.count(x)) {
            cycle = i - seen.at(x);
            cur = i;
            break;
        }
        total += x;
        seen.emplace(x, i);
        his.push_back(x);
        x = (x*x) % m;
    }
    ll c_total = 0;
    rep (k, cycle) {
        c_total += his[k + cur - cycle];
    }
    total += (n - cur + 1) / cycle * c_total;
    n = (n - cur) % cycle;
    rep (w, n) {
        total += his[w + cur - cycle];
    }
    //cout << his[cur- cycle +1]<<endl;
    //cout << cycle<< "cycle: total:" << c_total << endl;
    cout << total << endl;
    //cout << total - 492443256176507 << endl;
}

int main() {
    bootstrap
    solve();
}
