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
int arr[N];
vector<int> leaves;

// Global vars definition
int n, u, v;


int main(){
    cin >> n;
    for(int i = 1; i < n; i ++){
        cin >> u >> v;
        arr[u] ++;
        arr[v] ++;
    }

    int root_idx = 0;
    int root_count = 0;
    int root_counter = 0;
    for(int i = 1; i <= n; i ++){
        if(arr[i] > 2){
            root_counter ++;
        }
        if(arr[i] > root_count){
            root_count = arr[i];
            root_idx = i;
        }
    }

    if(root_counter >1){
        cout << "No" << '\n';
        return 0;
    }

    for(int i = 1; i <= n; i ++){
        if(arr[i] == 1 && i != root_idx){
            leaves.push_back(i);
        }
    }

    cout << "Yes\n";
    cout << leaves.size() << '\n';
    
    for(int leaf : leaves){
        cout << root_idx << ' ' << leaf << '\n';
    }
    
    return 0;
}