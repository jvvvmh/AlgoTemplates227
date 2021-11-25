/*
lengths[1,1,3,4]            (4 rods) 
cut away the shortest
-> [2,3]                    (2 rods)
cut away 2
[1]                         (1 rod)

return {4, 3, 1}.

Solution:
sorted dictionary of {len, cnt}
print from right, sum of cnt.
*/ 

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'rodOffcut' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY lengths as parameter.
 */

map<int, int> mp; // len, cnt
vector<int> res;
vector<int> rodOffcut(vector<int> lengths){
    for (auto i: lengths){
        mp[i] += 1;
    }
    int s = 0;
    for (auto i = mp.rbegin(); i != mp.rend(); ++i){
        int cnt = i -> second;
        s += cnt;
        res.push_back(s);
    }
    reverse(res.begin(), res.end());
    return res;
}

int main()
