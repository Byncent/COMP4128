/*
 * primes
 */

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool isprime(ll x) {
  if (x < 2) return false;

  for (ll f = 2; f*f <= x; f++)
    if (x % f == 0)
      return false;
  
  return true;
}

// Returns prime factors in increasing order with right multiplicity.
vector<ll> primefactorize(ll x) {
  vector<ll> factors;
  for (ll f = 2; f*f <= x; f++)
    while (x % f == 0) {
      factors.push_back(f);
      x /= f;
    }

  if (x != 1) factors.push_back(x);
  return factors;
}

int main(){
    ll n;
    cin >> n;

    vector<ll> factors = primefactorize(n);
    map<ll, ll> m;

    ll pow_of_2 = 1;
    ll idx = 0;

    for(ll factor : factors){
        m[factor] += 1;
        if(m[factor] > pow_of_2){
            pow_of_2 *= 2;
            idx ++;
        }
    }

    ll val = 1;
    ll flag = 0;
    for(auto it : m){
        val *= it.first;
        if(it.second < pow_of_2){
            flag = 1;
        }
    }

    idx += flag;
    cout << val << " " << idx << '\n';
}