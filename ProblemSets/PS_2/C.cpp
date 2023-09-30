#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>

using namespace std;

#define OR 1
#define XOR -1

const int N = 131072; // The number of additional nodes created can be as high as the next power of two up from N (2^17 = 131,072)
int tree[1 << 18]; // Initialize the tree with a size that accommodates the required number of nodes


int update(int p, int v, int i = 1, int cL = 0, int cR = N);
void debug(int i = 1, int cL = 0, int cR = N);


int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < pow(2, n); i++){
        int v;
        cin >> v;
        update(i, v);
    }

    for(int i = 0; i < m; i++){
        int p, v;
        cin >> p >> v;
        update(p -1, v);
        cout << tree[1] << '\n';
    }
}

// p is the index in the array (0-based)
// v is the value that the p-th element will be updated to
// i is the index in the tree, rooted at 1, so children are 2*i and 2*i+1
// Instead of explicitly storing each node's range of responsibility [cL, cR),
// we calculate it on the way down.
// The root node is responsible for [0, n)
int update(int p, int v, int i, int cL, int cR) {
    if (cR - cL == 1) {
        // This node is a leaf, so apply the update
        tree[i] = v;
        return OR;
    }

    // Figure out which child is responsible for the index (p) being updated
    int mid = (cL + cR) / 2;
    int op;
    if (p < mid)
        op = update(p, v, i * 2, cL, mid);
    else
        op = update(p, v, i * 2 + 1, mid, cR);

    // Once we have updated the correct child, recalculate our stored value.
    if(op == OR)
        tree[i] = tree[i * 2] | tree[i * 2 + 1];
    else
        tree[i] = tree[i * 2] ^ tree[i * 2 + 1];

    return op * -1;
}

// Print the entire tree to stderr
// Instead of explicitly storing each node's range of responsibility [cL, cR),
// we calculate it on the way down.
// The root node is responsible for [0, n)
void debug(int i, int cL, int cR) {
    // Print current node's range of responsibility and value
    cerr << "tree[" << cL << "," << cR << ")=" << tree[i];

    if (cR - cL > 1) { // Not a leaf
        // Recurse within each child
        int mid = (cL + cR) / 2;
        debug(i * 2, cL, mid);
        debug(i * 2 + 1, mid, cR);
    }
}



