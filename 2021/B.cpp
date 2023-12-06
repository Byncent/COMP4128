#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll N = 1e6+7;

ll n, res = 0;
ll diff[N];

int main(){

    cin >> n;
    for(ll i = 0; i < 2*n; i ++){
        ll c, d;
        cin >> c >> d;
        diff[i] = d - c;
        res += c;
    }

    sort(diff, diff+2*n,  greater<ll>());

    for(ll i = 0;i < n; i ++){
        res += diff[i];
    }

    cout << res << '\n';

}