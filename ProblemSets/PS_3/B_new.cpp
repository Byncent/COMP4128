#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>

typedef long long ll;
using namespace std;

const ll N = 2010;
ll n, m, k;
ll dp[N][N];

ll recursion(ll bricks, ll blocksRem, ll colors){

    if(blocksRem == 1){
        dp[bricks][1] = 1;
        return 1;
    }

    ll res = 0;
    for(ll i = 1; bricks - i >= blocksRem-1; i++){
        ll val;
        if(dp[bricks-i][blocksRem-1]) val = dp[bricks-i][blocksRem-1];
        else val = recursion(bricks-i, blocksRem -1, colors);
        res += val;
    }
    res = (res * (colors - 1)) % 998244353;
    dp[bricks][blocksRem] = res;
    return res;
}

int main(){
    cin >> n >> m >> k;
    ll currlen = 0;
    ll res = recursion(n, k+1, m) * m % 998244353;
    cout << res << '\n';

    return 0;
}