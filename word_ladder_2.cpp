#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

// High-Performance C++ Solution for Word Ladder II
// Strategy: Level-by-Level BFS for Shortest DAG + Backtracking DFS for Path Reconstruction
class Solution {
    unordered_map<string, int> dist;
    vector<vector<string>> ans;
    string bWord;

    void dfs(const string& word, vector<string>& seq) {
        if (word == bWord) {
            vector<string> path = seq;
            reverse(path.begin(), path.end());
            ans.push_back(path);
            return;
        }

        int steps = dist[word];
        int sz = word.size();
        string temp = word;

        for (int i = 0; i < sz; ++i) {
            char original = temp[i];
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                temp[i] = ch;
                if (dist.count(temp) && dist[temp] + 1 == steps) {
                    seq.push_back(temp);
                    dfs(temp, seq);
                    seq.pop_back();
                }
            }
            temp[i] = original;
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        // Fast I/O
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        unordered_set<string> st(wordList.begin(), wordList.end());
        if (!st.count(endWord)) return {};

        bWord = beginWord;
        queue<string> q;
        q.push(beginWord);
        dist[beginWord] = 0;
        st.erase(beginWord);

        int sz = beginWord.size();
        bool found = false;

        // Step 1: BFS to find shortest path distance to all nodes (DAG construction)
        while (!q.empty()) {
            string word = q.front();
            q.pop();
            int steps = dist[word];

            if (word == endWord) {
                found = true;
                break;
            }

            string temp = word;
            for (int i = 0; i < sz; ++i) {
                char original = temp[i];
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    temp[i] = ch;
                    if (st.count(temp)) {
                        dist[temp] = steps + 1;
                        q.push(temp);
                        st.erase(temp); // Visited in BFS
                    }
                }
                temp[i] = original;
            }
        }

        // Step 2: Backtrack from endWord to beginWord using DFS
        if (found) {
            vector<string> seq = {endWord};
            dfs(endWord, seq);
        }

        return ans;
    }
};
