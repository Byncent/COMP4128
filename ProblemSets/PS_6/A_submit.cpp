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
typedef struct node {
  int r0;
  int r1;
  int r2;
} node;

// Constants definition
const int N = 1e6+7;

// Global vars definition
int n, q, deg=1;
ll lazyadd[N << 2];
node sum[N << 2];


// Procedure for recalculating a node's sum from its lazy and children.
void recalculate(int id, long long l, long long r, long long v) {
    // cout << "   recalculating node " << id << " = " << l << " - " << r << '\n';
    int mod = v % 3;
    // cout << "      lazy add [" << id <<"] = " << lazyadd[id] << ", mod = " << mod<<'\n';

    if (r - l == 1) {
        // cout << "         Is a leaf node\n";
        int r0=sum[id].r0, r1=sum[id].r1, r2=sum[id].r2;
        if(mod == 1){
            // cout << "            mod = 1, before: \n";
            // cout << "               r0 = " << sum[id].r0 << '\n';
            // cout << "               r1 = " << sum[id].r1 << '\n';
            // cout << "               r2 = " << sum[id].r2 << '\n';

            sum[id].r0 = r2;
            sum[id].r1 = r0;
            sum[id].r2 = r1;
            // cout << "            mod = 1, after: \n";
            // cout << "               r0 = " << sum[id].r0 << '\n';
            // cout << "               r1 = " << sum[id].r1 << '\n';
            // cout << "               r2 = " << sum[id].r2 << '\n';
        }else if (mod == 2){
            // cout << "            mod = 2, before: \n";
            // cout << "               r0 = " << sum[id].r0 << '\n';
            // cout << "               r1 = " << sum[id].r1 << '\n';
            // cout << "               r2 = " << sum[id].r2 << '\n';
            sum[id].r0 = r1;
            sum[id].r1 = r2;
            sum[id].r2 = r0;
            // cout << "            mod = 2, after: \n";
            // cout << "               r0 = " << sum[id].r0 << '\n';
            // cout << "               r1 = " << sum[id].r1 << '\n';
            // cout << "               r2 = " << sum[id].r2 << '\n';
        }
    }
    else{
        if(mod == 0){
            sum[id].r0 = sum[id * 2].r0 + sum[id * 2 + 1].r0;
            sum[id].r1 = sum[id * 2].r1 + sum[id * 2 + 1].r1;
            sum[id].r2 = sum[id * 2].r2 + sum[id * 2 + 1].r2;
        }else if(mod == 1){
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

void update_lazy(int id, long long v, long long l, long long r) {
    lazyadd[id] += v;
    recalculate(id, l, r, v);
}

// Preorder procedure for propagation. Do NOT call it on leaves.
void propagate(int id, long long l, long long r) {
    // cout << "   propagating\n";
    long long mid = (l + r) / 2;
    update_lazy(id * 2, lazyadd[id], l, mid);
    update_lazy(id * 2 + 1, lazyadd[id], mid, r);
    lazyadd[id] = 0;
}

void update(int uL, int uR, int v = 1, int i = 1, int cL = 0, int cR = n) {
    // cout << "attempting to update: " << cL << " - " << cR << '\n';
    if (uL == cL && uR == cR) {
        update_lazy(i, v, cL, cR);
        return;
    }
    propagate(i, cL, cR);
    int mid = (cL + cR) / 2;
    if (uL < mid) update(uL, min(uR, mid), v, i * 2, cL, mid);
    if (uR > mid) update(max(uL, mid), uR, v, i * 2 + 1, mid, cR);
    recalculate(i, cL, cR, v);
}

long long query(int qL, int qR, int i = 1, int cL = 0, int cR = n) {
    if (qL == cL && qR == cR) {
        return sum[i].r0;
    }
    propagate(i, cL, cR);
    int mid = (cL + cR) / 2;
    long long ans = 0;
    if (qL < mid) ans += query(qL, min(qR, mid), i * 2, cL, mid);
    if (qR > mid) ans += query(max(qL, mid), qR, i * 2 + 1, mid, cR);
    return ans;
}

int init(int i = 1, int l = 0, int r = deg, int max_val = n){
    int  mid = (l + r) / 2;
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
    while(deg < n){
        deg *= 2;
    }
    init();
    for(int i = 0; i < q; i ++){
        int op, A, B;
        cin >> op >> A >> B;
        // cout << "operation: " << op << " " << A << " " << B << '\n';
        if(op == 1){
            sol.push_back(query(A, B+1));
        }else{
            update(A, B+1);
        }
        // cout << "===================================================================\n";
    }

    for(int item : sol){

        cout << item << "\n";
    }
    return 0;
}