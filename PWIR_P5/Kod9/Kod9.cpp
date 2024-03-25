#include <thread>
#include <cstdio>
#include <windows.h>

thread_local unsigned int counter = 0;
thread_local unsigned int local = 0;
unsigned int global = 0;

void increment(int id, int* tablica) {
    /*
    for (int i = 0; i < 100; i++) {
        tablica[i] = rand() % 10;
        //counter++;
        //Sleep(300);
    }

    //ten blok wykona się tylko raz mimo, że wątków jest więcej
    if (id == 1) {
        //printf("%u\n", counter);
        for (int i = 0; i < 100; i++) {
            printf("%d ", tablica[i]);
        }
    }
    */

    int suma = 0;

    for (int i = id * 10; i < (id + 1) * 10; i++) {
        suma += tablica[i];
    }

    local += suma;
    global += suma;

    printf("Watek %d id -> wartosc: %u\n", id, local);

}

int main() {
    srand(time(NULL));

    int tablica[100];
    const int nthreads = 10;

    for (int i = 0; i < 100; i++) {
        tablica[i] = rand() % 10;
    }

    std::thread threads[nthreads];
    for (int i = 0; i < nthreads; ++i) {
        threads[i] = std::thread(increment, i, tablica);
    }

    for (int i = 0; i < nthreads; ++i) {
        threads[i].join();
    }

    printf("Suma thread_local: %d\n", local);
    printf("Suma globalna: %d\n", global);

    return 0;
}