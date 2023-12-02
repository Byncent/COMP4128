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

// hypedefs
typedef long long ll;
typedef pair<ll, ll> pll;

// Constants definition
const int N = 1e7+7;

vector<int> edges[N];
// dist from start. -1 if unreachable.
int dist[N];
// previous node on a shortest path to the start
// Useful for reconstructing shortest paths
int prev_node[N];

void bfs(int start) {
    fill(dist, dist+N, -1);
    dist[start] = 0;
    prev_node[start] = -1;

    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        for (int nxt : edges[c]) {
            // Push if we have not seen it already.
            if (dist[nxt] == -1) {
                dist[nxt] = dist[c] + 1;
                prev_node[nxt] = c;
                q.push(nxt);
            }
        }
    }
}


int n, r, sx, sy, hx, hy;

int G[N];
set<int> cols_rocks[N];
set<int> rows_rocks[N];

int get_idx(int x, int y){
    return n * (y-1) + x;
}

int main(){
    cin >> n >> r >> sy >> sx >> hy >> hx;
    
    for(int i = 1; i <= n; i ++){
        cols_rocks[i].insert(0);
        cols_rocks[i].insert(n+1);
        cols_rocks[i].insert(-n-1);
        rows_rocks[i].insert(0);
        rows_rocks[i].insert(n+1);
        rows_rocks[i].insert(-n-1);
    }

    for(int i = 0; i < r; i ++){
        int x, y;
        cin >> y >> x;
        cols_rocks[x].insert(y);
        cols_rocks[x].insert(-y);
        rows_rocks[y].insert(x);
        rows_rocks[y].insert(-x);
    }

    for(int y = 1; y <= n; y ++){
        for(int x = 1; x <= n; x ++){

            // if this is not a rock
            if(rows_rocks[y].find(x) == rows_rocks[y].end()){

                int u_end = -*(cols_rocks[x].upper_bound(-y)) + 1;
                int d_end = *(cols_rocks[x].upper_bound(y)) - 1;
                int l_end = -*(rows_rocks[y].upper_bound(-x)) + 1;
                int r_end = *(rows_rocks[y].upper_bound(x)) - 1;
                int idx = get_idx(x, y);
                int u_idx = get_idx(x, u_end);
                int d_idx = get_idx(x, d_end);
                int l_idx = get_idx(l_end, y);
                int r_idx = get_idx(r_end, y);

                edges[idx].push_back(u_idx);
                edges[idx].push_back(d_idx);
                edges[idx].push_back(l_idx);
                edges[idx].push_back(r_idx);
                // cout << "cell: (" << y << ", " << x << ") 's l_end = " << l_end << ", r_end = " << r_end << ", u_end = " << u_end << ", d_end = " << d_end << ", idx = " << idx << '\n'; 
            }
        }
    }

    int honey_l = -*(rows_rocks[hy].upper_bound(-hx));
    int honey_r = *(rows_rocks[hy].upper_bound(hx));
    int honey_u = -*(cols_rocks[hx].upper_bound(-hy));
    int honey_d = *(cols_rocks[hx].upper_bound(hy));

    int honey = get_idx(hx, hy);

    for(int i = honey_l + 1; i < honey_r; i ++){
        edges[get_idx(i, hy)].push_back(honey);
    }

    for(int i = honey_u + 1; i < honey_d; i ++){
        edges[get_idx(hx, i)].push_back(honey);
    }

    bfs(get_idx(sx, sy));

    int res = dist[honey];
    if(res == -1){
        res = 0;
    }

    cout << res << '\n';

    return 0;
}