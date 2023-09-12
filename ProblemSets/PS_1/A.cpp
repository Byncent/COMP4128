#include <iostream>
#include <string>

using namespace std;
int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    int num;
    cin >> num;
    for(int i=0; i<num; i++){
    	string val;
    	cin >> val;
        if (val != to_string(i+1) && val != "mumble"){
            cout << "something is fishy\n";
            return 0;
        }
    }
    cout << "makes sense\n";
    return 0;
}