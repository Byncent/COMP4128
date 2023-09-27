#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int N = 100100; // The number of additional nodes created can be as high as the next power of two up from N (2^17 = 131,072)
int tree[1 << 18]; // Initialize the tree with a size that accommodates the required number of nodes
int n; // The actual length of the underlying array


int query(int qL, int qR, int i = 1, int cL = 0, int cR = n) {
    // The query range exactly matches this node's range of responsibility
    if (cL == qL && cR == qR)
        return tree[i];

    // We might need to query one or both of the children
    int mid = (cL + cR) / 2;
    int ans = 0;

    // Query the part within the left child [cL, mid), if any
    if (qL < mid) ans += query(qL, min(qR, mid), i * 2, cL, mid);

    // Query the part within the right child [mid, cR), if any
    if (qR > mid) ans += query(max(qL, mid), qR, i * 2 + 1, mid, cR);

    return ans;
}

// p is the index in the array (0-based)
// v is the value that the p-th element will be updated to
// i is the index in the tree, rooted at 1, so children are 2*i and 2*i+1
// Instead of explicitly storing each node's range of responsibility [cL, cR),
// we calculate it on the way down.
// The root node is responsible for [0, n)
void update(int p, int v, int i = 1, int cL = 0, int cR = n) {
    if (cR - cL == 1) {
        // This node is a leaf, so apply the update
        tree[i] = v;
        return;
    }

    // Figure out which child is responsible for the index (p) being updated
    int mid = (cL + cR) / 2;
    if (p < mid)
        update(p, v, i * 2, cL, mid);
    else
        update(p, v, i * 2 + 1, mid, cR);

    // Once we have updated the correct child, recalculate our stored value.
    tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

// Print the entire tree to stderr
// Instead of explicitly storing each node's range of responsibility [cL, cR),
// we calculate it on the way down.
// The root node is responsible for [0, n)
void debug(int i = 1, int cL = 0, int cR = n) {
    // Print current node's range of responsibility and value
    cerr << "tree[" << cL << "," << cR << ")=" << tree[i];

    if (cR - cL > 1) { // Not a leaf
        // Recurse within each child
        int mid = (cL + cR) / 2;
        debug(i * 2, cL, mid);
        debug(i * 2 + 1, mid, cR);
    }
}


int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        int best = 1 + query(0, x);
        update(x, best);
    }

    cout << query(0, N) << '\n';

    return 0;
}


