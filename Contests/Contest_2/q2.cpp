#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>


typedef long long ll;
using namespace std;

const int N = 1e4;

int m;
int n;
int k;

int dist[N][N];


int main(){

    string res = "";
    cin >> m >> n >> k;

    for(int i = 0; i < k; i ++){
        int xCoord, yCoord;
        cin >> yCoord >> xCoord;
        dist[yCoord][xCoord] = 1;

        int north = 1;
        int south = 1;
        int west = 1;
        int east = 1;
        for(; yCoord-north > 0; north++){
            if(dist[yCoord+north][xCoord] == 1){
                break;
            }
        }
        for(; yCoord+south < m; south ++){
            if(dist[yCoord+south][xCoord] == 1){
                break;
            }
        }

        for(; xCoord-west > 0; west++){
            if(dist[yCoord][xCoord+west] == 1){
                break;
            }
        }

        for(; xCoord+east < n; east ++){
            if(dist[yCoord][xCoord+east] == 1){
                break;
            }
        }
        cout << "N: " << north << '\n';
        cout << "E: " << east << '\n';
        cout << "S: " << south << '\n';
        cout << "W: " << west << '\n';
        res += to_string(max(max(north, south), max(west, east)));
        res += '\n';

    }

    cout << res;
    return 0;
}