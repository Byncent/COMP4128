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
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

struct edge {
    int u, v, w;
};

// Constants definition
const int N = 1e5+7;
const int max_log = 20;

// Global vars definition

// problem parameters
int n, m;

// MST
edge edges[N];
vector<edge> graph[N];
int p[N];

// Tree Construction
int parent[N][max_log]; // Parent. -1 for the root.
vector<int> children[N]; // Your children in the tree.
int size[N]; // As an example: size of each subtree.

// LCA
int depth[N];
int log2s[N];

/* LCA */
// parent[u][k] is the 2^k-th parent of u
void preprocess() {
    for (int i = 1; i <= n; i++) {
        // assume parent[i][0] (the parent of i) is already filled in
        for (int j = 1; (1<<j) < n; j++) {
            parent[i][j] = -1;
        }
    }

    // fill in the parent for each power of two up to n
    for (int j = 1; (1<<j) < n; j++) {
        for (int i =1; i <= n; i++) {
            if (parent[i][j-1] != -1) {
                // cout << "parent["<<i << "]["<<j<<"]" << " = " << parent[parent[i][j-1]][j-1] << '\n';
                // the 2^j-th parent is the 2^(j-1)-th parent of the 2^(j-1)-th parent
                parent[i][j] = parent[parent[i][j-1]][j-1];
            }
        }
    }
}

void init_logs(){
    for(int i = 2; i < N; i ++){
        log2s[i] = log2s[i/2] + 1;
    }
}

int lca (int u, int v) {
    
    // make sure u is deeper than v
    if (depth[u] < depth[v]) swap(u,v);
    // cout << "Computing the LCA of " << u << " and " << v << '\n';
    // log2s[i] holds the largest k such that 2^k <= i
    // precompute by DP: log2s[i] = log2s[i/2] + 1
    for (int i = log2s[depth[u]]; i >= 0; i--) {
        // cout << "i = " << i << '\n';
        // repeatedly raise u by the largest possible power of two until it is the same depth as v
        if (depth[u] - (1<<i) >= depth[v]){
            // cout << "depth of " << u << " is " << depth[u] << '\n';
            // cout << "depth of " << v << " is " << depth[v] << '\n';
            // cout << "u is updated to " << parent[u][i] << '\n';
            u = parent[u][i]; 
        }
    }

    // cout << "u = " << u << ", v = " << v << '\n';
    if (u == v) return u;

    for (int i = log2s[depth[u]]; i >= 0; i--)
        if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
            // raise u and v as much as possible without having them coincide
            // this is important because we're looking for the lowest common ancestor, not just any
            u = parent[u][i];
            v = parent[v][i];
        }

    // u and v are now distinct but have the same parent, and that parent is the LCA
    // cout << "last nodes diff are " << u << " and " << v<<'\n'; 
    return parent[u][0];
}

/* tree construction with LCA*/
void constructTree(int c, int cPar = 0) {
    parent[c][0] = cPar;
    size[c] = 1;
    for (edge nxt : graph[c]) {
        int v = nxt.v;
        if (v == parent[c][0]) continue;
        depth[v] = depth[c] +1;
        constructTree(v, c);
        children[c].push_back(v);
        size[c] += size[v];
    }
}
int main(){

    cin >> n >> m;
    for(int i = 0; i < m; i ++){
        int u, v, w;
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    constructTree(1);

    preprocess();

    return 0;
}