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
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;

struct edge {
    ll u, v, w;
};

// Constants definition
const ll N = 200007;
const ll max_log = 15;

// Global vars definition

// problem parameters
ll n, m, log2_n;

// union find
ll union_root[N];
ll union_subtree_size[N];

// MST
edge edges[N];
edge sorted_edges[N];
vector<edge> MST_edges[N];

// Tree Construction
ll parent[N][max_log]; // Parent. -1 for the root.
ll max_up[N][max_log]; // the maximum cost out of all edges from node i goes up to 2*max_log level

// LCA
ll depth[N];
// ll log2s[N];

/* functions*/

/* union find */
bool operator< (const edge& a, const edge& b) {
    return a.w < b.w;
}

void init() {
    for (ll i = 1; i <= n; i++) {
        union_root[i] = i;
        union_subtree_size[i] = 1;
    }
}

ll root(ll x) { 
    return union_root[x] == x ? x : union_root[x] = root(union_root[x]);
}

void join(ll x, ll y) {
    // cout << "joining " << x << " and " << y << '\n';
    ll root_x = root(x); 
    ll root_y = root(y);

    // cout << "root of " << x << " is " << root_x << '\n';
    // cout << "root of " << y << " is " << root_y << '\n';

    // test whether already connected
    if (root_x == root_y)
        return;

    // size heuristic
    // hang smaller subtree under root of larger subtree
    if (union_subtree_size[root_x] < union_subtree_size[root_y]) {
        union_root[root_x] = root_y;
        union_subtree_size[root_y] += union_subtree_size[root_x];
    } else {
        union_root[root_y] = root_x;
        union_subtree_size[root_x] += union_subtree_size[root_y];
    }
}

/* MST*/
ll mst() {
    sort(sorted_edges, sorted_edges+m); // sort by increasing weight
    ll total_weight = 0;
    for (ll i = 0; i < m; i++) {
        edge& e = sorted_edges[i];
        // if the endpolls are in different trees, join them
        if (root(e.u) != root(e.v)) {
            MST_edges[e.u].push_back(edge{e.u, e.v, e.w});
            MST_edges[e.v].push_back(edge{e.v, e.u, e.w});
            total_weight += e.w;
            join(e.u, e.v);
        }
    }
    return total_weight;
}

/* tree construction with LCA*/
void constructTree(ll c, ll cPar = 0) {

    for (edge nxt : MST_edges[c]) {
        ll v = nxt.v, w = nxt.w;
        if (v == parent[c][0]) continue;
        depth[v] = depth[c] +1;
        parent[v][0] = c;
        max_up[v][0] = w;
        constructTree(v, c);
    }
}

/* LCA */
// parent[u][k] is the 2^k-th parent of u
void preprocess() {
    // fill in the parent for each power of two up to n
    for (ll j = 1; (1<<j) < n; j++) {
        for (ll i =1; i <= n; i++) {

                // cout << "parent["<<i << "]["<<j<<"]" << " = " << parent[parent[i][j-1]][j-1] << '\n';
                // the 2^j-th parent is the 2^(j-1)-th parent of the 2^(j-1)-th parent
                parent[i][j] = parent[parent[i][j-1]][j-1];
                max_up[i][j] = max(max_up[i][j-1], max_up[parent[i][j-1]][j-1]);

        }
    }
}

// void init_logs(){
//     for(ll i = 2; i < n; i ++){
//         log2s[i] = log2s[i/2] + 1;
//     }
// }

ll compute_lca (ll u, ll v) {
    
    // make sure u is deeper than v
    if (depth[u] < depth[v]) swap(u,v);
    // cout << "Computing the LCA of " << u << " and " << v << '\n';
    // log2s[i] holds the largest k such that 2^k <= i
    // precompute by DP: log2s[i] = log2s[i/2] + 1
    for (ll i = log2_n; i >= 0; i--) {
        // repeatedly raise u by the largest possible power of two until it is the same depth as v
        if (depth[parent[u][i]]>= depth[v]){
            u = parent[u][i]; 
        }
    }

    // cout << "u = " << u << ", v = " << v << '\n';
    if (u == v) return u;

    for (ll i = log2_n; i >= 0; i--)
        if (parent[u][i] != parent[v][i]) {
            // raise u and v as much as possible without having them coincide
            // this is important because we're looking for the lowest common ancestor, not just any
            u = parent[u][i];
            v = parent[v][i];
        }

    // u and v are now distinct but have the same parent, and that parent is the LCA
    // cout << "last nodes diff are " << u << " and " << v<<'\n'; 
    return parent[u][0];
}

ll max_along_path(ll u, ll lca){
    ll res = 0;

    for (ll i = log2_n; i >= 0; i--) {
        // repeatedly raise u by the largest possible power of two until it is the same depth as lca
        if (depth[parent[u][i]]>= depth[lca]){
            res = max(res, max_up[u][i]);
            u = parent[u][i]; 
        }
    }
    return res;
}

int main(){

    cin >> n >> m;
    log2_n = log2(n);
    for(ll i = 0; i < m; i ++){
        ll u, v, w;
        cin >> u >> v >> w;
        edge e = edge{u, v, w};
        edges[i] = e;
        sorted_edges[i] = e;
    }
    // init_logs();
    init();

    ll min_weight = mst();

    depth[1] = 1;
    constructTree(1);

    preprocess();

    for(ll i = 0; i < m; i ++){
        edge e = edges[i];
        ll lca = compute_lca(e.u, e.v);
        ll max_cost = max(max_along_path(e.u, lca), max_along_path(e.v, lca));
        cout << min_weight + e.w - max_cost << '\n';
    }


    return 0;
}