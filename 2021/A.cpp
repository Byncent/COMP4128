#include <bits/stdc++.h>

using namespace std;

int n;
map<int, int> m;

int main(){
    cin >> n;

    for(int i = 0; i < n; i ++){
        int val;
        cin >> val;
        m[val] ++;
    }

    int res = 0;
    for(auto it : m){
        if(it.first == it.second){
            res = max(res, it.first);
        } 
    }

    cout << res << '\n';
}