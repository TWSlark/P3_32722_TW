#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<iomanip>
#include<thread>
#include<mutex>

using namespace std;

int cr_pt = 0, sq_pt = 0;
mutex mtx;

void monteCarlo(int intrval) {
    double x, y, r;
    srand(time(NULL));
    for (int i = 0; i < intrval; i++) {
        x = double((1 + rand() % intrval)) / intrval;
        y = double((1 + rand() % intrval)) / intrval;
        r = x * x + y * y;
        if (r <= 1) {
            lock_guard<mutex> guard(mtx);
            cr_pt++;
        }
        lock_guard<mutex> guard(mtx);
        sq_pt++;
    }
}

int main() {
    cout.setf(ios::fixed);

    int intrval = 1000;
    double pi;

    thread t1(monteCarlo, intrval);
    thread t2(monteCarlo, intrval);

    t1.join();
    t2.join();

    pi = double(4 * cr_pt) / sq_pt;
    cout << "Final pi: " << pi << endl;

    return 0;
}