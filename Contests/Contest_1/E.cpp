#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int door[100][3];
int coins[23];

bool determine(int m, int max){

    if(m == max){
        return true;
    }

    if(coins[abs(door[m][0])] == door[m][0] || coins[abs(door[m][1])] == door[m][1] || coins[abs(door[m][2])] == door[m][2]){
        return determine(m+1, max);
    } else{

        int i;
        for(i = 0; i < 3; i ++){
            if(coins[abs(door[m][i])] == 0){
                coins[abs(door[m][i])] = door[m][i];
                if(determine(m+1, max)){
                    return true;
                } else{
                    coins[abs(door[m][i])] = 0;
                };
            }
        }
        return false;
    }
}

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    if(m == 0){
        for(int i = 0; i < n; i ++){
            cout << "H "; 
        }
        cout << '\n';
        return 0;
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < 3; j++){
            cin >> door[i][j];
        }
    }

    if(determine(0, m)){
        for(int i = 1; i <= n; i ++){
            if(coins[i] < 0){
                cout << "T ";
            } else{
                cout << "H ";
            }
        }

        cout << '\n';
        return 0;
    }

    cout << "Doomed\n";
    return 0;

}