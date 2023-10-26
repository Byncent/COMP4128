#include <iostream>
#include <utility>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <functional>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;

const ll N = 1e6+7;

ll n, m;
vector<pll> edges[N];  // Edges as pairs of (weight, vertex)
bool in_tree[N];
priority_queue<pll, vector<pll>, greater<pll>> pq;  // Min-heap priority queue

void add_edge(ll u, ll v, ll w){
    edges[u].push_back(make_pair(w, v));
}


ll mst(ll root) {
    ll total_weight = 0;
    in_tree[root] = true;  // (2)

    for (auto edge : edges[root]) {
        pq.emplace(edge.first, edge.second);
    }

    ll num_edges = 0;
    while (!pq.empty()) {  // (3)
        auto edge = pq.top();
        pq.pop();

        // If this edge goes to somewhere already in the tree, it's useless.
        if (in_tree[edge.second])
            continue;

        in_tree[edge.second] = true;
        total_weight += edge.first;
        num_edges += 1;

        for (auto edge : edges[edge.second]) {
            pq.emplace(edge.first, edge.second);  // (4)
        }
    }

    if(num_edges == n-1){
        return total_weight;
    } else{
        return -1;
    }
    
}

int main(){

    cin >> n;
    ll root_val = -1;
    ll root_idx = -1;

    for(ll i = 0; i < n; i ++){
        ll val;
        cin >> val;
        if(val > root_val){
            root_val = val;
            root_idx = i + 1;
        }
    }
    cout << "root:" << root << '\n';
    cin >> m;
    for(ll i = 0; i < m; i ++){
        ll u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    ll weight = mst(root_idx);
    cout << weight << '\n';
    return 0;
}