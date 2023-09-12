#include <iostream>
#include <string>

using namespace std;

int count01(string str){
    int sum = 0;
    for(int i = 0; i < str.length(); i++){
        if(str[i] == 1){
            sum += countBit(str, i, 0);
        }
    }
    return sum;
}

int count10(string str){
    int sum = 0;
    for(int i = 0; i < str.length(); i++){
        if(str[i] == 0){
            sum += countBit(str, i, 1);
        }
    }
    return sum;
}

int countBit(string str, int position, int bit){
    int c = 0;
    for(int i = 0; i < position; i ++){
        if(str[i] == bit){
            c++;
        }
    }
    return c;
}

int main() {
    int a, b, c, d;
    cin >>a>>b>>c>>d;
    int sum = 0, num0 = -1, num1 = -1;

    for(int i=0; i <= a; i ++){
        sum += i;
        if(sum == a){
            num0 = i;
        }
        if(sum == d){
            num1 = i;
        }
        if(sum > a && sum > b){
            cout << "impossible\n";
            return 0;
        }
    }
}