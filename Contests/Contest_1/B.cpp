#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int board[300][300];

bool checkWon(int player, int n, int k, int col, int row){

    int i, j;

    // horizontal
    for(i = 0; row - i > 0; i ++){
        if(board[col][row - i - 1] != player){
            break;
        }
    }

    for(j = 0; row + j < n; j ++){
        if(board[col][row + j + 1] != player){
            break;
        }
    }

    if(i+j >= k - 1){
        return true;
    }

    // vertical
    for(i = 0; col - i > 0; i ++){
        if(board[col - i - 1][row] != player){
            break;
        }
    }

    for(j = 0; col + j < n; j ++){
        if(board[col + j + 1][row] != player){
            break;
        }
    }

    if(i+j >= k - 1){
        return true;
    }

    // top-left to bot-right diagonal
    for(i = 0; row - i > 0 && col - i > 0; i ++){
        if(board[col - i - 1][row - i - 1] != player){
            break;
        }
    }

    for(j = 0; row + j < n && col + j < n; j ++){
        if(board[col + j + 1][row + j + 1] != player){
            break;
        }
    }

    if(i+j >= k - 1){
        return true;
    }

    // top-right to bot-left diagonal
    for(i = 0;  row + i < n && col - i > 0; i ++){
        if(board[col - i - 1][row + i + 1] != player){
            break;
        }
    }

    for(j = 0; row - j > 0 && col + j < n; j ++){
        if(board[col + j + 1][row - j - 1] != player){
            break;
        }
    }

    if(i+j >= k - 1){
        return true;
    }
    return false;
}

int main() {

    int n, m, k;
    string res = "No winner\n";
    int player = -1;

    cin >> n >> m >> k;

    for(int i = 0; i < m; i ++){
        player = -1 * player;

        int col, row;
        cin >> col;
        col --;
        for(row = 0; row < n; row ++){
            if(board[col][row] != 0){
                board[col][row-1] = player;
                break;
            }
        }

        if (row == n){
            board[col][n-1] = player;
        }

        if(checkWon(player, n, k, col, row-1)){
            if(res == "No winner\n"){
                if(player == 1){
                    res =  "Ayumi ";
                } else {
                    res = "Bunji ";
                }
                res += to_string( i+1) + '\n';
            }
        }
 
    }
    cout << res;
}