#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>

#define VECTOR_SIZE 10000

double calculateVectorLengthSequential(const std::vector<double>& vec) {
    double sum = 0.0;
    for (double x : vec) {
        sum += x * x;
    }
    return std::sqrt(sum);
}

double calculateVectorLengthParallel(const std::vector<double>& vec) {
    double sum = 0.0;
#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        sum += vec[i] * vec[i];
    }
    return std::sqrt(sum);
}

int main() {
    std::srand(std::time(nullptr));
    std::vector<double> vec(VECTOR_SIZE);

    // Wypelnianie wektora losowymi wartosciami
    for (int i = 0; i < VECTOR_SIZE; ++i) {
        vec[i] = static_cast<double>(std::rand() % 11); // Losowe liczby z zakresu 0-10
    }

    // Obliczanie dlugosci wektora w sposob sekwencyjny
    auto startSeq = std::chrono::high_resolution_clock::now();
    double lengthSeq = calculateVectorLengthSequential(vec);
    auto endSeq = std::chrono::high_resolution_clock::now();

    printf("Dlugosc wektora (bez zrownoleglonego): %.2f\n", lengthSeq);
    printf("Czas obliczen (bez zrownoleglonego): %lld us\n", std::chrono::duration_cast<std::chrono::microseconds>(endSeq - startSeq).count());

    // Obliczanie dlugosci wektora w sposob zrownoleglonego
    auto startPar = std::chrono::high_resolution_clock::now();
    double lengthPar = calculateVectorLengthParallel(vec);
    auto endPar = std::chrono::high_resolution_clock::now();

    printf("Dlugosc wektora (zrownoleglonego): %.2f\n", lengthPar);
    printf("Czas obliczen (zrownoleglonego): %lld us\n", std::chrono::duration_cast<std::chrono::microseconds>(endPar - startPar).count());

    return 0;
}