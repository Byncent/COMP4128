#include <iostream>
#include <string>
#include <cmath>
#include <map>
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



// Global vars definition
set<pii> s;

int main(){
    s.insert(make_pair(1, 2));
    s.insert(make_pair(1, 2));

    for(set<pii> :: iterator it = s.begin(); it != s.end(); it ++ ){
        cout << (*it).first << '\n';
        cout << (*it).second << '\n'; 
    }

    return 0;
}