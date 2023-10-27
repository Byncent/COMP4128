#include <iostream>
#include <utility>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <functional>

using namespace std;

typedef long long ll;
typedef pair<int, int> pint;

const int N = 1e3+7;

int n, m, temp;
priority_queue<pint, vector<pint>, greater<pint>> edges[N];  // Edges as pairs of (weight, vertex)

void add_edge(int u, int v, int w){
    edges[u].push(make_pair(w, v));
}

int main(){

    cin >> n;
    for(int i = 0; i < n; i ++){
        cin >> temp;
    }

    cin >> m;
    for(int i = 0; i < m; i ++){
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(v, u, w);
    }

    int weight = 0;
    int root = -1;
    for(int i = 1; i <= n; i ++){
        if(edges[i].empty()){
            if(root != -1 && root != i){
                cout << -1 << '\n';
                return 0;
            }
            root = i;
        }else{
            weight += edges[i].top().first;
        }
        
    }
    cout << weight << '\n';
    return 0;
}