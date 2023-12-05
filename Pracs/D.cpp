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
typedef pair<ll, ll> pll;
/*
 * tree representation
 */

const int N = 1e8 + 5;

int n;

// We need the list of edges to construct our representation
// But we don't use it afterwards.
vector<int> edges[N];
int par[N]; // Parent. -1 for the root.
vector<int> children[N]; // Your children in the tree.
int size_tree[N]; // As an example: size of each subtree.
int parent[N][N];
int depth[N];
int log2s[N];

void constructTree(int c, int cPar = -1) {
    par[c] = cPar;
    size_tree[c] = 1;
    for (int nxt : edges[c]) {
        if (nxt == par[c]) continue;
        constructTree(nxt, c);
        children[c].push_back(nxt);
        size_tree[c] += size_tree[nxt];
    }
}


/*
 * lca 1
 */

// parent[u][k] is the 2^k-th parent of u
void preprocess() {
  for (int i = 0; i < n; i++) {
    // assume parent[i][0] (the parent of i) is already filled in
    for (int j = 1; (1<<j) < n; j++) {
      parent[i][j] = -1;
    }
  }

  // fill in the parent for each power of two up to n
  for (int j = 1; (1<<j) < n; j++) {
    for (int i = 0; i < n; i++) {
      if (parent[i][j-1] != -1) {
        // the 2^j-th parent is the 2^(j-1)-th parent of the 2^(j-1)-th parent
        parent[i][j] = parent[parent[i][j-1]][j-1];
      }
    }
  }
}


/*
 * lca 2
 */

int lca (int u, int v) {
  // make sure u is deeper than v
  if (depth[u] < depth[v]) swap(u,v);
  
  // log2s[i] holds the largest k such that 2^k <= i
  // precompute by DP: log2s[i] = log2s[i/2] + 1
  for (int i = log2s[depth[u]]; i >= 0; i--) {
    // repeatedly raise u by the largest possible power of two until it is the same depth as v
    if (depth[u] - (1<<i) >= depth[v]) u = parent[u][i]; 
  }

  if (u == v) return u;

  for (int i = log2s[depth[u]]; i >= 0; i--)
    if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
      // raise u and v as much as possible without having them coincide
      // this is important because we're looking for the lowest common ancestor, not just any
      u = parent[u][i];
      v = parent[v][i];
    }

  // u and v are now distinct but have the same parent, and that parent is the LCA
  return parent[u][0];
}


int main(){
    int n, t;
    for(int i = 1; i < n; i ++){
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    constructTree()
}