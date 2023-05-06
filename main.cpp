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

void algNonRecursive(const vector<int>& arr, int arrSize, int sum){
    Stack stack;
    ItemType curr(arrSize, 0, ItemType::START);
    bool returnFromRec = false;

    do {
        if(returnFromRec){
            curr = stack.pop();
        }
        if(curr.line == ItemType::START){
            if (curr.index == 1){
                if (curr.compared != 0){
                    if (arr[0]+curr.compared == sum){
                        cout << arr[0] << " " << curr.compared << endl;
                    }
                }
                returnFromRec = true;
            } else {
                if (curr.compared != 0){
                    if (arr[curr.index - 1] + curr.compared == sum){
                        cout << arr[curr.index - 1] << " " << curr.compared << endl;
                    }
                    curr.line = ItemType::AFTER_RETURN;
                    stack.push(curr);
                    curr.index = curr.index - 1;
                } else {
                    curr.line = ItemType::AFTER_REC;
                    stack.push(curr);
                    curr.index--;
                    curr.compared = arr[curr.index];
                }
                curr.line = ItemType::START;
                returnFromRec = false;
            }
        } else if(curr.line == ItemType::AFTER_REC){
            curr.line = ItemType::AFTER_RETURN;
            stack.push(curr);
            curr.index--;
            curr.compared = 0;
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
    cout << fixed << time_taken << setprecision(9);
    cout << " seconds" << endl;
}

vector<int> getUserInput(int& o_sum) noexcept(false){
    int arrSize;
    cin >> arrSize;
    if(arrSize <= 0){
        throw invalid_argument("wrong input");
    }
    vector<int> arr(arrSize);
    for (int i = 0; i < arrSize; i++) {
        cin >> arr[i];
        if(arr[i] <= 0){
            throw invalid_argument("wrong input");
        }
    }
    cin >> o_sum;
    if(o_sum <= 0){
        throw invalid_argument("wrong input");
    }
    return arr;
}

int main() {
    ios_base::sync_with_stdio(false);

    int sum;
    vector<int> arr;
    try {
        arr = getUserInput(sum);
    } catch (invalid_argument& e) {
        cout << e.what();
        exit(1);
    }

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
