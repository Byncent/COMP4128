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
    ll n;
    vector<vector<ll> > adjMat, adjList;
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

/*
 * dinic 2
 */

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


int main(){
    ll cases;
    cin >> cases;
    for(ll i = 1; i <= cases; i ++){
        ll n;
        cin >> n;
        FlowNetwork network(n*n + 2);
        ll graph[1000][1000];
        // index of the nodes, 0 is the source and n*n + 1 is the sink
        ll idx = 1;

        for(ll j = 0; j < n; j ++){
            for(ll k = 0; k < n; k ++){

                char cell;
                cin >> cell;

                if(cell == '#'){
                    graph[j][k] = idx++;
                }else{
                    graph[j][k] = 0;
                }
                
                // if has oil
                if(graph[j][k]!=0){
                    //
                    if((j+k)%2 == 0){

                        // cout << "edge: " << 0 << " - " << graph[j][k] << " = " << 1 << "\n";
                        network.add_edge(0, graph[j][k], 1);
                        if(j-1 >= 0 && graph[j-1][k]!=0){

                            // cout << "edge: " << graph[j][k] << " - " << graph[j-1][k]<< " = " << 1 << "\n";
                            network.add_edge(graph[j][k], graph[j-1][k], 1);
                        }
                        if(k-1 >= 0 && graph[j][k-1]!=0){

                            // cout << "edge: " << graph[j][k] << " - " << graph[j][k-1]<< " = " << 1 << "\n";
                            network.add_edge(graph[j][k], graph[j][k-1], 1);
                        }
                    }else{

                        // cout << "edge: " << graph[j][k] << " - " << n*n+1 << " = " << 1 << "\n";
                        network.add_edge(graph[j][k], n*n+1, 1);
                        // cout << "j-1 = " << j-1 << '\n';
                        // cout << "graph[j-1][k]" << graph[j-1][k] << '\n';
                        if(j-1 >= 0 && graph[j-1][k]!=0){

                            // cout << "edge: " << graph[j-1][k] << " - " << graph[j][k] << " = " << 1<< "\n";
                            network.add_edge(graph[j-1][k], graph[j][k], 1);
                        }
                        if(k-1 >= 0 && graph[j][k-1]!=0){

                            // cout << "edge: " << graph[j][k-1] << " - " <<graph[j][k] << " = " << 1 << "\n";
                            network.add_edge(graph[j][k-1], graph[j][k], 1);
                        }
                    }
                }
            }
        }

        ll res = network.dinic(0, n*n+1);
        cout << "Case "<< i << ": "<<res << '\n';
    }
}