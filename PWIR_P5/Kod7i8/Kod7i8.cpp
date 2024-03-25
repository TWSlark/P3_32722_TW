#include <thread>
#include <cstdio>
#include <windows.h>
#include <mutex>

std::mutex counter_mutex;
unsigned int counter = 0;

void increment() {
    for (int i = 0; i < 10; i++) {
        counter_mutex.lock();
        counter++;
        counter_mutex.unlock();
        Sleep(2000);
    }
}

void parity() {
    for (int i = 0; i<10; i++) {
        counter_mutex.lock();        
        if (counter % 2) {
            printf("%u jest nieparzyste\r\n", counter);
        }
        else {
            printf("%u jest parzyste\r\n", counter);
        }
        counter_mutex.unlock();
        Sleep(2000);
    }
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();

    std::thread inc(increment);
    std::thread par(parity);

    inc.join();
    par.join();

    printf("Done\r\n");

    auto end = std::chrono::high_resolution_clock::now();
    printf("Czas wykonania: %llu ms\r\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    return 0;
}