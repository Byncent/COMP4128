#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){

    string s;
    string t = "", u = "";
    
    cin >> s;

    t += s[0];
    s = s.substr(1, s.length() - 1);

    while(s != ""){
        // finding idx of minimum character
        int idx = 0;
        for (int i = 0; i < s.length(); i++)   
            if (s[i] < s[idx])
                idx = i;


        if (s[idx] < t[t.length() - 1]){

            t += s.substr(0, idx);
            u += s[idx];
            s = s.substr(idx+1, s.length() - idx - 1);
        }else{
            u += t[t.length() - 1];
            t = t.substr(0, t.length() - 1);

            if(t == ""){
                t += s[0];
                s = s.substr(1, s.length() - 1);
            }
        }
    }

    reverse(t.begin(), t.end());
    u += t;
    cout << u << '\n';
    return 0;
}