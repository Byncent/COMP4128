#include <bits/stdc++.h>

using namespace std;

// Typedefs
typedef long long ll;
typedef pair<ll, ll> pll;

struct edge{
    ll u,v;
};

// Constants definition
const ll N = 1e4+7;
const ll INF = 1e15;

// Global vars definition
ll n, k, d = 0;
ll deepest = 0;

ll depth[N];
vector<edge> edges[N];
ll adjMat[N][N];
ll parent[N];

/* tree construction with LCA*/
void dfs(ll c, ll cPar = -1) {

    for (edge nxt : edges[c]) {
        ll v = nxt.v, w = adjMat[c][v];
        // cout << "visiting edge " << c << " - " << v<< " = " << w << '\n';
        if (w == 0) continue;
        if (v == cPar) continue;
        depth[v] = depth[c] +1;

        if(depth[v] > d){
            d = depth[v];
            deepest = v;
        }
        d = max(d, depth[v]);
        parent[v] = c;
        dfs(v, c);
    }
}


int main(){
    cin >> n >> k;

    for(ll i = 1; i < n; i ++){
        ll u, w;
        cin >> u >> w;
        adjMat[u][i] = w;
        edges[u].push_back(edge{u, i});
    }

    ll res = 0;
    ll minCapacity = INF;
    for(ll i = 0; i < k; i += minCapacity){
        // cout << "i = " << i << '\n';
        // cout << "starting dfs\n";
        deepest = 0;
        d = 0;
        dfs(0);

        // cout << "deepest node is " << deepest << '\n';
        int deepest_cpy = deepest;
        while(deepest_cpy!= 0){
            // cout << "searching thru the edge " << parent[deepest_cpy] << " - " << deepest_cpy << '\n';
            minCapacity = min(minCapacity, adjMat[parent[deepest_cpy]][deepest_cpy]);
            deepest_cpy = parent[deepest_cpy];
        }

        // cout << "min capacity is " << minCapacity << '\n';
        deepest_cpy = deepest;
        while(deepest_cpy!= 0){
            // cout << "subtracting" << minCapacity <<" from the edge " << parent[deepest_cpy] << " - " << deepest_cpy << '\n';
            adjMat[parent[deepest_cpy]][deepest_cpy] -= minCapacity;
            deepest_cpy = parent[deepest_cpy];
        }

        res += d * min(k-i, minCapacity);
    }

    cout << res << '\n';
    return 0;
}