#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'getMinimumUniqueSum' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */


// 1 2 2 3 7 ->
// 1 2 3 4 7
int getMinimumUniqueSum(vector<int> arr){
    sort(arr.begin(), arr.end());
    int s = 0;
    int cmin = -1;
    for (auto i: arr){
        i = max(i , cmin + 1);
        cmin = i;
        s += i;
    }
    return s;
}

int main()
