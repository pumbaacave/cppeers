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

  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto tail = head;
        while(n-- >0) {
            tail = tail->next;
        }
        ListNode* last = new ListNode(0, head);
        auto cur = head;
        while(tail) {
            tail =tail->next;
            last =cur ;
            cur = cur-> next;
        }
        if(last->next == head) {
            head = head->next;
        } else {
            last->next = last->next->next;
        }
        return head;
    }

    ListNode* removeNthFromEnd_recur(ListNode* head, int n) {
        int idx = checkAndDelete(head, n);
        if(idx == n + 1)  {
            head = head->next;
        }
        return head;
    }
private:
    int checkAndDelete(ListNode* node, int target) {
        if(!node) {
            return 0;
        }
        int idx = checkAndDelete(node->next, target) + 1;
        cout << idx <<" --" << node->val << endl;
        if(idx == target + 1) {
            node->next = node->next->next;
        }
        return idx;
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