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
const ll INF = 1e18;
struct cell{
    ll v = 0;
    ll c = 0;
};

struct FlowNetwork {
    ll n;
    vector<vector<ll>> adjMat, adjList;
    // level[v] stores dist from s to v
    // uptochild[v] stores first non-useless child.
    vector<ll> level, uptochild;

    FlowNetwork(ll _n) : n(_n) {
        // adjacency matrix is zero-initialised
        adjMat.resize(n);
        for (ll i = 0; i < n; i++)
            adjMat[i].resize(n);
        adjList.resize(n);
        level.resize(n);
        uptochild.resize(n);
    }

    void add_edge(ll u, ll v, ll c) {
        // add to any existing edge without overwriting
        adjMat[u][v] += c;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void flow_edge(ll u, ll v, ll c) {
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
            ll u = q.front();
            q.pop();
            uptochild[u] = 0; // reset uptochild

            for (ll v : adjList[u]) {
                if (adjMat[u][v] > 0) {
                    if (level[v] != -1) // already seen
                        continue;
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }

        return level[t] != -1;
    }

    // finds an augmenting path with up to f flow.
    ll augment(ll u, ll t, ll f) {
        if (u == t)
            return f; // base case.

        // note the reference here! we increment uptochild[u], i.e. walk through
        // u's neighbours until we find a child that we can flow through
        for (ll &i = uptochild[u]; i < adjList[u].size(); i++) {
            ll v = adjList[u][i];

            if (adjMat[u][v] > 0) {
                // ignore edges not in the BFS tree.
                if (level[v] != level[u] + 1)
                    continue;

                // revised flow is constrained also by this edge
                ll rf = augment(v, t, min(f, adjMat[u][v]));

                // found a child we can flow through!
                if (rf > 0) {
                    flow_edge(u, v, rf);
                    return rf;
                }
            }
        }

        level[u] = -1;
        return 0;
    }

    ll dinic(ll s, ll t) {
        ll res = 0;
        while (bfs(s, t))
            for (ll x = augment(s, t, INF); x; x = augment(s, t, INF))
                res += x;
        return res;
    }
};

map<ll, ll> weights;
cell graph[50][50];

int main(){
    ll n, m, c;
    cin >> n >> m >> c;
    FlowNetwork network(n * m + 1);

    // node index
    ll cnt = 0;
    ll s, t = n*m;

    for(ll i = 0; i < n; i ++){
        for(ll j = 0; j < m; j ++){
            char chr;
            cin >> chr;

            // assign node index
            graph[i][j].v = cnt;

            // if node is a dot, then capacity of edge to this node is infinity (0 maps to INF in map)
            if(chr == '.'){
                graph[i][j].c = 0;

            // if node is B, then capacity of edge to this node is infinity (0 maps to INF in map)
            }else if(chr == 'B'){
                graph[i][j].c = 0;
                s = cnt;
                cout << "root: [" << i << "]["<< j << "] = " << s << "\n";

            // otherwise, the capacity maps to the alphabetical index (base 1, as 0 maps to infinity)
            }else{
                graph[i][j].c = chr - 'a' + 1;
            }
            // cout << "cnt = " << cnt << '\n';
            cnt ++;
        }
    }

    // map 0 to infinity    
    weights[0] = INF;
    for(ll i = 1; i <= c; i++){
        cin >> weights[i];
    }
    for(ll i = 0; i < n; i ++){
        for(ll j = 0; j <m; j ++){

            if(i - 1 < 0 || j - 1 < 0 || i + 1 >= n || j + 1 >= m){
                cout << "edge added: [" << i << "][" << j << "] - " <<"sink\n";
                network.add_edge(graph[i][j].v, t, INF);
            }
            if(i-1 >=0){
                cout << "edge added: [" << i << "][" << j << "] - " <<"[" << i-1 << "][" << j << "]\n";
                network.add_edge(graph[i][j].v, graph[i-1][j].v, weights[graph[i-1][j].c]);
            }
            if(j-1 >=0){
                cout << "edge added: [" << i << "][" << j << "] - " <<"[" << i << "][" << j-1 << "]\n";
                network.add_edge(graph[i][j].v, graph[i][j-1].v, weights[graph[i][j-1].c]);
            }
            if(i+1 <n){
                cout << "edge added: [" << i << "][" << j << "] - " <<"[" << i+1 << "][" << j << "]\n";
                network.add_edge(graph[i][j].v, graph[i+1][j].v, weights[graph[i+1][j].c]);
            }
            if(j+1 <m){
                cout << "edge added: [" << i << "][" << j << "] - " <<"[" << i << "][" << j+1 << "]\n";
                network.add_edge(graph[i][j].v, graph[i][j+1].v, weights[graph[i][j+1].c]);
            }
            
        }
    }
    ll res = network.dinic(s, t);
    if(res >= INF){
        res = -1;
    }
    cout << res << "\n";
}