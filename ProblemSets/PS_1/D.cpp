#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1e6+5;
int total[N], above[N];

int main(){

    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    int size;
    long long int sum = 0;
    cin >> size;

    for(int i = 1; i < size + 1; i ++){
        int val;
        cin >> val;
        above[i] = val + 1;
        total[i] = max(total[i-1], above[i]);
    }

    for(int i = size; i > 0; i --){
        if(total[i] - total[i-1] > 1){
            total[i-1] = total[i] - 1;
        }
        sum += total[i] - above[i];
    }

    cout << sum << '\n';

    return 0;

}