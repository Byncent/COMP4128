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

// Hash defines
#define TRUE 0
#define FALSE 1

// Typedefs
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// Constants definition
const int N = 1e5+7;

// Global vars definition
int n, m;
vector<int> finals;

int main(){
    cin >> n >> m;

    int s = 0;
    for(int i = 0;  i< n;  i++){
        int a;
        cin >> a;
        s += a;
    }

    cout << (s - m*n)/m << '\n';

    return 0;
}