#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>

using ll = long long;
using namespace std;

const ll N = 100000;
ll n;
ll a1[N];
ll a2[N];

ll recursion(ll i, ll j){
    
    if(i > n || j > n){
        return 0;
    }

    ll sol, sol1, sol2;
    if(i>j) {
        sol1 = a1[i] + recursion(i, i+1);
        sol2 = a1[i] + recursion(i, i+2);
    }else{
        sol1 = a2[j] + recursion(j+1, j);
        sol2 = a2[j] + recursion(j+2, j);
    }
    sol = max(sol1, sol2);


    return sol;
}

int main(){
    cin >> n;
    for(ll i = 1; i <= n; i++){
        cin >> a1[i];
    }
    for(ll i = 1; i <= n; i++){
        cin >> a2[i];
    }

    ll sol = max(recursion(0, 1), recursion(1, 0));

    cout << sol << '\n';
    return 0;
}