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

#define LEFT 0
#define RIGHT 1

// Typedefs
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Structs
typedef struct Edge{
    int coord;
    int steps;
} Edge;

//Constants definition
const int N = 1e6+7;

// Global vars definition
int n, k;
vector<Edge> edges[N];
int dist[N];  // dist from start, -1 if unreachable.
int prevNode[N];  // previous node on a shortest path to the start, useful for reconstructing shortest paths.

void bfs() {
    fill(dist, dist + N, -1);

    dist[0] = 0;
    prevNode[0] = -1;

    queue<Edge> q;
    Edge start;
    start.coord = 0;
    start.steps = 0;
    q.push(start);
    
    while (!q.empty()) {
        Edge edge = q.front();
        q.pop();
        
        for (Edge e : edges[edge.coord]) {
            e.steps = edge.steps +1;

            if(e.steps > e.coord/2){
                continue;
            } 
            
            // Push if we have not seen it already.
            if (dist[e.coord] == -1) {
                dist[e.coord] = dist[edge.coord] + 1;
                prevNode[e.coord] = edge.coord;
                q.push(e);
            }
        }
    }
}

void add_edge(int pos, int height, int from, int to){
    Edge e;
    e.coord = min(height, n)*2+to;
    e.steps = 0;
    edges[min(pos, n)*2+from].push_back(e);
}

int main(){
    cin >> n >> k;
    string left, right;

    cin >> left >> right;

    //destination
    left += '-';
    right += '-';

    for(int i = 0; i < n; i ++){
        if (left[i] == '-'){
            // move up/down
            if(i <n && left[i+1] == '-'){
                add_edge(i, i+1, LEFT, LEFT);
                add_edge(i+1, i, LEFT, LEFT);
            }

            // jump up by k
            if (right[min(i+k, n)] == '-'){
                add_edge(i, i+k, LEFT, RIGHT);
            }
        }

        if (right[i] == '-'){
            // move up/down
            if(i <n && right[i+1] == '-'){
                add_edge(i, i+1, RIGHT, RIGHT);
                add_edge(i+1, i, RIGHT, RIGHT);
            }

            // jump up by k
            if (left[min(i+k, n)] == '-'){
                add_edge(i, i+k, RIGHT, LEFT);
            }
        }
    }
    bfs();


    if(dist[2*n]!= -1 || dist[2*n+1]!=-1 ){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
    return 0;
}