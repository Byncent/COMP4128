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

    pq.push(e);  // distance to itself is zero
    dist[s] = 0;
    while (!pq.empty()) {
        // choose (d, v) so that d is minimal
        // i.e. the closest unvisited vertex
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


ll n, C;
set<pll> mountains;
int main(){
    cin >> n >> C;
    ll h1, h2;
    cin >> h1;

    mountains.insert(make_pair(h1, 0));

    for(ll i = 1; i < n; i ++){

        cin >> h2;

        auto it = mountains.upper_bound(make_pair(h2, i));
        if(it != mountains.end()){
            pll a = *it;
            edges[a.second].push_back(Edge{i, C});
        }

        mountains.insert(make_pair(h2, i));

        edges[i-1].push_back(Edge{i, abs(h1-h2)});

        h1 = h2;
    }

    // for(ll i = 0; i < n; i ++){
    //     for(Edge e : edges[i]){
    //         cout << "edge : " << i << " - " << e.v << " = " << e.w << '\n';
    //     }
    // }

    dijkstra(0);

    cout << dist[n-1] << '\n';
}