#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll INF = 1e15;

struct edge{
    ll u, v, w;
};

struct FlowNetwork {
    ll n;
    vector<vector<ll>> adjMat, adjList;
    // level[v] stores dist from s to v
    // uptochild[v] stores first non-useless child.
    vector<ll> level, uptochild;

    FlowNetwork (ll _n): n(_n) {
        // adjacency matrix is zero-initialised
        adjMat.resize(n);
        for (ll i = 0; i < n; i++)
            adjMat[i].resize(n);
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge (ll u, ll v, ll c) {
        // add to any existing edge without overwriting
        adjMat[u][v] += c;        
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void flow_edge (ll u, ll v, ll c) {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }


    // constructs the BFS tree and returns whether the sink is still reachable
    bool bfs(ll s, ll t) {
        fill(level.begin(), level.end(), -1);
        queue<ll> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            ll u = q.front(); q.pop();
            uptochild[u] = 0; // reset uptochild
            for (ll v : adjList[u])
                if (adjMat[u][v] > 0) {
                    if (level[v] != -1) // already seen
                        continue;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
        }
        return level[t] != -1;
    }


    // finds an augmenting path with up to f flow.
    ll augment(ll u, ll t, ll f) {
        if (u == t) return f; // base case.
        // note the reference here! we increment uptochild[u], i.e. walk through u's neighbours
        // until we find a child that we can flow through
        for (ll &i = uptochild[u]; i < adjList[u].size(); i++) {
            ll v = adjList[u][i];
            if (adjMat[u][v] > 0) {
                // ignore edges not in the BFS tree.
                if (level[v] != level[u] + 1) continue;
                // revised flow is constrained also by this edge
                ll rf = augment(v,t,min(f, adjMat[u][v]));
                // found a child we can flow through!
                if (rf > 0) {
                    flow_edge(u,v,rf);
                    return rf;
                }
            }
        }
        level[u] = -1;
        return 0;
    }


    ll dinic(ll s, ll t) {
        ll res = 0;
        while (bfs(s,t))
            for (ll x = augment(s,t,INF); x; x = augment(s,t,INF))
                res += x;
        return res;
    }
};

ll n, m, b;
vector<edge> edges;

// Find the smallest X such that f(X) is true;


bool check(double weightpp){
    FlowNetwork network(n+1);
    for(ll i = 0; i < m; i ++){
        edge e = edges[i];
        network.add_edge(e.u, e.v, floor(e.w/weightpp));
    }
    ll flow = network.dinic(1, n);
    // cout << "flow = " << flow << '\n';
    if(flow >= b){
        return true;
    }else{
        return false;
    }
}

double binarysearch() {

    double lo = 0;
    double hi = 100000010.0;
    double bestSoFar = 1.0;
    
    // Range [lo, hi];
    for(int i = 0; i < 100; i++){
        // cout << "High: " << hi << '\n';
        // cout << "Low: " << lo << '\n';
        // cout << "best: " << bestSoFar << '\n'; 
        double mid = (lo + hi) / 2.0;
        if (check(mid)) {
            bestSoFar = mid;
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return bestSoFar;
}

int main(){
    cin >> n >> m >> b;
    for(ll i = 1; i <= m; i ++){
        ll u, v, w;
        cin >> u >> v >> w;
        edge e = edge{u, v, w};
        edges.push_back(e);
    }
    
    double res = binarysearch();
    cout << setprecision(10) << res*b << '\n';

}
