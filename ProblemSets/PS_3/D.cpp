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

const int N = 1e6;

ll dp[N];
int n, k;
string r;
set<int> s;

int main(){

    cin >> n >> k >> r;
    for(int i = 1; i <= n; i ++){
        if (r[i-1] == '1'){
            s.insert(i);
        }
    }

    // cout << "set elements: ";

    // for(auto it = s.begin(); it != s.end(); it++){
    //     cout << *it << ", ";
    // }
    // cout << '\n';

    for(int i = 1;i <= n;  i ++){
        auto router = s.lower_bound(max(i-k, 1));
        
        if( router!= s.end() && *router<=i+k){
            // cout << "i = " << i << '\n';
            // cout << "router at: " << *router << '\n';
            // cout << "index of second element: " << max(*router - k, 1) -1 << '\n';
            // cout << "first element: " << dp[i-1]+i << '\n';
            // cout << "second element: " << dp[max(*router - k, 1) -1] + *router << '\n';
            dp[i] = min(dp[i-1]+i, dp[max(*router - k, 1) - 1] + *router);
        } else{
            dp[i] = dp[i-1]+i;
        }
    }

    // for(int i = 1; i <= n ;i ++){
    //     cout << dp[i] << '\n';
    // }

    cout << dp[n] << '\n';

    return 0;
}