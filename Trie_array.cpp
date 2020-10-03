#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <array>

#define P pair<int, int>
#define rep(i, n) for (int i = 0; i < (n); i++)

using namespace std;

struct TrieNode {
public:
    static const size_t SIZE {27};
    explicit TrieNode(char x) : val(x) {fill(children.begin(), children.end(), nullptr);};

    // Default copy;
    TrieNode& operator=(const TrieNode&) = default;
    TrieNode(const TrieNode&) = default;

    ~TrieNode() {
        for (auto &node: children) {
            delete node;
        }
    }

    char val = '#'; // [a-z], # is special
    array<TrieNode *, SIZE> children;
};

class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode('#');
    }

    ~Trie() {
        delete root;
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        auto cur = root;
        for (const auto &ch: word) {
            int idx = ch - 'a';
            if (!cur->children[idx]) {
                // add new
                cur->children[idx] = new TrieNode(ch);
                cur = cur->children[idx];
            } else {
                cur = cur->children[idx];
            }
        }
        cur->children[26] = new TrieNode('#');
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        auto cur = root;
        for (const auto &ch: word) {
            int idx = ch - 'a';
            if (!cur->children[idx]) {
                return false;
            }
            cur = cur->children[idx];
        }
        return cur->children[26] != nullptr;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        auto cur = root;
        for (const auto &ch: prefix) {
            int idx = ch - 'a';
            if (!cur->children[idx]) {
                return false;
            }
            cur = cur->children[idx];
        }
        return true;
    }

    TrieNode *root;
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    Trie* t = new Trie();
    t->insert("abc");
    if(t->search("ab")) {
        cout << "found" << endl;
    } else {
        cout << "not found" << endl;
    }
    for(const auto& node: t->root->children) {
        if(node) {
            cout << "val: " << node->val << " ";
        } else {
            cout << node << " ";
        }
    }
    delete t;
    return 0;
}
