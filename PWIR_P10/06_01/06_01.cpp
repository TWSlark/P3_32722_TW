#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <windows.h>
#include <omp.h>

void wait(int x) {
    Sleep(x);
}

int main() {
    int32_t i;
    uint32_t n = 10;
    auto start = std::chrono::high_resolution_clock::now();

    // Przypadek 1: Działanie bez klauzuli nowait
#pragma omp parallel num_threads(2) default(shared) private(i)
    {
#pragma omp sections
        {
#pragma omp section
            {
                wait(2000);
                printf("Sections (without nowait) - Thread %d working...\n", omp_get_thread_num());
            }

#pragma omp section
            {
                wait(4000);
                printf("Sections (without nowait) - Thread %d working...\n", omp_get_thread_num());
            }
        }

#pragma omp for
        for (i = 0; i < n; i++) {
            printf("Iteration %d execute thread %d.\n", i, omp_get_thread_num());
            wait(400);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    printf("Parallel normal way (without nowait) %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    // Przypadek 2: Działanie z klauzulą nowait
    auto start_with_nowait = std::chrono::high_resolution_clock::now();

#pragma omp parallel num_threads(2) default(shared) private(i)
    {
#pragma omp sections nowait
        {
#pragma omp section
            {
                wait(2000);
                printf("Sections (with nowait) - Thread %d working...\n", omp_get_thread_num());
            }

#pragma omp section
            {
                wait(4000);
                printf("Sections (with nowait) - Thread %d working...\n", omp_get_thread_num());
            }
        }

#pragma omp for
        for (i = 0; i < n; i++) {
            printf("Iteration %d execute thread %d.\n", i, omp_get_thread_num());
            wait(400);
        }
    }

    auto end_with_nowait = std::chrono::high_resolution_clock::now();
    printf("Parallel normal way (with nowait) %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end_with_nowait - start_with_nowait).count());

    // Przypadek 3: Działanie na większej ilości wątków
    auto start_multiple_threads = std::chrono::high_resolution_clock::now();

#pragma omp parallel num_threads(4) default(shared) private(i)
    {
#pragma omp sections nowait
        {
#pragma omp section
            {
                wait(2000);
                printf("Sections - Thread %d working...\n", omp_get_thread_num());
            }

#pragma omp section
            {
                wait(4000);
                printf("Sections - Thread %d working...\n", omp_get_thread_num());
            }
        }

#pragma omp for
        for (i = 0; i < n; i++) {
            printf("Iteration %d execute thread %d.\n", i, omp_get_thread_num());
            wait(400);
        }
    }

    auto end_multiple_threads = std::chrono::high_resolution_clock::now();
    printf("Parallel normal way (multiple threads) %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end_multiple_threads - start_multiple_threads).count());

    return 0;
}