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
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef struct Edge{
    int distance;
    int vertex;
    int type;

    // Overload the '<' operator
    bool operator<(Edge const& other) const {
        if(distance == other.distance){
            return type < other.type;
        }else{
            return distance < other.distance;
        }
    }

    // Overload the '>' operator
    bool operator>(Edge const& other) const {
        if(distance == other.distance){
            return type > other.type;
        }else{
            return distance > other.distance;
        }
    }
} Edge;

//Constants definition
const int N = 1e6+7;

// Global vars definition
int n, m, k;
vector<Edge> edges[N];
int dist[N];
bool seen[N];

priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

int dijkstra(int s) {
    int c = 0;
    Edge e;
    e.distance=0;
    e.vertex=s;
    e.type=CAR;

    pq.push(e);  // distance to itself is zero
    
    while (!pq.empty()) {
        // choose (d, v) so that d is minimal
        // i.e. the closest unvisited vertex
        Edge cur = pq.top();
        pq.pop();
        int v = cur.vertex, d = cur.distance;
        
        if (seen[v]){
            cout << "hi\n";
            if(cur.type == TRAIN){
                c ++;
            }
            continue;
        }
            
        dist[v] = d;
        seen[v] = true;
        
        // relax all edges from v
        for (Edge nxt : edges[v]) {
            int u = nxt.vertex, weight = nxt.distance;
            if (!seen[u]){
                Edge new_edge = {d + weight, u, cur.type|nxt.type};
                pq.push(new_edge);
            }else{
                cout << "hello\n";
                if(nxt.type == TRAIN){
                    c ++;
                }
            }
        }
    }
    return c;
}


int main(){
    cin >> n >> m >> k;

    for(int i = 0; i < m; i ++){
        int u, v, x;
        cin >> u >> v >> x;

        Edge e1 = {v, x, CAR};
        Edge e2 = {u, x, CAR};
        edges[u].push_back(e1);
        edges[v].push_back(e2);
    }

    for(int i = 0; i < k; i ++){
        int s, y;
        cin >> s >> y;

        Edge e = {s, y, TRAIN};
        edges[1].push_back(e);
    }

    int res = dijkstra(1);
    cout << res << '\n';

    return 0;
}

