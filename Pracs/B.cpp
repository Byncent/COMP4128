#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <functional>

using namespace std;

// Hash defines
#define TRUE 0
#define FALSE 1

// Typedefs
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;

// Constants definition
const ll N = 1e9+7;

// Global vars definition
ll n, m, copies = 0;
vector<ll> groups;
vector<ll> flags;

int main(){
    cin >> n >> m;

    for(ll i = 0; i < n; i ++){
        ll t;
        cin >> t;
        groups.push_back(t);
    }

    for(ll i = 0; i < m; i ++){
        ll t;
        cin >> t;
        flags.push_back(t);
    }

    sort(groups.begin(), groups.end(), greater<ll>());
    sort(flags.begin(), flags.end(), greater<ll>());

    for(ll i = 0; i < n; i ++){
        if(flags[i]+copies<groups[i]){
            copies += groups[i] - (flags[i]+copies);
        }
    }

    if(copies == 0){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
    return 0;
}