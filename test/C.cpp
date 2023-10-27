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
const ll N = 1e6+7;

// Global vars definition
ll n, m;

ll low[N];
ll preorder[N];
ll T = 0;
ll bridges = 0;
vector<ll> bi_edges[N];
vector<ll> uni_edges[N];

void dfs(ll u, ll from = -1) {
    low[u] = preorder[u] = T++;
    // cout << "update: low[" << u <<"] = preorder[" << u <<"] = " << low[u] << '\n';
    
    for (ll v : bi_edges[u]) {
        // Ignore the edge to our parent in the dfs
        if (v == from)
            continue;

        // cout << "  curr edge: " << u << " - " << v << '\n';
        // cout << "  preorder[v]: " << preorder[v] << '\n';

        // Update the lowest value in the preorder sequence that we can reach
        if (preorder[v] != -1){
            if (low[u]> preorder[v]){
                uni_edges[u].push_back(v);
            }
            low[u] = min(low[u], preorder[v]);
        } else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            
            // If we haven't visited v before, check to see if we have a bridge
            if (low[v] == preorder[v] && low[v] != 0){
                bridges ++;
            }else{
                // cout << "# edge added: " << u << " ==> " << v << '\n';
                // cout << "# low[v] = " << low[v] << ", preorder[v] = " << preorder[v] << '\n';
                uni_edges[u].push_back(v);
            }
        }
    }
}


int main(){
    cin >> n >> m;

    for(ll i = 0; i < m; i ++){
        ll u, v;
        cin >> u >> v;
        bi_edges[u].push_back(v);
        bi_edges[v].push_back(u);
    }

    for(ll i = 0; i <= n+10; i ++){
        preorder[i] = -1;
    }

    dfs(1);

    // cout << "================================\n";
    if(bridges!=0){
        cout << 0 << '\n';
    } else{
        for(ll u = 0; u < m; u ++){
            for(ll v : uni_edges[u]){
                cout << u << ' ' << v << '\n';
            }
        }
    }

    return 0;
}