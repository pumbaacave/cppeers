#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ret = vector(num, 0);
        if (num >= 1) {
            ret[1] = 1;
        }
        int i = 2, j;
        while ((i >> 1) < num) {
            for (int k = 0; k < i && k + i < num; ++k) {
                ret[k + i] = 1 + ret[k];
            }
            i <<= 1;
        }
        return ret;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
