#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <iostream>

#define SIZE 40
#define watki 4

void add(int id, int* a, int* b, int* c) {
    int start = id * 10;
    int koniec = start + 10;
    for (int i = start; i < koniec; ++i) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    srand(time(NULL));
    int a[SIZE];
    int b[SIZE];
    int c[SIZE];

    for (int i = 0; i < SIZE; i++) {
        a[i] = rand() % 100 + 1; //1 do 100
        b[i] = rand() % 100 + 1;
    }

    //wypisanie na ekranie A
    for (int i = 0; i < SIZE; i++) {
        printf("%u ", a[i]);
    }
    printf("\n");

    //wypisanie na ekranie B
    for (int i = 0; i < SIZE; i++) {
        printf("%u ", b[i]);
    }
    printf("\n");

    auto start = std::chrono::steady_clock::now();

    std::thread** threads = new std::thread * [watki];
    for (int i = 0; i < watki; i++) {
        threads[i] = new std::thread(add, i, a, b, c); //wykorzystuje i jako id danego wątku
    }

    for (int i = 0; i < watki; i++) {
        threads[i]->join();
    }

    auto end = std::chrono::steady_clock::now();
    std::cout << "Czas: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milisekund" << std::endl;

    for (int i = 0; i < watki; i++) {
        delete threads[i];
    }
    delete[] threads;

    //wypisanie na ekranie C
    for (int i = 0; i < SIZE; i++) {
        printf("%u ", c[i]);
    }

    return 0;
}