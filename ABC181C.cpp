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

#define rep(i, n) for (int i = 0; i < (n); i++)

using namespace std;

#define ll long long
#define all(v) v.begin(),v.end()
#define bootstrap ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);


bool colinear(int &x1, int &y1, int &x2, int &y2, int &x3, int &y3) {
    if (x1 == x2 and x2 == x3) {
        return true;
    }

    if (x1 == x2 or x2 == x3) {
        return false;
    }
    // Case strips have gradiant.
    return (((x2 - x1) * (y3 - y1)) == ((x3 - x1) * (y2 - y1)));
}

void solve() {
    int N;
    cin >> N;
    vector<int> x(N), y(N);
    rep(q, N) {
        cin >> x[q] >> y[q];
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                if (colinear(x[i], y[i], x[j], y[j], x[k], y[k])) {
                    cout << "Yes" << endl;
                    goto stop;
                }
            }
        }
    }
    cout << "No" << endl;
    stop:
    return;
}

int main() {
    bootstrap
    solve();
}
