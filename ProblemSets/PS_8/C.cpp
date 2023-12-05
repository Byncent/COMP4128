#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, m;
ll mod = 1e9+7;

struct Matrix {
    ll n;
    vector <vector <long long >> v;
    
    Matrix(ll _n) : n(_n) {
        v.resize(n);
        for (ll i = 0; i < n; i++)
            for (ll j = 0; j < n; j++)
                v[i]. push_back (0);
    }

    static Matrix getIdentity(ll n) {
        Matrix res(n);
        for (ll i = 0; i < n; i++)
            res.v[i][i] = 1;
        return res;
    }

    Matrix operator *(const Matrix &o) const {
        Matrix res(n);
        for (ll i = 0; i < n; i++)
            for (ll j = 0; j < n; j++)
                for (ll k = 0; k < n; k++)
                    res.v[i][j] = (res.v[i][j] +  v[i][k] * o.v[k][j])%mod;
        return res;
    }

    Matrix operator ^(long long k) const {
        Matrix res = Matrix:: getIdentity(n);
        Matrix a = *this;
        while (k) { // building up in powers of two
            if (k&1) res = res*a;
            a = a*a;
            k /= 2;
        }
        return res;
    }

    void setEntry(ll i, ll j, ll val){
        v[i][j] = val;
    }
};


int main(){
    cin >> n >> m;


    Matrix mat(m);

    mat.setEntry(0, 0, 1);
    mat.setEntry(0, m-1, 1);

    for (ll i = 1; i < m; i++)
        mat.v[i][i-1] = 1; // other rows of transition matrix

    mat = mat^n;

    // cout << mat.v[0][0] << mat.v[0][1] << '\n';
    // cout << mat.v[1][0] << mat.v[1][1] << '\n';

    ll res = 0;
    for(ll i = 0; i < m; i++){
        res = (res + mat.v[m-1][i])%mod;
    }

    cout << res << '\n';
}