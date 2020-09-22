#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <unordered_set>

#define P pair<int, int>
#define rep(i, n) for (int i = 0; i < (n); i++)

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        // key is val
        // DFS with stack
        TreeNode *ans = nullptr;
        unordered_set<int> targets{p->val, q->val};
        dfs(root, targets, ans);
        return ans;
    }

    // return: found count
    // ref to a pointer, copy will fail
    int dfs(TreeNode *cur, unordered_set<int> &targets, TreeNode *&found) {
        cout << cur->val << endl;
        if (!cur) {
            return 0;
        }
        auto l = dfs(cur->left, targets, found);
        if (l == 2) {
            return l;
        }
        auto r = dfs(cur->right, targets, found);
        if (r == 2) {
            return r;
        }
        int total = 0;
        if (targets.count(cur->val)) {
            total++;
        }
        total = total + r + l;
        if (total == 2) {
            found = cur;
            cout << cur->val;
        }
        return total;
    }
};
//int main() {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}
