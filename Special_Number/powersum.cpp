#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'countPowerNumbers' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER l
 *  2. INTEGER r
 */

vector <int> power;               // all powers smaller than r
unordered_set<int> sum;           // for i, j in power, i + j
typedef vector<int>::iterator vp;

int countPowerNumbers(int l, int r) {
    power.push_back(0);
    power.push_back(1);

    for (int i = 2; i * i <= r; ++i){
        int x = i * i;
        while (x <= r){
            power.push_back(x);
            x *= i;
        }
    }
    
    for (vp p1 = power.begin(); p1 != power.end(); ++p1){
        for (vp p2 = power.begin(); p2 != power.end(); ++p2){
            sum.insert(*p1 + *p2);
        }
    }
  
    int cnt = 0;
    for (int num = l; num <= r; ++num){
        if (sum.find(num) != sum.end()){
            cnt += 1;
        }
    }
    
    return cnt;
}