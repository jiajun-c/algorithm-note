#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
struct Node {
    Node *child[2];
    bool containskey(int bit) {
        return child[bit] != nullptr;
    }

    Node *get(int bit) {
        return child[bit];
    }
    
    void put(int bit, Node *node) {
        child[bit] = node;
    }
};

class Trie {
    public:
        Node *root;
        Trie() {
            root = new Node();
        }

        void insert(int num) {
            Node *node = root;
            for (int i = 31; i >= 0; i--) {
                int bit = (num >> i) & 1;
                if (!node->containskey(bit)) {
                    node->put(bit, new Node());
                }
                node = node->get(bit);
            }
        }

        int getMax(int num) {
            Node *node = root;
            int maxXor = 0;
            for (int i = 31; i >= 0; i--) { 
                int bit = (num >> i) & 1;
                if (node->containskey(1 - bit)) {
                    maxXor = maxXor | (1 << i);
                    node = node->get(1 - bit);
                } else {
                    node = node->get(bit);
                }
            }
            return maxXor;  
        }
};

class Solution {
    public:
        int findMaximumXOR(vector<int>& nums) {
            Trie trie;
            for (auto num: nums) {
                trie.insert(num);
            }
            int maxXor = 0;
            for (auto num: nums) {
                maxXor = max(maxXor, trie.getMax(num));
            }
            return maxXor;
        }
    };

int main() {
    
}