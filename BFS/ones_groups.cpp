/*
grid[i][j] can be 0 or 1.
return number of connected 1s (up, down, left, right).
BFS for each i, j.
*/


#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


/*
 * Complete the 'onesGroups' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY grid
 *  2. INTEGER_ARRAY queries
 */
struct node{
    int x;
    int y;
    node(int x_, int y_){
        x = x_;
        y = y_;
    }
};

int m, n;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
vector<vector<bool>> visited;
unordered_map<int, int> mp; // cnt -> N

void bfs(int i, int j, vector<vector<int>> & grid){
    //cout <<"ij"<<i <<" "<<i<<endl;
    int total = 0;
    queue <node> q;
    q.push(node(i, j));
    while (!q.empty()){
        node tmp = q.front();
        q.pop();
        i = tmp.x;
        j = tmp.y;
        if (visited[i][j]){
            continue;
        }
        visited[i][j] = true;
        total += 1;
        for (int k = 0 ; k < 4; ++k){
            int i_new = i + dx[k];
            int j_new = j + dy[k];
            // cout << i_new <<" "<<j_new<<endl;
            
            if (0 <= i_new && i_new < m && 0 <= j_new && j_new < n){
                //cout <<"here"<<i_new <<" "<<j_new<<endl;
                if (!visited[i_new][j_new] && grid[i_new][j_new]){
                //cout <<"go" << i_new <<" "<<j_new<<endl;
                q.push(node(i_new, j_new));
                }
            }
        }
    }
    //cout << i << " " << j << " total="<<total<<endl;
    if (mp.find(total) != mp.end()){
        mp[total] += 1;
    }else{
        mp[total] = 1;
    }
}
vector<int> onesGroups(vector<vector<int>> grid, vector<int> queries){
    m = grid.size();
    n = grid[0].size();

    visited = vector<vector<bool>>(m, vector<bool>(n, 0));

    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            if (grid[i][j] && !visited[i][j]){
                bfs(i, j, grid);
            }
        }
    }
    for (auto i = mp.begin(); i != mp.end();++i){
        cout << i->first <<" "<<i->second<<endl;
    }
    vector<int> res;
    for (auto i: queries){
        res.push_back(mp[i]);
    }
    return res;
}
int main()