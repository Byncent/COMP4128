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
typedef pair<ll, ll> pll;
typedef struct node {
  ll r0;
  ll r1;
  ll r2;
} node;

// Constants definition
const ll N = 1e6+7;

// Global vars definition
ll n, q;
ll lazyadd[N << 2];
node sum[N << 2];


// Procedure for recalculating a node's sum from its lazy and children.
void recalculate(ll id, ll l, ll r) {
    if (r - l == 1) {
        // cout << "         Is a leaf node\n";
        ll r0=sum[id].r0, r1=sum[id].r1, r2=sum[id].r2;
        if(lazyadd[id] == 1){
            sum[id].r0 = r2;
            sum[id].r1 = r0;
            sum[id].r2 = r1;
        }else if (lazyadd[id] == 2){
            sum[id].r0 = r1;
            sum[id].r1 = r2;
            sum[id].r2 = r0;
        }
        lazyadd[id] = 0;
    }
    else{
        if(lazyadd[id] == 0){
            sum[id].r0 = sum[id * 2].r0 + sum[id * 2 + 1].r0;
            sum[id].r1 = sum[id * 2].r1 + sum[id * 2 + 1].r1;
            sum[id].r2 = sum[id * 2].r2 + sum[id * 2 + 1].r2;
        }else if(lazyadd[id] == 1){
            sum[id].r0 = sum[id * 2].r2 + sum[id * 2 + 1].r2;
            sum[id].r1 = sum[id * 2].r0 + sum[id * 2 + 1].r0;
            sum[id].r2 = sum[id * 2].r1 + sum[id * 2 + 1].r1;
        }else{
            sum[id].r0 = sum[id * 2].r1 + sum[id * 2 + 1].r1;
            sum[id].r1 = sum[id * 2].r2 + sum[id * 2 + 1].r2;
            sum[id].r2 = sum[id * 2].r0 + sum[id * 2 + 1].r0;
        }
    }
}

void update_lazy(ll id, ll v, ll l, ll r) {
    lazyadd[id] = (lazyadd[id] + v)%3;
    recalculate(id, l, r);
}

// Preorder procedure for propagation. Do NOT call it on leaves.
void propagate(ll id, ll l, ll r) {
    // cout << "   propagating\n";
    ll mid = (l + r) / 2;
    update_lazy(id * 2, lazyadd[id], l, mid);
    update_lazy(id * 2 + 1, lazyadd[id], mid, r);
    lazyadd[id] = 0;
}

void update(ll uL, ll uR, ll v = 1, ll i = 1, ll cL = 0, ll cR = n) {
    // cout << "attempting to update: " << cL << " - " << cR << '\n';
    if (uL == cL && uR == cR) {
        update_lazy(i, v, cL, cR);
        return;
    }
    propagate(i, cL, cR);
    ll mid = (cL + cR) / 2;
    if (uL < mid) update(uL, min(uR, mid), v, i * 2, cL, mid);
    if (uR > mid) update(max(uL, mid), uR, v, i * 2 + 1, mid, cR);
    recalculate(i, cL, cR);
}

ll query(ll qL, ll qR, ll i = 1, ll cL = 0, ll cR = n) {
    if (qL == cL && qR == cR) {
        return sum[i].r0;
    }
    propagate(i, cL, cR);
    ll mid = (cL + cR) / 2;
    ll ans = 0;
    if (qL < mid) ans += query(qL, min(qR, mid), i * 2, cL, mid);
    if (qR > mid) ans += query(max(qL, mid), qR, i * 2 + 1, mid, cR);
    return ans;
}

ll init(ll i = 1, ll l = 0, ll r = n, ll max_val = n){
    ll  mid = (l + r) / 2;
    if(l >= max_val){
        sum[i].r0 = 0;
    }else{
        if (r - l == 1) {
            sum[i].r0 = 1;
        }else{
            sum[i].r0 = init(i*2, l, mid) +  init(i*2+1, mid, r);
        }
    }

    return sum[i].r0;
}

int main() {
    vector<ll> sol;
    cin >> n >> q;

    init();
    // for(int i = 0; i < 20; i ++){
    //     cout << "i = " << i << ", sum[i] = " << sum[i].r0 << '\n';
    // }
    for(ll i = 0; i < q; i ++){
        ll op, A, B;
        cin >> op >> A >> B;
        if(op == 1){
            sol.push_back(query(A, B+1));
        }else{
            update(A, B+1);
        }
    }
    for(ll item : sol){
        cout << item << "\n";
    }
    return 0;
}