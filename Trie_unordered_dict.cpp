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
    static const size_t SIZE{27};

    explicit TrieNode(char x) : val(x) {
        children = make_shared<unordered_map<char, TrieNode *>>();
    };

    // Default copy;
    TrieNode &operator=(const TrieNode &) = default;

    TrieNode(const TrieNode &) = default;

    char val = '#';// [a-z], # is special
    //array<TrieNode *, SIZE> children;
    shared_ptr<unordered_map<char, TrieNode *>> children;
};

class Trie {
public:
    static const char END;

    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode('#');
    }

    /** Inserts a word into the trie. */
    void insert(string word) {
        // copy
        auto cur = root;
        for (auto ch: word) {
            char c = ch;
            if (!cur->children->count(ch)) {
                // add new
                cur->children->emplace(c, new TrieNode(c)); // implicit ch -> TreeNode*
            }
            cur = cur->children->at(ch);
        }
        cur->children->emplace(move('#'), new TrieNode(END)); // implicit ch -> TreeNode*
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        auto cur = root;
        for (const auto &ch: word) {
            if (!cur->children->count(ch)) {
                return false;
            }
            cur = cur->children->at(ch);
        }
        return cur->children->count(END) > 0;
    }

    // Exact num required
    bool searchWithWildcard(const string &word, int strIdx, int numWild, const TrieNode *node) {
        if (!node or numWild < 0) { return false; }
        // All character match.
        if (strIdx == word.size()) {
            if(numWild == 0) {
                return node->children->count(END) > 0;
            } else {
                return false;
            }
        }
        char cur = word.at(strIdx);
        bool found = false;
        const auto &chd = node->children;
        for (const auto &kv : *chd) {
            if (kv.first != cur) {
                found = searchWithWildcard(word, strIdx + 1, numWild -1 , kv.second);
                if (found) { return found; }
            } else {
                found = searchWithWildcard(word, strIdx + 1, numWild, kv.second);
                if (found) { return found; }
            }
        }
        return found;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        auto cur = root;
        for (const auto &ch: prefix) {
            if (!cur->children->count(ch)) {
                return false;
            }
            cur = cur->children->at(ch);
        }
        return true;
    }

    TrieNode *root;
};

// init const static
const char Trie::END{'#'};

class MagicDictionary {
public:
    /** Initialize your data structure here. */
    MagicDictionary() {
    }

    void buildDict(vector<string> dictionary) {
        for (auto &s: dictionary) {
            trie.insert(s);
        }
    }

    bool search(string searchWord) {
        const auto cur = trie.root;
        return trie.searchWithWildcard(searchWord, 0, 1, cur);
    }

    Trie trie;
};

int main() {
    MagicDictionary *t = new MagicDictionary();
    auto dict = vector<string> {"hello", "wow"};
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