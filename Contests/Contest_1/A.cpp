#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    
    vector<string> sig;
    vector<string> art;

    for(int i = 0; i < r1; i++){
        string txt;
        cin >> txt;
        sig.push_back(txt);
    }

    for(int i = 0; i < r2; i++){
        string txt;
        cin >> txt;
        art.push_back(txt);
    }
    
    for(int i = 0; i <= r2-r1; i++){
        for(int j = 0; j <= c2 - c1; j++ ){
            bool flag = true;
            for(int k = 0; k < r1; k ++){
                if(art[i+k].substr(j,c1) != sig[k]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                cout << "Genuine\n";
                return 0;
            }
        }
    }
    cout << "Forgery\n";

    return 0;
}