#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>

typedef long long ll;
using namespace std;

const ll N = 110;
//if the colour of a grid is 0, then it is uncoloured
const ll uncoloured = 0;
//define infinity to be a big numbere
const ll INF = 1e12+7;

// treee[i]: The colour of the ith tree
ll trees[N];

// cost[i][j]: Cost to colour the ith tree with colour j. If the ith tree is alredy coloured, then the cost is 0.
ll costs[N][N];

//dp[i][j][k]: Minimum cost of coloring the ith tree with colour j with total beauty score being k
ll dp[N][N][N];

// n: Number of trees 
ll nTrees;
// m: Number of colours
ll nColours;
// k: Beauty score required
ll nScores;

int main(){
    cin >> nTrees >> nColours >> nScores;

    // record the colour of each tree
    for(ll i = 1; i <= nTrees; i ++){
        cin >> trees[i];
    }

    // record the cost to colour the ith tree with colour j. If it is already coloured, then the cost is 0.
    for(ll i = 1; i <= nTrees; i ++){
        for(ll j = 1; j <= nColours; j++){
            ll val;
            cin >> val;
            if(trees[i] == uncoloured) costs[i][j] = val;
            else costs[i][j] = 0;
        }
    }
    for(ll i = 1; i <= nTrees; i ++){
        for(ll j = 1; j <= nColours; j++){
            for(ll k = 0; k <= nScores; k++){
                if(k == 0){
                    dp[i][j][k] = INF;
                    continue;
                }
                if(trees[i]!=j && trees[i] != uncoloured){
                    dp[i][j][k] = INF;
                    continue;
                }
                if( i == 1){
                    if(k == 1){
                        dp[1][j][k] = costs[1][j];
                    } else{
                        dp[1][j][k] = INF;
                    }
                    continue;
                }
            }
        }
    }


    for(ll i = 2; i <= nTrees; i++){
        for(ll k = 1; k <= nScores; k++){
            for(ll j = 1; j <= nColours; j++){
                ll val = INF;
                for(int p = 1; p <= nColours; p++){
                    val = min(val, dp[i-1][p][k-(p != j)]);
                }
                dp[i][j][k] = max(dp[i][j][k], val + costs[i][j]);
            }
        }
    }

    ll sol = INF;
    for(ll j = 1; j <= nColours; j ++){
        sol = min(sol, dp[nTrees][j][nScores]);
    }

    if(sol >= INF){
        sol = -1;
    }

    for(int i = 1; i <= nTrees; i ++){
        for(int j = 1; j <= nColours; j ++){
            for(int k = 1; k <= nScores; k++){
                cout << "dp[" << i << "][" << j << "][" << k << "] = " << dp[i][j][k] << '\n'; 
            }
        }
    }

    cout << sol << '\n';
}
