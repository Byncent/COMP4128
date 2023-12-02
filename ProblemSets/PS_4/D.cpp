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
typedef struct edge{
    int idx;
    int v;
} edge;

// Constants definition
const int N = 1e4+7;

// Global vars definition
int n, m;

vector<edge> edges[N];
int seen[N];
int active[N];
int colouring[N];

void add_edge(int i, int u, int v){
    edge e = edge{i, v};
    edges[u].push_back(e);
}

// the vertices that are still marked active when this returns are the ones in the cycle we detected
bool has_cycle(int u) {
    bool flag = false;
    // cout << "At vertex " << u << '\n';
    if (seen[u]) return false;
    seen[u] = true;
    active[u] = true;
    for (edge e : edges[u]) {
        int v = e.v;
        int i = e.idx;
        // cout << "Edge " << u << " - " << v;
        if (active[v]){
            // cout << " introduces a cycle\n";
             colouring[i] = 1; 
        }else {
            // cout << " does NOT introduce a cycle\n";
        }
        if(has_cycle(v) || active[v]){
            flag = true;
        }
    }
    active[u] = false;
    return flag;
}

int main(){
    cin >> n >> m;

    for(int i = 0; i < m; i ++){
        int u, v;
        cin >> u >> v;
        add_edge(i, u, v);
    }

    int colours = 1;
    for(int i = 1; i <= n; i ++){
        // cout << "Cycle detection from vertex " << i << '\n';
        if (has_cycle(i)) colours = 2;
    }
    cout << colours << '\n';

    for(int i = 0; i < m; i ++){
        cout << colouring[i]+1 << ' ';
    }

    cout << "\n";

    return 0;
}