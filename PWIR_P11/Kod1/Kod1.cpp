#include "mpi.h"
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>

void mainProcess(int size) {
    srand(time(NULL));

    int totalElements;
    std::cout << "Podaj wielkosc wektora: ";
    std::cin >> totalElements;

    int elementsPerProcess = totalElements / (size - 1);
    int remainingElements = totalElements % (size - 1);

    unsigned int* va = new unsigned int[totalElements];
    unsigned int* vb = new unsigned int[totalElements];
    unsigned int* vc = new unsigned int[totalElements];

    for (int i = 0; i < totalElements; i++) {
        va[i] = rand() % 10;
        vb[i] = rand() % 10;
        vc[i] = 0;
    }

    MPI_Bcast(&totalElements, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(va, totalElements, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(vb, totalElements, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    int* counts = new int[size - 1];
    int* displacements = new int[size - 1];

    for (int i = 0; i < size - 1; i++) {
        counts[i] = elementsPerProcess;
        if (remainingElements > 0) {
            counts[i]++;
            remainingElements--;
        }
        displacements[i] = (i > 0) ? displacements[i - 1] + counts[i - 1] : 0;
    }

    MPI_Request* requests = new MPI_Request[size - 1];
    MPI_Status* statuses = new MPI_Status[size - 1];
    for (int i = 0; i < size - 1; i++) {
        MPI_Irecv(vc + displacements[i], counts[i], MPI_UNSIGNED, i + 1, 0, MPI_COMM_WORLD, &requests[i]);
    }
    MPI_Waitall(size - 1, requests, statuses);

    for (int i = 0; i < totalElements; i++) printf("%d\t", va[i]);
    printf("\r\n");
    for (int i = 0; i < totalElements; i++) printf("%d\t", vb[i]);
    printf("\r\n");
    for (int i = 0; i < totalElements; i++) printf("%d\t", vc[i]);
    printf("\r\n");

    delete[] va;
    delete[] vb;
    delete[] vc;
    delete[] requests;
    delete[] statuses;
    delete[] counts;
    delete[] displacements;
}

void workerProcess(int id, int size) {
    int totalElements;
    MPI_Bcast(&totalElements, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int elementsPerProcess = totalElements / (size - 1);
    int remainingElements = totalElements % (size - 1);

    int myElements = elementsPerProcess;
    if (id <= remainingElements) {
        myElements++;
    }

    unsigned int* v = new unsigned int[myElements];
    unsigned int* va = new unsigned int[totalElements];
    unsigned int* vb = new unsigned int[totalElements];

    MPI_Bcast(va, totalElements, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    MPI_Bcast(vb, totalElements, MPI_UNSIGNED, 0, MPI_COMM_WORLD);

    int startIdx = (id - 1) * elementsPerProcess + std::min(id - 1, remainingElements);
    for (int i = 0; i < myElements; i++) {
        v[i] = va[startIdx + i] + vb[startIdx + i];
    }

    MPI_Send(v, myElements, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);

    delete[] v;
    delete[] va;
    delete[] vb;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        mainProcess(size);
    }
    else {
        workerProcess(rank, size);
    }

    MPI_Finalize();
    return 0;
}
