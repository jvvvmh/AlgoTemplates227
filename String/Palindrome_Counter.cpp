#include <bits/stdc++.h>

using namespace std;

#define MAXN 5000

char c[(MAXN << 1) + 10]; // new string
int p[(MAXN << 1) + 10];  // radius of position i of new string

int Init(string& s){
    int n = s.length();
    c[0] = '^';
    c[1] = '#';
    int j = 2;
    for (int i = 0; i < n; ++i){
        c[j++] = s[i];
        c[j++] = '#';
    }
    c[j++] = '$';
    return j;
}

int countPalindromes(string s) {
    int N = Init(s); // len of new string
    int cnt = 0;
    int center = 0;
    int R = 0;
    p[0] = 0;
    for (int i = 1; i < N - 1; ++i){
        int r = 0;
        if (i < R){
            r = min(p[(center << 1) - i], R - i);
        }
        while (c[i + r + 1] == c[i - r - 1]){
            ++r;
        }
        p[i] = r;
        // update Right & center
        if (i + r > R){
            R = i + r;
            center = i;
        }
    }
    int ischar = 0;
    for (int i = 1; i < N - 1; ++i){
        cnt += ((p[i] + ischar) >> 1);
        ischar = 1 - ischar;
    }

    return cnt;
}