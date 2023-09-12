#include <iostream>
using namespace std;
int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    int num;
    cin >> num;
    for(int i=0; i<num; i++){
    	int val1, val2;
    	cin >> val1;
    	cin >> val2;
    	cout << val1+val2 << '\n';
    }
    return 0;
}