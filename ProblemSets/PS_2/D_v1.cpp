#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <functional>

typedef long long ll;
using namespace std;

const ll N = 1e5+7;

ll n, m, s;
vector<ll> bugs;
pair<ll, ll> vStudents[N];
multiset<pair<ll, ll>> sStudents;


ll binarySearch(function<bool(ll)> f);
bool check(ll days);
multiset<pair<ll, ll>>::iterator findCheapest(multiset<pair<ll, ll>> mset, ll lv);

int main(){

    cin >> n >> m >> s;

    ll difficultyMax = 0;
    for(ll i = 0; i < m; i++){
        ll difficulty;
        cin >> difficulty;
        bugs.push_back(difficulty);
        difficultyMax = max(difficulty, difficultyMax);
    }

    sort(bugs.begin(), bugs.end(), greater<ll>()); 

    ll abilityMax = 0;
    for(ll i = 0; i < n; i++){
        ll ability;
        cin >> ability;
        vStudents[i].first = ability;
        abilityMax = max(ability, abilityMax);
    }

    if(difficultyMax > abilityMax){
        cout << "NO\n";
        return 0;
    }

    for(ll i = 0; i < n; i++){
        cin >> vStudents[i].second;
    }
    
    for(ll i = 0; i < n; i++){
        sStudents.insert({vStudents[i]});
    }

    ll days = binarySearch(&check);
    
    cout << days;
}

bool check(ll days){
    multiset<pair<ll, ll>> temp(sStudents);
    ll passes = s;
    ll bugCount = 0;

    while(passes>=0 && bugCount < n){
        auto it = temp.lower_bound({bugs[bugCount], 0});
        if(it == temp.end()) return false;

        auto cheapest = findCheapest(temp, it->first);
        passes -= cheapest->second;
        bugCount += days;
        temp.erase(cheapest);
        
    }

    if(passes<0){
        return false;
    }
    return true;
}

multiset<pair<ll, ll>>::iterator findCheapest(multiset<pair<ll, ll>> mset, ll lv){

    auto it = mset.lower_bound({lv, 0});
    auto minPass = it;

    while(it != mset.end()){
        if (it->second < minPass->second){
            minPass = it;
        }
        it ++;
    }
    return minPass;
}


ll binarySearch(function<bool(ll)> f) {
    ll lo = 0;
    ll hi = n;
    ll bestSoFar = -1;

    // Range [lo, hi];
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (f(mid)) {
            bestSoFar = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    return bestSoFar;
}

