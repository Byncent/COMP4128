#include <iostream>
#include <string>

using namespace std;

int main() {
    int a, b, c, d;
    string res;
    cin >>a>>b>>c>>d;
    int sum = 0, num0 = -1, num1 = -1;

    // check if a and d are triangle numbers
    for(int i=0; i <= a + d; i ++){
        sum += i;
        if(sum == a){
            num0 = i + 1;
        }
        if(sum == d){
            num1 = i + 1;
        }
    }

    // if not, impossible
    if (num0 == -1 || num1 == -1){
        cout << "impossible\n";
        return 0;
    }

    // check if there exist 0 and 1
    if(a == 0  && (b == 0 && c == 0)){
        for(int i = 0; i < num1; i++){
            res += '1';
        }
        cout << res << '\n';
        return 0;
    }
    if(d == 0  && (b == 0 && c == 0)){
        for(int i = 0; i < num0; i++){
            res += '0';
        }
        cout << res << '\n';
        return 0;
    }

    // if the number of combinations of 01 and 10 are not the same as number of 0 * number of 1 then impossible
    if(b + c != num0 * num1){
        cout << "impossible\n";
        return 0;
    }

    if(a == 0 && b == 0 && c == 0 && d == 0){
        cout << '0\n';
        return 0;
    }

    int head1, tail1, mid1, head0, tail0;
    head1 = c / num0;
    tail0 = c % num0;
    mid1 = (tail0 != 0);
    head0 = num0 - tail0;
    tail1 = num1 - head1 - mid1;

    
    for(int i = 0; i < head1; i ++){
        res += '1';
    }
    for(int i = 0; i < head0; i ++){
        res += '0';
    }
    if(mid1){
        res += '1';
    }
    for(int i = 0; i < tail0; i ++){
        res += '0';
    }
    for(int i = 0; i < tail1; i ++){
        res += '1';
    }

    cout <<  res << '\n';
}