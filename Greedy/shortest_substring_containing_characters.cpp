/*
given a string of [a-z], 
find the len of shortest substring that contains at least set(string characters).
given: dabbcabcd
return: 4

记录: best node (不同character的个数, substring的长度).
向右扩展, 左边收缩.

*/

#include <bits/stdc++.h>

using namespace std;


/*
 * Complete the 'shortestSubstring' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING givenString as parameter.
 */
class node{
    public:
    int len;
    int contain;
    node(int len_, int contain_){
        len = len_;
        contain = contain_;
    }
    bool operator < (const node & b) const{
        if (contain != b.contain){
            return contain < b.contain;
        }
        return (len > b.len);
    }
 };
 
unordered_map<char, int> mp;
int shortestSubstring(string givenString){
// a b c | c c | a
    int st = 0, ed = 1;
    mp[givenString[0]] = 1;
    int value = 1;
    // v.push_back(value);
    node best = node(ed - st, value);
    for (int i = 1; i < givenString.length(); ++i){
        char tmp = givenString[i];
        if (mp.find(tmp) == mp.end()){
            // add in new
            mp[tmp] = 1;
            ++ed;
            value += 1;
            // v.push_back(value);
            best = max(best, node(ed - st, value));
        }else{
            // add old
            // cout << "add old" <<endl;
            mp[tmp] += 1;
            ++ed;
            for (int k = st; k < ed ; ++k){
                // if delete [k]
                char to_del = givenString[k];
                if (mp[to_del] >= 2){
                    st = st + 1;
                    mp[to_del] -= 1;
                }else{
                    break;
                }
            }
            best = max(best, node(ed - st, value));
        }
    }
    for (int k = ed - 1; k >= st; --k){
        char to_del = givenString[k];
        // cout << "to del " << to_del <<endl;
        // cout << "ed = "<<ed<<endl;
        if (mp[to_del] >= 2){
            ed = ed - 1;
            mp[to_del] -= 1;
        }else{
            break;
        }
    }
    return best.len;
}
int main()