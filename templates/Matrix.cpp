#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n, m;
ll mod = 1e9+7;

struct Matrix {
    int n;
    vector <vector <long long >> v;
    
    Matrix(int _n) : n(_n) {
        v.resize(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                v[i]. push_back (0);
    }

    static Matrix getIdentity(int n) {
        Matrix res(n);
        for (int i = 0; i < n; i++)
            res.v[i][i] = 1;
        return res;
    }

    Matrix operator *(const Matrix &o) const {
        Matrix res(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    res.v[i][j] += v[i][k] * o.v[k][j];
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

    void setEntry(int i, int j, int val){
        v[i][j] = val;
    }
};


int main(){
    cin >> n >> m;
}