#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    int a, b, c, d;
    cin >>a>>b>>c>>d;
    int sum = 0, num0 = -1, num1 = -1;

    // check if a and d are triangle numbers
    int ceil = max(a, d);
    for(int i=0; i <= ceil; i ++){
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
            cout << '1';
        }
        cout << '\n';
        return 0;
    }
    if(d == 0  && (b == 0 && c == 0)){
        for(int i = 0; i < num0; i++){
            cout << '0';
        }
        cout << '\n';
        return 0;
    }

    // if the number of combinations of 01 and 10 are not the same as number of 0 * number of 1 then impossible
    if(b + c != num0 * num1){
        cout << "impossible\n";
        return 0;
    }

    if(a == 0 && b == 0 && c == 0 && d == 0){
        cout << "0\n";
        return 0;
    }

    while(c > num0){
        cout << '1';
        num1 -= 1;
        c -= num0;
    }

    while(num0 > c){
        cout << '0';
        num0 -= 1;
    }

    cout << '1';
    num1 -= 1;

    while(num0 > 0){
        cout << '0';
        num0 -= 1;
    }

    while(num1 > 0){
        cout << '1';
        num1 -= 1;
    }

    cout << '\n';
    return 0;
}