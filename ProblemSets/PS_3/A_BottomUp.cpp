#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>

using ll = long long;
using namespace std;

const ll N = 200000;
ll n;
ll a1[N];
ll a2[N];
ll dp[2][N];

int main(){
    cin >> n;
    for(ll i = 1; i <= n; i++){
        cin >> a1[i];
    }
    for(ll i = 1; i <= n; i++){
        cin >> a2[i];
    }

    for(int i = 1; i <= n; i++){
        dp[0][i] = max(dp[1][i-1]+a1[i], dp[0][i-1]);
        dp[1][i] = max(dp[0][i-1]+a2[i], dp[1][i-1]);
    }
    
    ll res = max(dp[0][n], dp[1][n]);
    cout << res;
    return 0;
}