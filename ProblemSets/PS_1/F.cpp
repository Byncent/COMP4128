#include <iostream>
using namespace std;

typedef long long ll;

const int N = 1010;
ll arr[N];

// An optimized version of Bubble Sort
void bubbleSort(int n)
{
    string str;
    ll invCounter = 0;
    ll i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                str +=  to_string(j+1) + ' ' + to_string(j+2) + '\n';
                invCounter ++;
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }

    cout << invCounter << '\n';
    cout << str << '\n';
}
 
// Driver program to test above functions
int main()
{
    ll n;
    cin >> n;
    for(ll i = 0; i < n; i ++){
        cin >> arr[i];
    }
    bubbleSort(n);
    return 0;
}