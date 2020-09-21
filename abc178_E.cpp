#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <array>

#define rep(i, n) for (int i = 0; i < (n); i++)

using namespace std;

#define ll long long
#define all(v) v.begin(),v.end()
#define bootstrap ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);


void solve() {
    int N;
    cin >> N;
    vector<int> A, B;
    // transform for Mannhatan distance ,so no need for pair-wise comparison.
    rep(i, N) {
        int a,b;
        cin >> a >> b;
        A.push_back(a + b);
        B.push_back(a -b );
    }
    sort(all(A));
    sort(all(B));
    //rep(k, N) {
    //    cout << B[k] << endl;
    //}
    int res = max(A[N - 1] - A[0], B[N - 1] - B[0]);
    cout << res << endl;
}

int main() {
    bootstrap
    solve();
}
