# 3xn的格子, 三种颜色涂, 每行每列不能只有一种颜色, 问有多少种涂法?
# (1) valid row: ABC, AAB 共 24种, 不考虑col => n ^ 24
# (2) 除去清一色的col的情况: 有1 2 3列, 求1或2或3有清一色列的种数: 1U2U3=1+2+3- 1U2 - ...
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'countPatterns' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER n as parameter.
 */
 
// #define MOD(x) ((long long)x % (long long)(pow(10, 9) + 7))
// int (*a) [3];
// int (*r_cnt) [3];
// int (*c_cnt) [3];

// bool check(int r, int c, int n, int k){
//     // check col
//     if (r == n - 1){
//         for (int j = 0; j <= c; ++j){
//             int c = 0;
//             for (auto nn: c_cnt[j]){
//                 c += (nn == 0? 0 : 1);
//             }
//             if (c <= 1) return false;
//         }
//     }
//     // check row
//     int r_max = (c == 2? r : r - 1);
//     if (r_max < 0) return true;
//     for (int i = 0; i <= r_max; ++i){
//         int c = 0;
//         for (auto nn: r_cnt[i]){
//             c += (nn == 0? 0 : 1);
//         }
//         if (c <= 1) return false;
//     }
//     return true;
// }


// int dfs(int r, int c, int n){
//     int res = 0;
//     for (int k = 0; k < 3; ++k){
//         // a[r][c] = k; // put k in pos=(r,c)
//         r_cnt[r][k] += 1;
//         c_cnt[c][k] += 1;
//         bool is_valid = check(r, c, n, k);
//         if (is_valid){
//             if (r == n - 1 && c == 2){
//                 res += 1;
//             }else{
//                 int next_r = r;
//                 int next_c = c;
//                 if (c == 2){
//                     next_r += 1;
//                     next_c = 0;
//                 }else{
//                     next_c += 1;
//                 }
//                 res += dfs(next_r, next_c, n);
//                 res = MOD(res);
//             }
//         }
//         r_cnt[r][k] -= 1;
//         c_cnt[c][k] -= 1;
//     }
//     return res;
// }

long f(long x, long n, long M){
    long res = 1;
    for (int i = 0; i < n; ++i){
        res *= x;
        res = res % M;
    }
    return res;
}
int countPatterns(int n) {
    // a = (int (*) [3])calloc(n * 3, sizeof(int));
    // r_cnt = (int (*) [3])calloc(n * 3, sizeof(int));
    // c_cnt = (int (*) [3])calloc(3 * 3, sizeof(int));
    long M = (long)(pow(10, 9) + 7);
    long res = f(24, n, M) - (9 * f(8, n, M) % M);
    // cout << res;
    res += 9 * f(2, n, M);
    res = res % M;
    res += 18 * f(3, n, M);
    res = res % M;
    res -= 24;
    res = res % M;
    return res;
}
int main()