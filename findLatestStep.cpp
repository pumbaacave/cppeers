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
    int findLatestStep(vector<int> &arr, int m) {
        // from_lefts: left -> right
        // till_rights: right-> left
        unordered_map<int, int> from_lefts, till_rights;
        vector<int>counter (arr.size()+1,0);
        int step = -1, cnt = 0;
        int l, r;
        for (const int &idx : arr) {
            cnt++;
            l = r = idx;
            if (till_rights.count(idx - 1)) {
                l = till_rights[idx - 1];
                till_rights.erase(idx - 1);
                counter.at(idx - l) -= 1;
                from_lefts.erase(l);
            }
            if (from_lefts.count(idx + 1)) {
                r = from_lefts[idx + 1];
                from_lefts.erase(idx + 1);
                counter.at(r - idx) -= 1;
                till_rights.erase(r);
            }
            int delta = r - l + 1;
            counter.at(delta) += 1;
            if (counter[m] > 0) {
                step = cnt;
            }
            from_lefts.emplace(l, r);
            till_rights.emplace(r, l);
        }

        return step;
    }
};

int main() {
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