#include <thread>
#include <cstdio>
#include <windows.h>
#include <atomic>

std::atomic<unsigned int> counter(0);

void increment() {
    for (int i = 0; i < 10; i++) {
        counter.fetch_add(1, std::memory_order_relaxed);
        Sleep(2000);
    }
}

void parity() {
    for (int i = 0; i < 10; i++) {
        unsigned int value = counter.load(std::memory_order_relaxed);
        if (value % 2) {
            printf("%u jest nieparzyste\r\n", value);
        }
        else {
            printf("%u jest parzyste\r\n", value);
        }
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