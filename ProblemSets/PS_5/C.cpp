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
ll n;
ll dist[N][N];
vector<edge> edges;
vector<ll> vertices;
vector<ll> res;

void fw(){
    for (ll i = n-1; i >=0; i--){
        ll s = 0;
        ll vi = vertices[i];
        for (ll u = 0; u < n; u ++){
            for (ll v = 0; v < n; v++){
                // dist[u][v] is the length of the shortest path from u to v using only 0 to i-1 as llermediate vertices
                // now that we're allowed to also use i, the only new path that could be shorter is u -> i -> v
                
                // cout << "dist["<<u <<"][" <<v << "]"  << "= min(" <<"dist["<<u<<"]["<<v<<"] = "<< dist[u][v] << ", " << "dist["<<u<<"]["<<i<< "] = " << dist[u][i]<<  " + "  << "dist[" << i << "][" << v <<"] = "<< dist[i][v] <<") = " << min(dist[u][v], dist[u][i] + dist[i][v]) << "\n";
                ll vu = vertices[u], vv = vertices[v];
                dist[vu][vv] = min(dist[vu][vv], dist[vu][vi] + dist[vi][vv]);
                if(u >=i && v >=i ){
                    s += dist[vu][vv];
                }
                // cout << "confirm: " << "dist["<< u <<"]["<<v << "] = " <<  dist[u][v] << "\n";
            }
        }
        res.push_back(s);
    }
}

int main(){
    cin >> n;

    for(ll i = 0; i < n; i ++){
        for(ll j = 0; j < n; j ++){
            cin >> dist[i][j];
        }
    }

    for(ll i = 0; i < n; i ++){
        ll v;
        cin >> v;
        vertices.push_back(v-1);
    }

    fw();

    for(ll i = n-1; i >=0; i --){
        cout << res[i] << ' ';
    }
    cout << '\n';
    return 0;
}