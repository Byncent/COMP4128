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

ll cmp(pair<ll, pair<ll, ll>> a, pair<ll, pair<ll, ll>> b);
ll binarySearch(function<bool(ll)> f);
bool check(ll days);

ll n, m, s;

// array of bugs sorted by difficulty in descending order
// - bugs[i].first => difficulty of bugs[i]
// - bugs[i].second => original index of bugs[i] before sort
vector<pair<ll, ll>> bugs;

// buffer for pair of students
pair<ll, ll> vStudents[N];

// array of students sorted by ability in descending order
// - studentsAbilitySorted[i].first => original index of studentsAbilitySorted[i] before sort
// - studentsAbilitySorted[i].second.first => ability of the student
// - studentsAbilitySorted[i].second.second => credits required by the student
vector<pair<ll, pair<ll, ll>>> studentsAbilitySorted;

// priority queue for binary search query
// checking.top().first => lowest cost
// checking.top().second => index of student who offers this cost
priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> checking;

ll sol[N];

ll tempSol[N];

int main(){

    // Acquiring inputs

    cin >> n >> m >> s;

    for(ll i = 0; i < m; i++){
        ll difficulty;
        cin >> difficulty;
        bugs.push_back({difficulty, i});
    }

    // sort bugs by difficulty
    sort(bugs.begin(), bugs.end(), greater<pair<ll, ll>>()); 

    // for(auto i : bugs){
    //     cout << "(" << i.first << ", " << i.second << "), ";
    // }

    for(ll i = 0; i < n; i++){
        cin >> vStudents[i].first;
    }

    for(ll i = 0; i < n; i++){
        cin >> vStudents[i].second;
    }
    
    for(ll i = 0; i < n; i++){
        studentsAbilitySorted.push_back({i, vStudents[i]});
    }

    sort(studentsAbilitySorted.begin(), studentsAbilitySorted.end(), cmp);

    // for(auto i : studentsAbilitySorted){
    //     cout << "(" << i.first << ", " << i.second.first << "-" << i.second.second << "), ";
    // }

    ll days = binarySearch(&check);
    
    if(days == -1){
        cout << "NO\n";
        return 0;
    }

    cout << "YES\n";

    for(ll i = 0; i < m; i ++){
        cout << sol[i] + 1 << ' ';
    }
    cout << '\n';
}

ll cmp(pair<ll, pair<ll, ll>> a, pair<ll, pair<ll, ll>>b ){
    return(a.second.first > b.second.first);
}

ll binarySearch(function<bool(ll)> f) {
    ll lo = 0;
    ll hi = m;
    ll bestSoFar = -1;

    // Range [lo, hi];
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (f(mid)) {
            bestSoFar = mid;
            hi = mid - 1;
            for(ll i = 0; i < m; i ++){
                sol[i] = tempSol[i];
            }
        } else {
            lo = mid + 1;
        }
    }

    return bestSoFar;
}

bool check(ll days){
    while( !checking.empty() ) checking.pop();

    ll passes = s;
    ll bugCount = 0;

    ll i = 0, j = 0;
    while(bugCount < m){
        while(studentsAbilitySorted[i].second.first >= bugs[bugCount].first){
            checking.push({studentsAbilitySorted[i].second.second, studentsAbilitySorted[i].first});
            i++;
        }

        if(checking.empty()){
            return false;
        }

        auto p = checking.top();
        passes -= p.first;
        bugCount += days;
        bugCount = min(bugCount, m);

        for(; j < bugCount; j++){
            tempSol[bugs[j].second] = p.second;
        }

        checking.pop();
        if(passes < 0){
            return false;
        }
    }

    return true;
}