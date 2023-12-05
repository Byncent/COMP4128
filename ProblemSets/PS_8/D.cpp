#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

const ll N = 1e7+7;
const ll N1 = 1e6;
int sol[N][2];

int P;
int notprime[N];
int primes[N];


void init() {
	notprime [0] = notprime [1] = 1;
	for (ll i = 2; i < N; i++) {
		if (notprime[i]){
			continue;
		}
		primes[P++] = i;
		// if i is prime , mark aint its multiples as not prime
		for (ll j = i*i; j < N; j += i){
			notprime[j] = true;
		}
	}
}

int n;
vector<int> vals;
int main(){
	cin >> n;
	init();
	for(int i = 0; i < n; i ++){
		int val;
		cin >> val;

		if(!notprime[val]){
			sol[i][0] = sol[i][1] = -1;
			continue;
		}


		int a = 1;
		for (int i = 0; i < P; i ++ ){
			if (val % primes[i] == 0){
				
				int f = primes[i];

				while (val % f == 0) {
					val /= f;
					a *= f;
				}
					break;
			}
		}
		
		if(val == 1 || a == 1){
			sol[i][0] = sol[i][1] = -1;
		} else{
			sol[i][0] = a;
			sol[i][1] = val;
		}
		
	}
	for(int i = 0; i < n; i ++){
		cout << sol[i][0] << ' ';
	}
	cout << '\n';
	for(int i = 0; i < n; i ++){
		cout << sol[i][1] << ' ';
	}
	cout << '\n';
}