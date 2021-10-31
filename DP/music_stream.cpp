#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'countChoices' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER libSize
 *  2. INTEGER betweenRepeats
 *  3. INTEGER numSongs
 */
// libSize������, ��numSongs�׸�, ÿ�������Լ��ļ������ betweenRepeats.
// ���ж����ֲ��ŷ�ʽ? 
// dp[i][j] -> dp[numSongs][libSize]
// have played numSongs, which include libSize unique songs.
// dp[i][j] = 1. ���һ�׷�һ���� dp[i-1][j]*(j-k) 
//            2. ���һ���¸� dp[i-1][j-1]*(libSize-j+1)                               // dp[0][XXX] = 0
#define M 1000000007
vector<long> dp;
int countChoices(int libSize, int betweenRepeats, int numSongs) {
    dp = vector<long>(libSize + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= numSongs; ++i){
        for (int j = libSize; j > 0; --j){
            long tmp1 = dp[j] * max((j - betweenRepeats), 0);
            tmp1 = tmp1 % M;
            long tmp2 = dp[j - 1] * (libSize - j + 1);
            tmp2 = tmp2 % M;
            dp[j] = tmp1 + tmp2;
            dp[j] = dp[j] % M;
        }
        dp[0] = 0;
    }
    return (int)dp[libSize];
}

int main()
