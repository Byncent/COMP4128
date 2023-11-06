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

// Typedefs
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

//Constants definition
const int N = 1e5+7;

// Global vars definition
int n, k;
vector<int> edges[N];
int dist[N];  // dist from start, -1 if unreachable.
int prevNode[N];  // previous node on a shortest path to the start, useful for reconstructing shortest paths.

void bfs(int start) {
    fill(dist, dist + N, -1);
    dist[start] = 0;
    prevNode[start] = -1;
    
    queue<int> q;
    q.push(start);
    
    int lv = 0;
    while (!q.empty()) {
        int c = q.front();
        q.pop();
        
        for (int nxt : edges[c]) {

            string edge1;
            string edge2;
            if(c%2 == 0){
                edge1 = "left";
            }else {
                edge1 = "right";
            }

            if(nxt%2 == 0){
                edge2 = "left";
            }else {
                edge2 = "right";
            }

            cout << edge1 << " " << c/2 << " - " <<edge2 << " " << nxt/2;
            if (nxt/2 <= lv){
                cout << " NOT added, level = " << lv << '\n';
                continue;
            }
            cout << " added, lv = " << lv << '\n';
            // Push if we have not seen it already.
            if (dist[nxt] == -1) {
                dist[nxt] = dist[c] + 1;
                prevNode[nxt] = c;
                q.push(nxt);
            }
        }
        lv ++;
    }
}



int main(){
    cin >> n >> k;
    string left, right;

    cin >> left >> right;

    //destination
    left += '-';
    right += '-';

    cout << "left[n]: " << left[n] << '\n';

    for(int i = 0; i < n; i ++){
        if (left[i] == '-'){

            // move up/down
            if(i <n && left[i+1] == '-'){
                edges[i*2].push_back((i+1)*2);
                edges[(i+1)*2].push_back(i*2);
            }

            // jump up by k
            if (right[min(i+k, n)] == '-'){
                edges[i*2].push_back(min(i+k, n)*2 + 1);
            }

        }

        if (right[i] == '-'){

            // move up/down
            if(i <n && right[i+1] == '-'){
                edges[i*2+1].push_back((i+1)*2+1);
                edges[(i+1)*2+1].push_back(i*2+1);
            }

            // jump up by k
            if (left[min(i+k, n)] == '-'){
                edges[i*2+1].push_back(min(i+k, n)*2);
            }
        }
    }
    
    for(int i = 0 ; i <= n*2; i ++){
        for ( int edge : edges[i]){
            string edge1;
            string edge2;
            if(i%2 == 0){
                edge1 = "left";
            }else {
                edge1 = "right";
            }

            if(edge%2 == 0){
                edge2 = "left";
            }else {
                edge2 = "right";
            }

            cout << edge1 << " " << i/2 << " - " <<edge2 << " " << edge/2 <<'\n';
        }
    }


    bfs(0);
    cout << dist[n];
    return 0;
}