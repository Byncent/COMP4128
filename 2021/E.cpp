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

ll n, s, f, m, g;
vector<int> gods[N];

int main(){
    cin >> n >> s >> f >> m >> g;

    for(int i = 1; i <= n; i ++){
        int cnt;
        cin >> cnt;
        for(int j = 0; j < cnt; j ++){
            int god;
            cin >> god;
            gods[god].push_back(i);
        }
    }

    for(int i = 0; i < m; i ++){
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back(Edge{v, w});
        edges[v].push_back(Edge{u, w});
    }

    for(int i = 1; i <= g; i ++){
        int cost;
        cin >> cost;

        for(int town : gods[i]){
            edges[town].push_back(Edge{n+i, cost});
            edges[n+i].push_back(Edge{town, 0});
        }
    }

    dijkstra(s);
    if(dist[f] >= INF){
        cout << -1 << '\n';
    }else{
        cout << dist[f] << '\n';
    }

}