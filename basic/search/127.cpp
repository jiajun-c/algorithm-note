#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

class Solution {
    public:
        using dtype = pair<string, int>;
        int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
            set<string> wordSet(wordList.begin(), wordList.end());
            queue<dtype> q;
            q.push(dtype(beginWord, 1));
            int ans = 0;
            while (!q.empty()) {
                dtype cur = q.front();
                q.pop(); 
                string word = cur.first;
                if (word == endWord) return cur.second;
                for (int i = 0; i < cur.first.size(); i++) {
                    char tmp = word[i];
                    for (char c = 'a'; c <= 'z'; c++) {
                        word[i] = c;
                        if (wordSet.count(word)) {
                            q.push(dtype(word, cur.second + 1));
                            wordSet.erase(word);
                        }
                    }
                    word[i] = tmp;
                }
            }

            return ans;
        }
    };