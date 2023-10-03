#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
    
    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    string val, res;
    int iter;
    int counter = 0;

    cin >> val >> iter;
    
    for(int i = 0; i < iter - 1; i++){
        string str = "";
        
        str += val[0];

        for(int j = 0; j < val.length() - 1; j++){
            if(val[j+1] == val[j]){
                str += val[j+1];
            }else{
                res += to_string(str.length());
                res += str[0];
                str = "";
                str += val[j+1];
            }
            
            
        }
        res += to_string(str.length());
        res += str[0];

        val = res;
        res = "";
    }
    cout << val << '\n';
    return 0;
}