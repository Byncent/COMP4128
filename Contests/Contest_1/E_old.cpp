#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int door[100][3];
int coins[23];


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


    for(int i = 0; i < 3; i ++){

        //init array of coins
        for(int l = 0; l < 23; l ++){
            coins[l] = 0;
        }
        coins[abs(door[0][i])] = door[0][i];
        // cout << "if row 1 is coin " << door[0][k] << ": \n";

        // if a valid scheme has been found
        bool found = false;

        // iterate over every row
        for(int i = 0; i < m; i++){
            found = false;
            for(int j = 0; j < 3; j++){
                if(coins[abs(door[i][j])] == door[i][j]){
                    found = true;
                    // cout << "row " << i+1 << ": " << door[i][j] << ": \n";
                    break;
                }
            }

            if(!found){
                for(int k = 0; k < 3; k ++){
                    if(coins[abs(door[i][k])] == 0){
                        // cout << "row " << i+1 << ": " << door[i][j] << ": \n";
                        coins[abs(door[i][k])] = door[i][k];
                        found = true;
                        break;
                    }
                }

                if(!found){
                    break;
                }
            }
        }

        if(found){
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
    }



    cout << "Doomed\n";
    return 0;
}