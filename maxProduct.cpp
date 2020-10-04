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


#define P pair<int, int>
#define rep(i, n) for (int i = 0; i < (n); i++)

using namespace std;

class Solution {
public:
    int maxProduct(vector<int> &nums) {
        // state: last possible positive && minus value
        if (nums.size() == 1) { return nums[0]; }
        int res = nums[0];
        //vector<vector<int>> dp = vector<vector<int>>(2);
        int p, n;
        p = max(nums[0], 0);
        n = min(nums[0], 0);
        for (int i = 1; i < nums.size(); i++) {
            auto num = nums[i];
            p  *= num;
            n  *= num;
            // only 0 equals
            if(p < n) {
                swap(p, n);
            }
            p = max(p, num);
            n = min(n, num);
            res = max(res, p);
        }
        return res;
    }
};

int main() {
    MagicDictionary *t = new MagicDictionary();
    auto dict = vector<string>{"hello", "wow"};
    t->buildDict(dict);
    assert(t->trie.search("hello"));
    assert(t->trie.search("hello"));
    assert(!t->search("hello"));
    assert(t->search("hhllo"));
    //for (const auto &node: *t->root->children) {
    //    cout << "val: " << node.second << " ";
    //}
    delete t;
    return 0;
}