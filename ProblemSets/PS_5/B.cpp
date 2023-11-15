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

// Hash defines
#define TRUE 0
#define FALSE 1
#define CAR 0
#define TRAIN 1

// Typedefs
typedef long long ll;
typedef pair<ll, ll> pll;
typedef struct Edge{
    ll vertex;
    ll distance;

    // Overload the '<' operator
    bool operator<(Edge const& other) const {
        return distance < other.distance;
    }

    // Overload the '>' operator
    bool operator>(Edge const& other) const {
        return distance > other.distance;
    }
} Edge;

//Constants definition
const ll N = 1e6+7;
const ll INF = 1e15+10;

// Global vars definition
ll n, m, k;
vector<Edge> edges[N];
vector<Edge> routes;
ll deg[N];
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
        ll v = cur.vertex;
        // cout << "visiting node: " << cur.vertex;
        if (seen[v]){
            // cout << " but skipped\n";
            continue;
        }

        seen[v] = 1;

        // cout << " for the first time\n";

        // relax all edges from v
        for (Edge nxt : edges[v]) {
            ll u = nxt.vertex, weight = nxt.distance;
            
            if(dist[v]+weight < dist[u]){
                dist[u] = dist[v]+weight;
                deg[u] = 1;
                pq.push(Edge{u, dist[u]});
            } else if(dist[v]+weight == dist[u]){
                deg[u] ++;
            }
        }
    }
}

int main(){
    cin >> n >> m >> k;

    for(ll i = 0; i < m; i ++){
        ll u, v, x;
        cin >> u >> v >> x;

        Edge e1 = {v, x};
        Edge e2 = {u, x};
        edges[u].push_back(e1);
        edges[v].push_back(e2);
    }

    for(ll i = 0; i < k; i ++){
        ll s, y;
        cin >> s >> y;

        Edge e1 = {s, y};
        routes.push_back(e1);
        edges[1].push_back(e1);
    }

    // for(ll i = 1; i <= n; i ++){
    //     for(Edge e : edges[i]){
    //         cout << "edge: " << i << " - " << e.vertex << " = " << e.distance << '\n';
    //     }
    // }

    dijkstra(1);

    // for(ll i = 0; i <= n; i ++){
    //     cout << "deg " << i << ": " << deg[i] << '\n';
    // }

    // for(ll i = 1;i <=n; i ++){
    //     cout << "dist to " << i << ": " << dist[i] << '\n';
    // }
    ll c = 0;
    for(Edge e : routes){
        if(e.distance > dist[e.vertex]){
            c++;

        }else if (e.distance  ==  dist[e.vertex] && deg[e.vertex] >1 ){

            c++;
            deg[e.vertex] --;
            
        }
    }

    cout << c << '\n';


    return 0;
}

