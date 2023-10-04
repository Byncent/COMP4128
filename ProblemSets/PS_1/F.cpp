#include <iostream>
using namespace std;
 
const int N = 1010;
int arr[N];

// An optimized version of Bubble Sort
void bubbleSort(int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                cout << j << ' ' << j+1 << '\n';
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}
 
// Driver program to test above functions
int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++){
        cin >> arr[i];
    }
    bubbleSort(n);
    return 0;
}