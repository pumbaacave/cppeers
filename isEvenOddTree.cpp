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


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool is_odd(int num) {
        return (bool) ((num & 1) == 1);
    }

    bool isEvenOddTree(TreeNode *root) {
        // BFS
        TreeNode *MARK = nullptr;
        if (!root) return false;
        deque<TreeNode *> deq;
        deq.push_back(root);
        deq.push_back(MARK);
        int last = 0, LOW = 0, HIGH = 1000001;
        bool oddTurn = false;
        while (!deq.empty()) {
            auto cur = deq.front();
            deq.pop_front();
            //if(cur) {
            //    cout << cur->val << ": " << oddTurn  << ": " << last  << endl;
            //}
            if (cur == MARK) {
                if (deq.empty()) {
                    // all element valid
                } else {
                    deq.push_back(MARK);
                    oddTurn = !oddTurn;
                    if (!oddTurn) {
                        last = LOW;
                    } else {
                        last = HIGH;
                    }
                }
                continue;
            }
            // normal pass
            // even layer
            if (!oddTurn) {
                if (!is_odd(cur->val)) {
                    return false;
                }
                if (cur->val <= last) {
                    return false;
                } else {
                    last = cur->val;
                }
                if (cur->left) {
                    deq.push_back(cur->left);
                }
                if (cur->right) {
                    deq.push_back(cur->right);
                }
            } else {
                // odd layer
                if (is_odd(cur->val)) {
                    return false;
                }
                if (cur->val >= last) {
                    return false;
                } else {
                    last = cur->val;
                }
                if (cur->left) {
                    deq.push_back(cur->left);
                }
                if (cur->right) {
                    deq.push_back(cur->right);
                }
            }
        }
        return true;
    }
};
//int main() {
//    Solution s;
//    vector<vector<int>> g{vector<int>{0}};
//    cout << s.minPathSum(g);
//    return 0;
//}