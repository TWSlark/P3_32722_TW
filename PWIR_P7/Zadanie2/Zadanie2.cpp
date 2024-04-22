#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;

atomic<bool> done(false);

bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

void bogoSort(int arr[], int n, int numThreads) {
    vector<thread> threads;

    for (int i = 0; i < numThreads; i++) {
        threads.push_back(thread([&] {

            int* localArr = new int[n];
            copy(arr, arr + n, localArr);

            while (!done) {
                random_shuffle(localArr, localArr + n);
                if (isSorted(localArr, n)) {
                    copy(localArr, localArr + n, arr);
                    done = true;
                    break;
                }
            }

            delete[] localArr;
        }));
    }

    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    int arr[] = { 5, 2, 0, 8, 1, 9, 3, };
    int n = sizeof(arr) / sizeof(arr[0]);
    int numThreads = 4;

    bogoSort(arr, n, numThreads);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
