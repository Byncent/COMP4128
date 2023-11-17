#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <functional>

using namespace std;

typedef long long ll;
const ll INF = 1e15;
/*
 * dinic 1
 */

struct FlowNetwork {
    int n;
    vector<vector<ll> > adjMat, adjList;
    // level[v] stores dist from s to v
    // uptochild[v] stores first non-useless child.
    vector<int> level, uptochild;

    FlowNetwork (int _n): n(_n) {
        // adjacency matrix is zero-initialised
        adjMat.resize(n);
        for (int i = 0; i < n; i++)
            adjMat[i].resize(n);
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge (int u, int v, ll c) {
        // add to any existing edge without overwriting
        adjMat[u][v] += c;        
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void flow_edge (int u, int v, ll c) {
        adjMat[u][v] -= c;
        adjMat[v][u] += c;
    }

/*
 * dinic 2
 */

    // constructs the BFS tree and returns whether the sink is still reachable
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            uptochild[u] = 0; // reset uptochild
            for (int v : adjList[u])
                if (adjMat[u][v] > 0) {
                    if (level[v] != -1) // already seen
                        continue;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
        }
        return level[t] != -1;
    }

/*
 * dinic 3
 */

    // finds an augmenting path with up to f flow.
    ll augment(int u, int t, ll f) {
        if (u == t) return f; // base case.
        // note the reference here! we increment uptochild[u], i.e. walk through u's neighbours
        // until we find a child that we can flow through
        for (int &i = uptochild[u]; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
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

/*
 * dinic 4
 */

    ll dinic(int s, int t) {
        ll res = 0;
        while (bfs(s,t))
            for (ll x = augment(s,t,INF); x; x = augment(s,t,INF))
                res += x;
        return res;
    }
};

int main(){
    int n, m, k, t;
    cin >> n >> m >> k;
    FlowNetwork network(n + m + 3);
    // source to potion
    // cout << "edge: " << 0 << " - " << n+m+2 << " = " << k << "\n";
    network.add_edge(0, n+m+2, k);
    
    for(int i = 1; i <= n; i ++){
        cin >> t;
        // source to warrior
        // cout << "edge: " << 0 << " - " << i << " = " << 1 << "\n";
        network.add_edge(0, i, 1);

        // potion to warrior
        // cout << "edge: " << n+m+2 << " - " << i << " = " << 1 << "\n";
        network.add_edge(n+m+2, i, 1);
        
        for(int j = 1; j <= t; j ++){
            int Mij;
            cin >> Mij;
            // warrior to monster
            // cout << "edge: " << i << " - " << Mij+n << " = " << 1 << "\n";
            network.add_edge(i, Mij+n, 1);
        }
    }

    for(int i = 1; i <= m; i++){
        network.add_edge(i+n, n+m+1, 1);
    }

    int res = network.dinic(0, n+m+1);

    cout << res << '\n';

    return 0;
}