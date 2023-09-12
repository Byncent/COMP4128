#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    int num1;
    cin >> num1;
    
    for(int i = 0; i < num1; i++){

        int num2;
        cin >> num2;

        long long int sum = 0;
        int prev = 0, curr = 0, temp = 0;

        for (int j = 0; j < num2; j++) {

            cin >> curr;

            if((curr>=0 && prev<=0) || ((curr<=0 && prev>=0))){
                sum += temp;
                temp = curr;
                prev = curr;
            } else{
                if (curr > temp){
                    temp = curr;
                }
                prev = curr;
            }
        }
        sum += temp;
        cout << sum << '\n';
    }
}