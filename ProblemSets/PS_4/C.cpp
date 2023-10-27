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

// Typedefs
typedef long long ll;

//Constants definition
const ll N = 3 * 1e5+7;

// Global vars definition
ll n, m;

ll low[N];
ll preorder[N];
ll T = 0;
bool bridge = false;
vector<ll> edges[N];
set<pair<ll, ll>> sol;

void dfs(ll u, ll from = -1) {
    low[u] = preorder[u] = T++;
    // cout << "update: low[" << u <<"] = preorder[" << u <<"] = " << low[u] << '\n';
    
    for (ll v : edges[u]) {
        // Ignore the edge to our parent in the dfs
        if (v == from)
            continue;
        // cout << "curr edge: " << u << " - " <<v << '\n';
        // cout << "low[" <<u<<"] = " << low[u] << ", preorder[" <<u<<"] = " <<preorder[u] <<  ", low[" <<v<<"] = " << low[v]<<", preorder[" << v << "] = " <<preorder[v]<< '\n';
        // cout << "  curr edge: " << u << " - " << v << '\n';
        // cout << "  preorder[v]: " << preorder[v] << '\n';
        
        // Update the lowest value in the preorder sequence that we can reach
        if (preorder[v] != -1){
            if (preorder[u]>= preorder[v]){
                sol.insert(make_pair(u, v));
            }
            low[u] = min(low[u], preorder[v]);
        } else {
            sol.insert(make_pair(u, v));
            dfs(v,  u);
            low[u] = min(low[u], low[v]);
            // If we haven't visited v before, check to see if we have a bridge
            if (low[v] == preorder[v]){
                bridge = true;
            }
        }
    }
}


int main(){
    cin >> n >> m;

    for(ll i = 0; i < m; i ++){
        ll u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    for(ll i = 0; i <= n+10; i ++){
        preorder[i] = -1;
    }

    dfs(1);
    // cout << "v_count = " << v_count << '\n';
    // cout << "================================\n";
    if(bridge){
        cout << 0 << '\n';
    } else{
        for(auto it : sol){
            cout << it.first << ' ' << it.second << '\n';
        }

    }

    return 0;
}