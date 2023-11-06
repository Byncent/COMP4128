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
struct edge{
    int distance;
    int vertex;
    int type;

    // Overload the '<' operator
    bool operator<(edge const& other) const {
        if(distance == other.distance){
            return type < other.type;
        }else{
            return distance < other.distance;
        }
    }

    // Overload the '>' operator
    bool operator>(edge const& other) const {
        if(distance == other.distance){
            return type > other.type;
        }else{
            return distance > other.distance;
        }
    }
};

typedef struct edge Edge;

//Constants definition
const int N = 1e5+7;

// Global vars definition
int n = 0;
vector<edge> edges[N];
int dist[N];
bool seen[N];

priority_queue<edge, vector<edge>, greater<edge>> pq;

void dijkstra(int s) {
    Edge e;
    e.distance=0;
    e.vertex=s;
    e.type=CAR;

    pq.push(e);  // distance to itself is zero
    
    while (!pq.empty()) {
        // choose (d, v) so that d is minimal
        // i.e. the closest unvisited vertex
        edge cur = pq.top();
        pq.pop();
        int v = cur.vertex, d = cur.distance;
        
        if (seen[v])
            continue;
        dist[v] = d;
        seen[v] = true;
        
        // relax all edges from v
        for (edge nxt : edges[v]) {
            int u = nxt.vertex, weight = nxt.distance;
            if (!seen[u]){
                Edge new_edge;
                new_edge.distance = d + weight;
                new_edge.type = cur.type|nxt.type;
                new_edge.vertex = u;
                pq.push(new_edge);
            }
        }
    }
}


int main(){
    cin >> n;

    

    return 0;
}

