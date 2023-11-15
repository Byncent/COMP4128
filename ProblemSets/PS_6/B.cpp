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
typedef pair<ll, ll> pll;
typedef struct node{
    ll maxrt = 0;
    ll sumrt = 0;
    ll l = 0;
    ll r = 0;
    bool incrt = false;
    bool decrt = false;
} node;

// Constants definition
const ll N = 1e7+7;

// Global vars definition
ll n, m;
vector<ll> res;
node tree[N];

node query(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
     
    // the query range exactly matches this node's range of responsibility
    if (cL == qL && cR == qR){
        return tree[i];
    }

    // we might need to query one or both of the children
    node ans, n1, n2;
    ll mid = (cL + cR) / 2;
    bool lv = false, rv = false;

    // query the part within the left child [cL, mid), if any
    if (qL < mid){
        lv = true;
        n1 = query(qL, min(qR, mid), i * 2, cL, mid);
    }
    // query the part within the right child [mid, cR), if any
    if (qR > mid){
        rv = true;
        n2 = query(max(qL, mid), qR, i * 2 + 1, mid, cR);
    }
    ans.sumrt = n1.sumrt + n2.sumrt;
    ans.maxrt = max(n1.maxrt, n2.maxrt);
    ans.l = n1.l;
    ans.r = n2.r;

    if(lv && rv){
        ans.decrt = n1.decrt && n2.decrt && (n1.r >= n2.l);
        ans.incrt = n1.incrt && n2.incrt && (n1.r <= n2.l);
    }else if(lv){
        ans.decrt = n1.decrt;
        ans.incrt = n1.incrt;
    } else if(rv){
        ans.decrt = n2.decrt;
        ans.incrt = n2.incrt;
    }

    return ans;
}

void update(ll p, ll v, ll i = 1, ll cL = 0, ll cR = n) {
    if (cR - cL == 1) {
        // this node is a leaf, so apply the update
        tree[i].sumrt = v;
        tree[i].maxrt = v;
        tree[i].l = v;
        tree[i].r = v;
        tree[i].incrt = true;
        tree[i].decrt = true;
        return;
    }
    
    // figure out which child is responsible for the index (p) being updated
    ll mid = (cL + cR) / 2;
    if (p < mid){
        update(p, v, i * 2, cL, mid);
    } 
    else{
        update(p, v, i * 2 + 1, mid, cR);
    }
    // once we have updated the correct child, recalculate our stored value.
    tree[i].sumrt = tree[i * 2].sumrt + tree[i * 2 + 1].sumrt;
    tree[i].maxrt = max(tree[i*2].maxrt, tree[i*2+1].maxrt);
    tree[i].l = tree[i*2].l;
    tree[i].r = tree[i*2+1].r;
    tree[i].incrt = tree[i*2].incrt && tree[i*2+1].incrt && (tree[i*2].r <= tree[i*2+1].l);
    tree[i].decrt = tree[i*2].decrt && tree[i*2+1].decrt && (tree[i*2].r >= tree[i*2+1].l);
}

int main(){
    cin >> n >> m;

    for(ll i = 0; i < n; i++){
        ll v;
        cin >> v;
        update(i, v);
    }

    for(ll i = 0; i < m; i ++){
        char op;
        ll x, y;
        cin >> op >> x >> y;
        x --;

        if(op == 'U'){
            update(x, y);
        }else{
            node sol = query(x, y);
            if(op == 'M'){
                res.push_back(sol.maxrt);
            }else if(op == 'S'){
                res.push_back(sol.sumrt);
            }else if(op == 'I'){
                res.push_back(sol.incrt);
            }else if(op == 'D'){
                res.push_back(sol.decrt);
            }
        }
    }

    for(ll i : res){
        cout << i << '\n';
    }

    return 0;
}