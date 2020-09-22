#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <climits>
#include <unordered_map>

#define P pair<int, int>
#define rep(i, n) for (int i = 0; i < (n); i++)

using namespace std;

class Solution {
public:
    int findUnsortedSubarray(vector<int> &nums) {
        deque<P > stack;
        // lite monotonic stack
        int l = nums.size(), r{0};
        int M{INT_MIN};
        rep(i, nums.size()) {
            // restriction not break
            if (nums[i] >= M) {
                // keep single point for same values
                if(nums[i] == M) {
                    continue;
                }
                M = nums[i];
                stack.emplace_back(i, nums[i]);
                continue;
            }
            // Find left side
            while (!stack.empty() and nums[i] < stack.back().second) {
                l = min(l, stack.back().first);
                stack.pop_back();
            }
            // Update right side
            r = max(r, i);
        }
        int res = r - l + 1;
        cout << l << r << endl;
        return res < 0 ? 0 : res;
    }
};

//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}
