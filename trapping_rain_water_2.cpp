#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& grid) {
        // Fast I/O Optimization
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int m = grid.size(), n = grid[0].size();
        if (m < 3 || n < 3) return 0; // 3x3'ten küçük matrislerde su birikemez

        // Memory-aligned visited grid (vector<char> for cache efficiency)
        vector<vector<char>> visited(m, vector<char>(n, 0));
        using Cell = tuple<int, int, int>;
        priority_queue<Cell, vector<Cell>, greater<Cell>> pq;

        auto addBoundary = [&](int r, int c) {
            pq.emplace(grid[r][c], r, c);
            visited[r][c] = 1;
        };

        // Row boundaries
        for (int r = 0; r < m; ++r) {
            addBoundary(r, 0);
            addBoundary(r, n - 1);
        }
        // Column boundaries (excluding corners)
        for (int c = 1; c < n - 1; ++c) {
            addBoundary(0, c);
            addBoundary(m - 1, c);
        }

        int totalWater = 0, maxHeight = 0;
        const int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!pq.empty()) {
            auto [h, r, c] = pq.top(); 
            pq.pop();
            
            if (h > maxHeight) maxHeight = h;

            for (const auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                    visited[nr][nc] = 1;
                    int nh = grid[nr][nc];
                    
                    // Branchless addition using inline condition
                    totalWater += (nh < maxHeight ? maxHeight - nh : 0);
                    pq.emplace(nh, nr, nc);
                }
            }
        }
        return totalWater;
    }
};
