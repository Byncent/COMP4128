#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

const int N = 100000;
char minArr[N];

int main(){

    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    string s, u = "";
    stack <char> t;
    cin >> s;

    char currMin = 'z';
    for(int i = s.length() - 1; i>=0; i--){
        if(s[i] < currMin){
            minArr[i] = s[i];
            currMin = s[i];
        }else{
            minArr[i] = currMin;
        }
    }

    int i = 0;

    while(i < s.length()){
        if(t.empty()){
            t.push(s[i]);
            i++;
            continue;
        }

        if(t.top() <= minArr[i]){
            u += t.top();
            t.pop();
        } else{
            t.push(s[i]);
            i ++;
        }
    }

    while(!t.empty()){
        u += t.top();
        t.pop();
    }
    cout << u << '\n';
    return 0;
}