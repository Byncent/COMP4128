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
    ll vertex;
    ll distance;
    bool seen;

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
ll dist[N];
bool seen[N];

priority_queue<Edge, vector<Edge>, greater<Edge> > pq;

int dijkstra(ll s) {

    fill(dist, dist + N, INF);
    Edge e = {s, 0, false};

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
            Edge new_edge = Edge{u, dist[u]};
            
            if(dist[v]+weight < dist[u]){
                if(u == a || u == c){
                    if(cur.seen){
                        return -1;
                    } else{
                        new_edge.seen = true;
                    }
                }
                dist[u] = dist[v]+weight;
                pq.push(new_edge);
            }
        }
    }
    return 0;
}


int n, m;
int a, b, c;
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i ++){
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back(Edge{v, w, false});
    }

    cin >> a >> b >> c;
    

    if(dijkstra(b) == -1){
        cout << "NO\n";
    }else {
        cout << "YES\n";
    }
}