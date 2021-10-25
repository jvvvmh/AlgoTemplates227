string isPossible(int a, int b, int c, int d) {
    if (a == c && b == d){
        return "Yes";
    }
    if (a > c || b > d){
        return "No";
    }
    if (c > d){
        return isPossible(a, b, c - d, d);
    }
    return isPossible(a, b, c, d - c);
}