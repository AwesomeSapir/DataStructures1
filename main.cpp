#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include "Stack.h"

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
            return;
        } else {
            algRecursive(arr, n-1, sum, arr[n-1]);
            algRecursive(arr, n-1, sum, 0);
        }
    }
}

void algNonRecursive(const vector<int>& arr, int n, int sum){
    Stack stack;
    ItemType curr(n, 0, ItemType::START);
    bool returnFromRec = false;

    do {
        if(returnFromRec){
            curr = stack.pop();
        }
        if(curr.line == ItemType::START){
            if (curr.n == 1){
                if (curr.x != 0){
                    if (arr[0]+curr.x == sum){
                        cout << arr[0] << " " << curr.x << endl;
                    }
                    returnFromRec = true;
                } else {
                    returnFromRec = true;
                }
            } else {
                if (curr.x != 0){
                    if (arr[curr.n-1]+curr.x == sum){
                        cout << arr[curr.n-1] << " " << curr.x << endl;
                    }
                    curr.line = ItemType::AFTER_RETURN;
                    stack.push(curr);
                    curr.n = curr.n-1;
                    curr.line = ItemType::START;
                    returnFromRec = false;
                } else {
                    curr.line = ItemType::AFTER_REC;
                    stack.push(curr);
                    curr.n--;
                    curr.x = arr[curr.n];
                    curr.line = ItemType::START;
                    returnFromRec = false;
                }
            }
        } else if(curr.line == ItemType::AFTER_REC){
            curr.line = ItemType::AFTER_RETURN;
            stack.push(curr);
            curr.n--;
            curr.x = 0;
            curr.line = ItemType::START;
            returnFromRec = false;
        } else if(curr.line == ItemType::AFTER_RETURN){
            returnFromRec = true;
        }
    } while (!stack.isEmpty());
}

void printTime(chrono::time_point<chrono::system_clock, chrono::system_clock::duration> start, chrono::time_point<chrono::system_clock, chrono::system_clock::duration> end){
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    cout << fixed << time_taken << setprecision(2);
    cout << " seconds" << endl;
}

vector<int> getUserInput(int& o_sum){
    int arrSize;
    cin >> arrSize;
    vector<int> arr(arrSize);
    for (int i = 0; i < arrSize; i++) {
        cin >> arr[i];
    }
    cin >> o_sum;
    return arr;
}

int main() {
    ios_base::sync_with_stdio(false);

    int sum;
    vector<int> arr = getUserInput(sum);


    cout << "Iterative algorithm:" << endl;
    auto start = chrono::high_resolution_clock::now();
    algIterative(arr, sum);
    auto end = chrono::high_resolution_clock::now();
    printTime(start, end);

    cout << "Recursive algorithm (recursive version):" << endl;
    start = chrono::high_resolution_clock::now();
    algRecursive(arr, (int)arr.size(), sum, 0);
    end = chrono::high_resolution_clock::now();
    printTime(start, end);

    cout << "Recursive algorithm (iterative version):" << endl;
    start = chrono::high_resolution_clock::now();
    algNonRecursive(arr, (int)arr.size(), sum);
    end = chrono::high_resolution_clock::now();
    printTime(start, end);

    return 0;
}
