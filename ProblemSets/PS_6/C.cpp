#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <functional>

using namespace std;


#define RESET 0
#define FILL 1
#define CLEAR 2
#define INVERT 3

//typedefs
typedef long long ll;

// the query operation: {l, r, type}
// - op.l: the left end of the query operation
// - op.r: the right range of query operation
// - op.type: the type of query operation, one of {ADD, REMOVE, INVERT}
// - - FILL: make all the values in the range peresent
// - - CLEAR: make all the values in the range absent
// - - INVERT: invert the status of all nodes
typedef struct operation{

    // the left end of the query operation
    ll l;

    // the right range of query operation
    ll r;

    // the type of query operation, one of {INVERT, FILL, CLEAR}
    // - - FILL: make all the values in the range peresent
    // - - CLEAR: make all the values in the range absent
    // - - INVERT: invert the status of all nodes
    ll type;
} op;

// node in the range tree array: {min_pres, min_absent}
// - node.min_pres: the minimum PRESENT value in the node's range of responsibility
// - node.min_absent: the minimum ABSENT value in the node's range of responsibility
typedef struct node{

    // the minimum PRESENT value in the node's range of responsibility
    ll min_pres;

    // the minimum ABSENT value in the node's range of responsibility
    ll min_absent;
} node;

// node in the lazyadd array: {inv_counter, reset_flag, last_op, last_reset}
// - lazy_node.inv_counter: lazy counter fot the the number of inversion applied to the current node
// - lazy_node.reset_flag: if the node has been cleared/filled, true if yes
// - lazy_node.last_op: the last operation applied to the range, one of {RESET, INVERT}
// -  - RESET: the last operation applied to this node's range of responsibility is either a FILL or a CLEAR
// - lazy_node.last_reset: the last operation that resets the value of the node's range of responsibility, one of {FILL, CLEAR}
// - - FILL: the last reset operation applied to the node's range of responsibilit is FILL
// - - CLEAR: the last reset operation applied to the node's range of responsibilit is CLEAR
typedef struct lazy_node{

    // lazy counter fot the the number of inversion applied to the current node
    ll inv_counter;

    // if the node has been cleared/filled, true if yes
    ll reset_flag;

    // the last operation applied to the range, one of {RESET = 0, or 1}
    // - RESET: the last operation applied to this node's range of responsibility is either a FILL or a CLEART
    ll last_op;

    // the last operation that resets the value of the node's range of responsibility, one of {FILL, CLEAR}
    // - FILL: the last reset operation applied to the node's range of responsibilit is FILL
    // - CLEAR: the last reset operation applied to the node's range of responsibilit is CLEAR
    ll last_reset;
}lazy_node;

//consts
const ll N = 1e6+10;
const ll INF = 1e18+10;

//global vars
ll n, n_nodes = 0;

// array of operations
op ops[N];

// look-up arrays from the compressed coordinate to value
ll vals[N];

// coordinate compression map from value to compressed coordinate
map<ll, ll> m;

// array of lazy nodes
lazy_node lazyadd[N];

// range tree
node tree[N];

// Procedure for recalculating a node's tree from its lazy and children.
void recalculate(ll id, ll l, ll r) {
    lazy_node ln = lazyadd[id];
    
    if(ln.last_op == RESET){
        if(ln.last_reset == FILL){
            tree[id].min_absent = INF;
            tree[id].min_pres = vals[l];
        }else{
            tree[id].min_absent = vals[l];
            tree[id].min_pres = INF; 
        }
    }else{
        if(r-1 == 1){
            if(ln.inv_counter % 2){
                ll temp = tree[id].min_absent;
                tree[id].min_absent = tree[id].min_pres;
                tree[id].min_pres = temp;
            }
            lazyadd[id] = lazy_node{0, 0, 0, 0};
        }else{
            if(ln.inv_counter % 2){
                tree[id].min_absent = min(tree[id*2].min_pres, tree[id*2+1].min_pres);
                tree[id].min_pres = min(tree[id*2].min_absent, tree[id*2+1].min_absent);
            } else{
                tree[id].min_pres = min(tree[id*2].min_pres, tree[id*2+1].min_pres);
                tree[id].min_absent = min(tree[id*2].min_absent, tree[id*2+1].min_absent);
            }
        }

    }
}

void update_lazy(ll id, lazy_node v, ll l, ll r) {

    lazyadd[id].inv_counter += v.inv_counter;
    lazyadd[id].last_op = v.last_op;
    lazyadd[id].reset_flag = lazyadd[id].reset_flag || v.reset_flag;
    if(v.reset_flag){
        lazyadd[id].last_reset = v.last_reset;
    }
    recalculate(id, l, r);
}

// Preorder procedure for propagation. Do NOT call it on leaves.
void propagate(ll id, ll l, ll r) {
    ll mid = (l + r) / 2;
    update_lazy(id * 2, lazyadd[id], l, mid);
    update_lazy(id * 2 + 1, lazyadd[id], mid, r);
    lazyadd[id] = lazy_node{0, 0, 0, 0};
}

// The root node is responsible for [0, n). Update range [uL, uR)
void update(ll uL, ll uR, ll operation, ll i = 1, ll cL = 0, ll cR = n_nodes) {

    if (uL == cL && uR == cR) {
        lazy_node op_node = {0, 0, operation, 0};
        if(operation == INVERT){
            op_node.inv_counter = 1;
        }else{
            op_node.reset_flag = 1;
            op_node.last_reset = operation;
        }
        update_lazy(i, op_node, cL, cR);
        return;
    }

    propagate(i, cL, cR);
    ll mid = (cL + cR) / 2;
    if (uL < mid) update(uL, min(uR, mid), operation, i * 2, cL, mid);
    if (uR > mid) update(max(uL, mid), uR, operation, i * 2 + 1, mid, cR);
    recalculate(i, cL, cR);
}

ll init(ll i = 1, ll l = 0, ll r = n, ll max_val = n_nodes){
    ll  mid = (l + r) / 2;
    if(l >= max_val){
        return 0;
    }else{
        if (r - l == 1) {
            tree[i].min_absent = vals[l];
            tree[i].min_pres = INF;
        }else{
            
            tree[i].min_absent = min(init(i*2, l, mid),  init(i*2+1, mid, r));
            tree[i].min_pres = INF;
        }
    }

    return tree[i].min_absent;
}


int main(){
    cin >> n;
    for(ll i = 0; i < n; i ++){
        cin >> ops[i].type >> ops[i].l >> ops[i].r;
        m[ops[i].l] = 1;
        m[ops[i].r] = 1;
        m[ops[i].r+1] = 1;
    }
    m[1] = 1;

    for(auto it : m){
        n_nodes ++;
        vals[n_nodes] = it.first;
        it.second = n_nodes;
    }

    for(ll i = 0; i < n; i ++){
        update(m[ops[i].l], m[ops[i].r], ops[i].type);
        cout << tree;
    }

}