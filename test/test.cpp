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

typedef struct node {
  int r0;
  int r1;
  int r2;
} node;

node sum[100];
int n = 4;
int deg = 1;

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

int main(){
    while(deg < n){
        deg *= 2;
    }
    init();
    for(int i = 0; i < 20; i ++){
        cout << "sum[" << i << "] = " << sum[i].r0 << '\n';
    }
}
