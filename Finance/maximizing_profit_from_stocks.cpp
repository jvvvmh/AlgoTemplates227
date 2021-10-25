// given stock price, decide buy 1 share/sell any you have

long maximumProfit(vector<int> price) {
    long res = 0, max_ = -1;
    for (auto it = price.rbegin(); it != price.rend(); ++it){
        long p = *it;
        if (p < max_){
            res += max_ - p;
        }else{
            max_ = p;
        }
    }
    return res;
}