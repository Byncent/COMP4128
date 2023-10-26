#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <functional>

typedef long long ll;
using namespace std;

int m;
int n;
int k;
int pad;
const int N = 1e4;

int a[N];
int b[N];
int dp[N][N];


int main(){

    cin >> n >> k;
    for(int i = 0; i < n; i ++){
        cin >> a[i] >> b[i];
    }

    pad = k+1;

    dp[0][pad-1] = a[0];
    dp[0][pad+1] = b[0];

    for(int i = 1; i < n; i ++){
        for(int j = max(pad-k, pad-i-1); j <= min(pad+k, pad+i+1); j ++){

            int val1 = dp[i-1][j-1];
            if (val1 != 0){
                val1 += b[i];
            } 

            int val2 = dp[i-1][j+1];
            if(val2 != 0){
                val2 += a[i];
            } 

            dp[i][j] = max(val1, val2);

        }
    }

    int sol = 0;
    for(int item : dp[n- 1]){
        sol = max(sol, item);
    }

    cout << sol << '\n';



    return 0;

}