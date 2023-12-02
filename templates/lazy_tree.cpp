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

// Constants definition
const int N = 1e6+7;

// Global vars definition
int n;
ll lazyadd[N << 2], sum[N << 2];

// Procedure for recalculating a node's sum from its lazy and children.
void recalculate(int id, long long l, long long r) {
    sum[id] = lazyadd[id] * (r - l);
    if (r - l != 1) {
        sum[id] += sum[id * 2];
        sum[id] += sum[id * 2 + 1];
    }
}

void update_lazy(int id, long long v, long long l, long long r) {
    lazyadd[id] += v;
    recalculate(id, l, r);
}

// Preorder procedure for propagation. Do NOT call it on leaves.
void propagate(int id, long long l, long long r) {
    long long mid = (l + r) / 2;
    update_lazy(id * 2, lazyadd[id], l, mid);
    update_lazy(id * 2 + 1, lazyadd[id], mid, r);
    lazyadd[id] = 0;
}

void update(int uL, int uR, int v, int i = 1, int cL = 0, int cR = n) {
    if (uL == cL && uR == cR) {
        update_lazy(i, v, cL, cR);
        return;
    }
    propagate(i, cL, cR);
    int mid = (cL + cR) / 2;
    if (uL < mid) update(uL, min(uR, mid), v, i * 2, cL, mid);
    if (uR > mid) update(max(uL, mid), uR, v, i * 2 + 1, mid, cR);
    recalculate(i, cL, cR);
}

long long query(int qL, int qR, int i = 1, int cL = 0, int cR = n) {
    if (qL == cL && qR == cR) {
        return sum[i];
    }
    propagate(i, cL, cR);
    int mid = (cL + cR) / 2;
    long long ans = 0;
    if (qL < mid) ans += query(qL, min(qR, mid), i * 2, cL, mid);
    if (qR > mid) ans += query(max(qL, mid), qR, i * 2 + 1, mid, cR);
    return ans;
}

int main() {
    // Example usage:
    n = 16; // Set the value of 'n' appropriately

    // Example update and query
    update(0, 16 , 10); // Update the range [1, 5) with the value 10
    long long result = query(0, 16); // Query the range [2, 8)

    cout << lazyadd[1] << '\n';

    cout << "Result: " << result << endl;

    return 0;
}