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

// Typedefs
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef struct edge{
    ll u;
    ll v;
    ll w;

    // Overload the '<' operator
    bool operator<(edge const& other) const {
        return w < other.w;
    }

    // Overload the '>' operator
    bool operator>(edge const& other) const {
        return w > other.w;
    }
} edge;

// Constants definition
const ll N = 1e3+7;
const ll INF = 1e15+10;

// Global vars definition
int n;
ll graph[N][N];
ll dist[N][N];
vector<edge> edges;
vector<int> vertices;
vector<int> res;

int fw(){
    // the distance between everything is infinity
    for (int u = 0; u < n; ++u){
        for (int v = 0; v < n; ++v){
            dist[u][v] = INF;
        }
    }

    // update the distances for every directed edge
    for (edge e : edges){
        // each edge u -> v with weight w
        dist[e.u][e.v] = e.w;
        // cout << "dist[" << e.u << "][" << e.v << "]" << " = " <<dist[e.u][e.v] << '\n';
    }

    // every vertex can reach itself
    for (int u = 0; u < n; ++u){
        dist[u][u] = 0;
    }

    int s = 0;
    for (int i = 0; i < n; i++){
        s = 0;
        for (int u = 0; u < n; u++){
            for (int v = 0; v < n; v++){
                // dist[u][v] is the length of the shortest path from u to v using only 0 to i-1 as intermediate vertices
                // now that we're allowed to also use i, the only new path that could be shorter is u -> i -> v
                
                // cout << "dist["<<u <<"][" <<v << "]"  << "= min(" <<"dist["<<u<<"]["<<v<<"] = "<< dist[u][v] << ", " << "dist["<<u<<"]["<<i<< "] = " << dist[u][i]<<  " + "  << "dist[" << i << "][" << v <<"] = "<< dist[i][v] <<") = " << min(dist[u][v], dist[u][i] + dist[i][v]) << "\n";
                dist[u][v] = min(dist[u][v], dist[u][i] + dist[i][v]);
                if(dist[u][v] < INF && i == n-1){
                    s += dist[u][v];
                }
                // cout << "confirm: " << "dist["<< u <<"]["<<v << "] = " <<  dist[u][v] << "\n";
            }
        }
    }
    return s;
}

int main(){
    cin >> n;

    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            cin >> graph[i][j];
        }
    }

    for(int i = 0; i < n; i ++){
        int v;
        cin >> v;
        vertices.push_back(v-1);
    }

    for(int i = n-1; i >= 0 ; i --){
        // cout << "i = " << i << '\n';
        for(int j = n-1; j > i; j --){
            // cout << "j = " << j << '\n';
            edges.push_back(edge{vertices[i], vertices[j], graph[vertices[i]][vertices[j]]});
            edges.push_back(edge{vertices[j], vertices[i], graph[vertices[j]][vertices[i]]});
        }

        // cout << "running fw: \n";
        res.push_back(fw());
        // cout << "finished with fw. \n";
        // int s = 0;
        // for(int i = 0; i < n; i ++){
        //     for(int j = 0; j < n; j ++){
        //         if(dist[i][j] < INF){
        //             s += dist[i][j];
        //             // cout << "dist[" << i << "][" <<j <<"] = " << dist[i][j] << " is added\n";
        //         }
        //     }
        // }
        // res.push_back(s);
    }

    for(int i = n-1; i >=0; i --){
        cout << res[i] << ' ';
    }
    cout << '\n';
    return 0;
}