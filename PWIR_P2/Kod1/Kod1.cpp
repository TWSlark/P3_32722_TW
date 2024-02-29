#include <cstdio>
#include <thread>
#include <windows.h>
#include <iostream>

int action(int id, int czas) {
    printf("Uruchamiam watek %d\n", id);
    Sleep(czas * 1000); //10 sekund
    printf("Koncze watek %d\n", id);
    return 0;
}

int main() {

    int czas;

    std::cout << "Podaj czas w s: ";
    std::cin >> czas;

    //tworzenie wątku
    std::thread t1(action, 1, czas); //konstruktor klasy t1 przyjmuje minimum wskaźnik na funckje do wykonania
    std::thread::id t1_id = t1.get_id();
    std::thread t2(action, 2, czas); //funckja ta może coś zwracać, ale może zwaracać też void
    std::thread::id t2_id = t2.get_id();
    std::thread t3(action, 3, czas); //dalsze parametry zostaną przekazane do podanej funckji
    std::thread::id t3_id = t3.get_id();

    std::cout << "ID: " << t1_id << std::endl;
    std::cout << "ID: " << t2_id << std::endl;
    std::cout << "ID: " << t3_id << std::endl;

    t1.join();  //synchronizacja
    t2.join();  //wątek główny ma tu poczekać na te 3 wątki
    t3.join();  //inaczej program by się zakończył wcześniej bo wątki trwają minimum 10 sekund

    printf("Koniec programu \r\n");

    return 0;
}