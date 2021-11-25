/*
colors to fill a picture.
picture is of a,b,c,d...
same char & in same bucket (up down left right) => same color
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'strokesRequired' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING_ARRAY picture as parameter.
 */

int m, n;
int colors = 0;
vector<vector<bool>> visited;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};

struct Node{
    int x;
    int y;
    Node(int x_, int y_){
        x = x_;
        y = y_;
    }
};

bool check(int x, int y, char c_, vector<string>& picture){
    if (x < 0 || x >= m || y < 0 || y >= n){
        return false;
    }
    if (visited[x][y]){
        return false;
    }
    return (picture[x][y] == c_);
}

void bfs(int x, int y, char c_, vector<string>& picture){
    // cout << "bfs "<<x <<" "<<y <<"          c_ ="<<c_<<endl;
    queue<Node> q;
    q.push(Node(x, y));
    while (!q.empty()){
        Node node = q.front();
        q.pop();
        if (visited[node.x][node.y]){
            continue;
        }
        visited[node.x][node.y] = true;
        for (int k = 0 ; k < 4; ++k){
            int new_x = node.x + dx[k];
            int new_y = node.y + dy[k];
            if (check(new_x, new_y, c_, picture)){
                q.push(Node(new_x, new_y));
            }
        }
    }
}

int strokesRequired(vector<string> picture){
    m = picture.size();
    n = picture[0].length();
    visited = vector<vector<bool>>(m, vector<bool>(n, 0));
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            if (!visited[i][j]){
                colors += 1;
                bfs(i, j, picture[i][j], picture);
            }
        }
    }
    return colors;
}

int main()