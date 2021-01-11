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
    int H, W;
    cin >> H >> W;
    vector<string> board = vector<string>(H);
    rep(i, H) {
        cin >> board[i];
    }
    ll MOD = 1000000000 + 7;
    vector<vector<ll>> dp = vector<vector<ll>>(H, vector<ll>(W, 0));
    vector<vector<ll>> x = vector<vector<ll>>(H, vector<ll>(W, 0));
    vector<vector<ll>> y = vector<vector<ll>>(H, vector<ll>(W, 0));
    vector<vector<ll>> z = vector<vector<ll>>(H, vector<ll>(W, 0));
    dp[0][0] = 1;
    x[0][0] = 0;
    //y[0][0] = 1;
    //z[0][0] = 1;
    rep(i, H) rep(j, W) {
            if (board[i][j] == '#') continue;
            if (i == 0 and j == 0) continue;
            // for Y
            if (i > 0 and board[i - 1][j] == '.') {
                x[i][j] = x[i - 1][j] + dp[i - 1][j];
                x[i][j] %= MOD;
            }
            // for X
            if (j > 0 and board[i][j - 1] == '.') {
                y[i][j] = y[i][j - 1] + dp[i][j - 1];
                y[i][j] %= MOD;
            }
            // for Z
            if (j > 0 and i > 0 and board[i - 1][j - 1] == '.') {
                z[i][j] = z[i - 1][j - 1] + dp[i - 1][j - 1];
                z[i][j] %= MOD;
            }
            dp[i][j] = x[i][j] + y[i][j] + z[i][j];
            dp[i][j] %= MOD;
        }
    cout << dp[H - 1][W - 1];
    return;
}

int main() {
    bootstrap
    solve();
}
