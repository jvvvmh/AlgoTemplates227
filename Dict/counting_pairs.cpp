# a + k = b 求不同pair的个数
 
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'countPairs' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY numbers
 *  2. INTEGER k
 */
unordered_map<int, int> d;
int countPairs(vector<int> numbers, int k) {
    for (auto x: numbers){
        if (d.find(x) == d.end()){
            d[x] = 1;
        }else{
            d[x] += 1;
        }
    }
    int res = 0;
    for (auto &pair: d){
        int x = pair.first;
        int cnt = pair.second;
        if (k == 0){
            if (cnt >= 2){
                ++res;
            }
        }else{
            if (d.find(x + k) != d.end()){
                ++res;
            }
        }
    }
    return res;
}

int main()
