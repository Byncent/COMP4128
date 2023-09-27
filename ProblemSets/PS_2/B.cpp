#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

multiset<int> s;
vector<pair<int, int>> v;

bool pairCmp(pair<int, int> p1, pair<int, int> p2){
    return(p1.second < p2.second);
}

int main(){

    int n, k;
    cin >> n >> k;

    int num = 0;

    for(int i = 0; i < n; i ++){
        pair<int, int> activity;
        cin >> activity.first >> activity.second;
        v.push_back(activity);
    }

    sort(v.begin(), v.end(), pairCmp);

    for(int i = 0; i < n; i ++){

        int start = - v[i].first;
        int end = - v[i].second;

        auto it = s.upper_bound(start);

        if(it == s.end()){
            if(s.size() < k){
                s.insert(end);
                num ++;
            }
            continue;
        }

        s.erase(it);
        s.insert(end);
        num ++;
    }

    cout << num << '\n';
    return 0;
}