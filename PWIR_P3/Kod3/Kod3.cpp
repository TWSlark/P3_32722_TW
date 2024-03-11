#include <chrono>
#include <cstdio>
#include <windows.h>
#include <fstream>
#include <iostream>

int main() {
    /*
    auto start = std::chrono::steady_clock::now();
    std::ifstream file("plik.txt");
    auto end = std::chrono::steady_clock::now();

    std::cout << "Czas otwierania pliku: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mikrosekund" << std::endl;

    start = std::chrono::steady_clock::now();
    file.close();
    end = std::chrono::steady_clock::now();

    std::cout << "Czas zamykania pliku: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " mikrosekund" << std::endl;
    */

    auto start = std::chrono::steady_clock::now();

    int n = 40;
    int a = 0, b = 1, fib;

    for (int i = 2; i <= n; ++i) {
        fib = a + b;
        std::cout << fib << " ";
        a = b;
        b = fib;
    }

    std::cout << std::endl;

    auto end = std::chrono::steady_clock::now();

    std::cout << "Czas: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " milisekund" << std::endl;

    return 0;
}