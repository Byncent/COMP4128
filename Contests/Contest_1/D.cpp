#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

const int maxn=1000;
int arr[maxn];
int diff[maxn];


int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        string str;
        cin >> str;
        arr[i] = stoi(str.substr(0, 2)) * 3600 + stoi(str.substr(3, 2)) * 60 + stoi(str.substr(6, 2));
    }

    for(int i = 0; i < n; i++){
        cin >> diff[i];
    }

    string res = "";
    int std;
    for(int i = 0; i < n; i++){
        std = arr[0] - diff[i];
        if(std<0) std +=86400;

        for(int j = 0; j < n; j++){
            int d = arr[j] - std;

            if(d < -43199){
                d += 86400;
            } else if(d > 43200) {
                d -= 86400;
            } 

            int idx = -1;

            for(int k = 0; k < n; k++){

                if(diff[k] == d){
                    idx = k;
                    break;
                }

            }

            if(idx == -1){
                res = "";
                break;
            }

            res += " " + to_string(idx + 1);
        }

        if(res != ""){
            break;
        }
    }

    if(res == ""){
        cout << "Impossible\n";
    } else{
        cout << res.substr(1) << "\n";
    }
    
    return 0;
}