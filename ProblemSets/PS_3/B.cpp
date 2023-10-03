#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>

using ll = long long;
using namespace std;

const ll N = 2010;
int n, m, k;
ll dp[N][N];

ll recursion(int bricks, int blocksRem){

    if(blocksRem == 1){
        dp[bricks][1] = 1;
        return 1;
    }

    ll res = 0;
    for(int i = 1; bricks - i >= blocksRem-1; i++){
        ll val;
        if(dp[bricks-i][blocksRem-1]) val = dp[bricks-i][blocksRem-1];
        else val = recursion(bricks-i, blocksRem -1);
        res += val;
    }
    dp[bricks][blocksRem] = res;
    return res;
}



int main(){


    cin >> n >> m >> k;
    int currlen = 0;

    int res = recursion(n, k+1);

    res = res * m;

    for(int i = 0; i < k; i ++){
        res = (res* (m-1)) % 998244353;
    }
    cout << res << '\n';

    return 0;
}