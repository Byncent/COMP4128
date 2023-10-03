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
        int found = art[0].find(sig[0]);

        while(found != -1){

            bool match = true;
            for(int j = 1; j <r1; j++){

                if(art[i+j].substr(found, c1) != sig[j]){
                    match = false;
                    break;
                }
            }

            if(match){
                cout << "Genuine\n";
                return 0;
            }
            found = art[i].find(sig[0], found + 1);
        }
    }
    cout << "Forgery\n";

    return 0;
}