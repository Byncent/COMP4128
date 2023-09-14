#include <iostream>

using namespace std;

int main(){
    int days, curr;
    int currmax = 0, counter = 0, sum = 0;

    cin >> days;

    for(int i = 0; i < days; i++){
        cin >> curr;

        if (curr != 0){
            currmax = max(curr, currmax);
            sum -= curr;
        } else{
            cout << "val added: "<< counter * currmax << '\n';
            sum += counter * currmax;
            counter = 0;
        }
        counter ++;
    }

    sum += counter * currmax;

    cout << sum << '\n';
    return 0;
}