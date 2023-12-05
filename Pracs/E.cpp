#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

#define CAKE 0
#define IC 1

typedef long long ll;

int n;
int k;
const int N = 20010;

int score[2][N];
int dp[N][2][N];


int main(){

    cin >> n >> k;

    for(int i = 1; i <= n;  i++){
        cin >> score[CAKE][i];
    }
    for(int i = 1; i <= n;  i++){
        cin >> score[IC][i];
    }

    for(int i = 0; i <= n; i ++){
        dp[i][CAKE][0] = 0;
        dp[i][IC][0] = 0;
    }

    for(int j = 0; j <= k; j ++){
        dp[0][CAKE][j] = 0;
        dp[0][IC][j] = 0;
    }

    for(int x = 1; x <=n; x ++){
        for(int y = 0; y <2; y ++){
            for(int z = 1; z <=k; z ++){
                if(z == 1){
                    int maxval = 0;
                    for(int u =1; u <=k; u ++){
                        maxval = max(maxval, dp[x-1][y^1][u]);
                    }
                    dp[x][y][z] = maxval + score[y][x];
                }else{
                    dp[x][y][z] = dp[x-1][y][z-1]+score[y][x];
                }
            }
        }
    }
    
    int res = 0;

    for(int i = 1; i <= k; i++){
        res = max(res, dp[n][IC][i]);
        res = max(res, dp[n][CAKE][i]);
    }

    cout << res << '\n';
    return 0;

}