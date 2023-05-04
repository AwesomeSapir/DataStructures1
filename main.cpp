#include <iostream>
#include <vector>

using namespace std;

void algIterative(const vector<int>& arr, int sum){
    for (int i = 0; i < arr.size()-1; i++) {
        for (int j = i+1; j < arr.size(); j++) {
            if (arr[i]+arr[j] == sum){
                cout << arr[i] << " " << arr[j] << endl;
            }
        }
    }
}

void algRecursive(const vector<int>& arr, int n, int sum, int x){
    if (n == 1){
        if (x != 0){
            if (arr[0]+x == sum){
                cout << arr[0] << " " << x << endl;
                return;
            }
        } else {
            return;
        }
    } else {
        if (x != 0){
            if (arr[n-1]+x == sum){
                cout << arr[n-1] << " " << x << endl;
            }
            algRecursive(arr, n-1, sum, x);
        } else {
            algRecursive(arr, n-1, sum, arr[n-1]);
            algRecursive(arr, n-1, sum, 0);
        }
    }
}



int main() {
    vector<int> arr = {1, 9, 7, 8, 9, 15};
    int sum = 16;
    cout << "iterative:" << endl;
    algIterative(arr, sum);
    cout << "recursive:" << endl;
    algRecursive(arr, arr.size(), sum, 0);
    return 0;
}
