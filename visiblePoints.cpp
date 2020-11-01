#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <math.h>

using namespace std;
using P = pair<int, int>;
#define rep(i, n) for (int i = 0; i < (n); i++)

class Solution {
public:
    int visiblePoints(vector<vector<int>> &points, int angle, vector<int> &location) {
        // turn to polar form
        int same_cnt = 0;
        vector<double> degrees;
        for (auto &p: points) {
            if (p == location) {
                same_cnt++;
                continue;
            }
            degrees.push_back(getDeg(location, p));
        }
        // window
        sort(degrees.begin(), degrees.end());
        int mmax = 0, temp = 0;
        int l = 0;
        int n = degrees.size();
        rep(i, n) {
            degrees.push_back(degrees[i] + 360);
        }
        rep(i, degrees.size()) {
            while (degrees[i] - degrees[l] > angle) {
                l++;
            }
            temp = i - l + 1;
            mmax = max(mmax, temp);
        }
        for (auto &num:degrees) {
            cout << num << " ";
        }
        return mmax + same_cnt;
    }

private:
    double getDeg(vector<int> &loc, vector<int> &tar) {
        if (tar[0] == loc[0]) {
            if (tar[1] > loc[1]) {
                return 90;
            } else {
                return 270;
            }
        }

        double a = atan((double) (tar[1] - loc[1]) / (double) (tar[0] - loc[0]));
        double d = a / M_PI * 180;
        if (tar[0] < loc[0]) {
            d += 180;
        }
        return d;
    }
};

using namespace std;

//int main() {
//    Solution s;
//    vector<vector<int>> g{vector<int>{0}};
//    cout << s.minPathSum(g);
//    return 0;
//}