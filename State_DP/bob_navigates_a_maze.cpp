#include <bits/stdc++.h>
// 从起点出发，要经过每一个coin, 达到终点, 求最短路径
// BFS+状压dp 
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


/*
 * Complete the 'minMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY maze
 *  2. INTEGER x
 *  3. INTEGER y
 */

// vector<vector<int>> a(10, vector<int>(10, 0));
int N = 0;
int C = 0; // coin的个数
vector<pair<int, int>> coins;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int d[15][105][105];
int m, n;

vector<vector<int>> dfs(vector<int> left, vector<int> right){
    if (right.size() == 0){
        return vector<vector<int>>(1, left);
    }
    vector<vector<int>> ans;
    for (int i = 0; i < right.size(); ++i){
        vector<int> new_left(left);
        new_left.push_back(right[i]);
        vector<int> new_right;
        for (int j = 0; j < right.size(); ++j){
            if (j != i){
                new_right.push_back(right[j]);
            }
        }
        vector<vector<int>> sub_ans = dfs(new_left, new_right);
        for (auto i: sub_ans){
            ans.push_back(i);
        }
    }
    return ans;
}

bool visited[105][105];

void BFS(int id, vector<vector<int>> &maze){
    int x = coins[id].first; // 金币的位置
    int y = coins[id].second;
    memset(visited, 0, sizeof(visited));
    queue<pair<pair<int, int>, int>> q; // x, y, depth
    q.push(make_pair(make_pair(x, y), 0));
    while(!q.empty()){
        // cout << q.size()<<endl;;
        auto head = q.front();
        q.pop();
        int old_x = head.first.first;
        int old_y = head.first.second;
        // cout<<old_x<<"; "<<old_y<<endl;
        if (visited[old_x][old_y]) continue;
        int tmp_d = head.second;
        d[id][old_x][old_y] = tmp_d;
        visited[old_x][old_y] = true;
        for (int k = 0; k < 4; ++k){
            int new_x = old_x + dx[k];
            int new_y = old_y + dy[k];
            if (new_x < 0 || new_x >= m) continue;
            if (new_y < 0 || new_y >= n) continue;
            if (maze[new_x][new_y] == 1) continue;
            if (visited[new_x][new_y]) continue;
            q.push(make_pair(make_pair(new_x, new_y), tmp_d + 1));
        }   
    }
    return;
}
int minMoves(vector<vector<int>> maze, int x, int y) {
    m = maze.size();
    n = maze[0].size();
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            int v = maze[i][j];
            if (v != 1){
                ++N;
                if (v == 2){
                    coins.push_back(make_pair(i, j));
                    ++C;
                }
                ++N;
            }
        }
    }

    memset(d, -1, sizeof(d));
    for (int i = 0; i < C; ++i){
        BFS(i, maze);
    }
    
    // 判断是否不连通:
    for (int i = 0; i < C; ++i){
        if (d[i][0][0] == -1 || d[i][x][y] == -1){
            return -1;
        }
    }
    // C个数字的全排列
    // i love huihui
    
    int dp[15][1024];  // currently at i, visited st, minimum distance dp[i][st]
    memset(dp, 0x3f, sizeof(dp));  // 0x3f3f3f3f + 0x3f3f3f3f > 0
    for (int i = 0; i < C; ++i) {
        dp[i][1 << i] = d[i][0][0];
    }
    for (int st = 0; st < (1 << C); ++st) {
        for (int i = 0; i < C; ++i) {
            if ((st >> i) & 1) {  // i in st
                for (int j = 0; j < C; ++j) {
                    if (!((st >> j) & 1)) {  // j not in st
                        dp[j][st | (1 << j)] = min(dp[j][st | (1 << j)], dp[i][st] + d[i][coins[j].first][coins[j].second]);
                    }
                }
            }
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < C; ++i) {
        ans = min(ans, dp[i][(1 << C) - 1] + d[i][x][y]);
    }
    return ans;
}
int main()
