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

// Global vars definition

// problem parameters
int n, m;

// union find
int parent[N];
int subtree_size[N];

// MST
edge edges[N];
int p[N];

/* functions*/

/* union find */
bool operator< (const edge& a, const edge& b) {
    return a.w < b.w;
}

void init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        subtree_size[i] = 1;
    }
}

int root(int x) { 
    return parent[x] == x ? x : root(parent[x]); 
}

void join(int x, int y) {
    cout << "joining " << x << " and " << y << '\n';
    int root_x = root(x); 
    int root_y = root(y);

    // join roots
    cout << "root of " << x << " is " << root_x << '\n';
    cout << "root of " << y << " is " << root_y << '\n';

    // test whether already connected
    if (root_x == root_y)
        return;

    // size heuristic
    // hang smaller subtree under root of larger subtree
    if (subtree_size[root_x] < subtree_size[root_y]) {
        
        parent[root_x] = root_y;
        subtree_size[root_y] += subtree_size[root_x];
    } else {
        parent[root_y] = root_x;
        subtree_size[root_x] += subtree_size[root_y];
    }
}

/* MST*/
int mst() {
    sort(edges, edges+m); // sort by increasing weight
    int total_weight = 0;
    for (int i = 0; i < m; i++) {
        edge& e = edges[i];
        // if the endpoints are in different trees, join them
        if (root(e.u) != root(e.v)) {
            total_weight += e.w;
            join(e.u, e.v);
        }
    }
    return total_weight;
}


int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i ++){
        int u, v, w;
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    init(n);
    mst();
    for(int i = 1; i <= n; i ++){
        cout << "parent of " << i << " is " << parent[i] << '\n';
    }
    cout << '\n';
    return 0;
}