#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <math.h>

#define rep(i, n) for (uint i = 0; i < (n); i++)

using namespace std;

#define ll long long
#define all(v) v.begin(),v.end()
#define bootstrap ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);

using cood = tuple<int, int, int>;

long dis(cood &a, cood &b) {
    return abs(get<0>(a) - get<0>(b)) + abs(get<1>(a) - get<1>(b)) + max(0, get<2>(b) - get<2>(a));
}

template<typename T>
void choose(T &temp, T val) {
    //temp = min(temp, val);
    if (temp > val) {
        temp = val;
    }
}

// bitmap first impl
// https://atcoder.jp/contests/abc180/tasks/abc180_e
void solve() {
    // N <= 17
    int N;
    cin >> N;
    vector<cood> nums;
    int a, b, c;
    rep(i, N) {
        cin >> a >> b >> c;
        nums.emplace_back(a, b, c);
    }
    cood zero = make_tuple(0, 0, 0);

    vector<vector<int>> dd = vector(N, vector(N, 0));
    rep(i, N) rep(j, N) {
            dd.at(i).at(j) = dis(nums[i], nums[j]);
            //cout << dd[i][j] << " ";
        }
    int FULL = (1 << N);
    int LARGE = 1000000000;
    // (state where reaching using minimum route, lastPlaceInTheRoute) => totalDistance;
    vector<vector<int>> states = vector(FULL, vector(N, LARGE));
    // The first step: from origin to i-th point.
    rep(i, N) {
        // what about states[0][0]
        if(i==0) continue;
        states[1 << i][i] = dd[0][i];
    }

    // state == 1, starting at where the last point is reached.
    // DFS should be feasible as well, but using the observation when reaching state, all [0..state-1] is computed,
    // will simplify the loop and visit every state exactly once.
    // The same as DFS, because this is a thorough traverse.
    rep(state, FULL) {
        // cout << "state: " << state << endl;
        rep(lastReach, N) {
            // no overflow
            // state not contain lastReach, invalid
            if (~state >> lastReach & 1) continue;
            rep(nextReach, N) {
                // already contains nextReach, invalid
                if (state >> nextReach & 1) continue;
                // from current state, reaching a newState by expanding nextReach
                // maintaining a min-policy, the minimum route to reach it.
                choose(states[state | 1 << nextReach][nextReach],
                       states.at(state).at(lastReach) + dd[lastReach][nextReach]);
            }
        }
    }
    cout << states[FULL - 1][0] << endl;
}

int main() {
    bootstrap
    solve();
}
