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
    ll to;
    ll dist;

    // Overload the '>' operator
    bool operator>(Edge const& other) const {
        return dist > other.dist;
    }
} Edge;

//Constants definition
const ll N = 1e6+7;
const ll INF = 1e15+10;

// Global vars definition
ll n, m, k;
vector<Edge> G[N];
pll routes[N];
ll deg[N];
ll d[N];
bool done[N];

priority_queue<Edge, vector<Edge>, greater<Edge> > q;

void dijkstra(int s){

    for (int i =0;i<=n;i++)
        d[i]=INF;
    d[s]=0;
    q.push((Edge){0,s});
    while (!q.empty())
    {
        Edge x = q.top();q.pop();
        int u = x.to;
        if (done[u])continue;
        done[u]=1;
        for (Edge e : G[u]) {
            if (d[e.to] == d[u]+e.dist)
                deg[e.to]++;
            if (d[e.to] > d[u]+e.dist)
            {
                d[e.to] = d[u] + e.dist;
                deg[e.to]=1;
                q.push((Edge){d[e.to],e.to});
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
        G[u].push_back(e1);
        G[v].push_back(e2);
    }

    for(ll i = 0; i < k; i ++){
        ll s, y;
        cin >> s >> y;
        Edge e1 = {s, y};
        routes[i] = make_pair(s, y);
        G[1].push_back(e1);
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
    for(int i = 0 ; i < k; i ++){

        ll v = routes[i].first;
        ll ds = routes[i].second;

        if(ds > d[v]){
            c++;
        }else if (ds == d[v] && deg[v] >1 ){
            c++;
            deg[v] --;
        }
    }

    cout << c << '\n';


    return 0;
}