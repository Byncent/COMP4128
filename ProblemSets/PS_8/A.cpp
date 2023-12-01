#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <functional>

using namespace std;

typedef long long ll;

const ll m = 1000000007;

ll pow(ll x, ll n, ll m) {
    if (n == 0) return 1;
    ll a = pow(x, n/2, m);
    a = a * a % m;
    if (n%2 == 1) a = a * x % m;
    return a;
}

int main(){
    ll T;
    cin >> T;
    for(ll i = 0; i < T; i ++){
        vector<ll> s;
        ll smax = 0;
        ll smin = 0;
        ll n;
        cin >> n;
        for(ll j = 0; j < n; j ++){
            ll val;
            cin >> val;
            s.push_back(val);
        }

        sort(s.begin(),s.end(), greater<ll>());
        for(ll j = 0; j < n; j ++){
            // cout << "pow smax = " << pow(2, n-j-1, m) << '\n';
            smax = (smax + s[j] * pow(2, n-j-1, m) % m ) % m;
            // cout << "smax = " << smax << '\n';
            // cout << "pow smin = " << pow(2, j, m) << '\n';
            smin = (smin + s[j] * pow(2, j, m) % m )% m;
            // cout << "smin = " << smin << '\n';
        }
        cout << (smax + m - smin) % m << '\n';
    }
}