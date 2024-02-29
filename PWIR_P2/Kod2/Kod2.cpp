#include <cstdio>
#include <thread>
#include <windows.h>
#include <iostream>
#include <vector>

void action(int id) {
    printf("Uruchamiam watek %d\n", id);
    Sleep(5 * 1000); //5 sekund
    printf("Koncze watek %d\n", id);
}

int main() {

    int thread_count;

    std::cout << "Podaj ilosc watkow: ";
    std::cin >> thread_count;

    std::vector<std::thread*> wektor;

    //alokacja tablicy, która będzie przechowywać wskaźniki na wątki
    //std::thread** threads = new std::thread * [thread_count];

    //otwieranie wątków
    for (int i = 0; i < thread_count; i++) {
        std::thread* wskaznik = new std::thread(action, i);
        wektor.push_back(wskaznik);
    }

    //watki pracują, ale trzeba je zsynchronizować
    //for (int i = 0; i < thread_count; i++) {
    //    threads[i]->join();
    //}

    //alokowaliśmy pamięć więc pasuje ją zwolnić
    //for (int i = 0; i < thread_count; i++) {
    //    delete threads[i];
    //}
    //delete[] threads;

    for (auto wskaznik : wektor) {
        wskaznik->join();
    }

    for (auto wskaznik : wektor) {
        delete wskaznik;
    }

    printf("Koniec programu \r\n");

    return 0;
}