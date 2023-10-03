#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>

using namespace std;
const long long MAX = 2147483647;

int main(){
    int n;
    long long k;
    cin >> n >> k;
    string s, t;
    cin >> s >> t;

    long long nodes = 1;
    long long res = 0;
    for(int i = 0; i < n; i++){
        nodes *= 2;
        
        if(s[i] == 'b'){
            nodes --;
        }
        if(t[i] == 'a'){
            nodes --;
        }

        nodes = min(MAX/2, nodes);

        res += min(nodes, k);
    }

    cout << res << '\n';

}