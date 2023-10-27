#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <functional>

using namespace std;

// Typedefs
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

//Constants definition
const int N = 1e5+7;

// Global vars definition
int n = 0;

void rec(int x){
    n++;
    cout << "x = " << x << ", n = " << n << '\n';
    if(x < 5){
        rec(x+1);
        rec(x+2);
    }

}


int main(){
    cin >> n;

    rec(0);

    return 0;
}