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
    int N;
    map<long, long> players;
    cin >> N;
    N = 1 << N;
    long score;
    rep(i, N) {
        cin >> score;
        players.emplace(i + 1, score);
    }
    while (players.size() != 2) {
        map<long, long> next_players;
        bool match = false;
        pair<long, long> last;
        for (auto entry: players) {
            if (!match) {
                last = entry;
            } else {
                if (last.second > entry.second) {
                    next_players.emplace(last);
                } else {
                    next_players.emplace(entry);
                }
            }
            match = !match;
        }
        players = next_players;
        next_players.clear();
    }
    auto v = vector<pair<long, long>>{players.begin(), players.end()};
    if(v[0].second > v[1].second) {
        cout << v[1].first<<endl;
    } else {
        cout << v[0].first<<endl;
    }
    return;
}

int main() {
    bootstrap
    solve();
}
