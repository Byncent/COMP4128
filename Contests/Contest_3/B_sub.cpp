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

// Constants definition
const int N = 10;

// Global vars definition
int n, r, s;
int garden[N][N];
int layouts[N][N][N];

// cost of decorating garden[i][j] with plant k
int dp(int i, int j){
    int layouts[N][N][N];
    if(j-1 < 0){

    }
    if(garden[i][j])
}


int main(){
    cin >> n >> r >> s;

    vector<int> sols;

    int all_reg = 0;

    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            char chr;
            cin >> chr;
            if(chr == '*'){
                garden[i][j] = -1;
            }else{
                garden[i][j] = 0;
            }
        }
    }



    for(int i = 0; i < n; i ++){

    }

    return 0;
}

