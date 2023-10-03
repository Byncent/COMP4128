#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>

typedef long long ll;
using namespace std;

const int N = 200;

ll trees[N];
ll coloring[N][N];

int main(){
    ll n, m, k;
    cin >> n >> m >> k;

    ll numEmpty;
    ll numGrps;
    for(int i = 0; i < n; i ++){
        int val;
        cin >> val;
        trees[i] = val;
    }

    for(ll i = 0; i < n; i ++){
        for(ll j = 0; j < m; j++){
            cin >> coloring[i][j];
        }
    }


}