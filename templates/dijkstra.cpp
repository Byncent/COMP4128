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
typedef struct Edge{
    ll v;
    ll w;

    // Overload the '<' operator
    bool operator<(Edge const& other) const {
        return w < other.w;
    }

    // Overload the '>' operator
    bool operator>(Edge const& other) const {
        return w > other.w;
    }
} Edge;


//Constants definition
const ll N = 1e6+7;
const ll INF = 1e15+10;

// Global vars definition
vector<Edge> edges[N];
ll dist[N];
bool seen[N];

priority_queue<Edge, vector<Edge>, greater<Edge> > pq;

void dijkstra(ll s) {

    fill(dist, dist + N, INF);
    Edge e = {s, 0};

    pq.push(e);  // w to itself is zero
    dist[s] = 0;
    while (!pq.empty()) {
        // choose (d, v) so that d is minimal
        // i.e. the closest unvisited v
        Edge cur = pq.top();
        pq.pop();
        ll v = cur.v;

        if (seen[v]){
            continue;
        }

        seen[v] = 1;


        // relax all edges from v
        for (Edge nxt : edges[v]) {
            ll u = nxt.v, weight = nxt.w;
            
            if(dist[v]+weight < dist[u]){
                dist[u] = dist[v]+weight;
                pq.push(Edge{u, dist[u]});
            }
        }
    }
}

ll n, m, k;

int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i ++){
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back(Edge{v, w});
    }
}