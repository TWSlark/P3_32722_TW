#include <iostream>
#include <omp.h>
#include <vector>
#include <cmath>

double calculateVectorLength(const std::vector<double>& vec) {
    double sum = 0.0;
#pragma omp parallel
    {
        double local_sum = 0.0;

#pragma omp sections
        {
#pragma omp section
            {
                for (int i = 0; i < vec.size() / 4; ++i) {
                    local_sum += vec[i] * vec[i];
                }
            }

#pragma omp section
            {
                for (int i = vec.size() / 4; i < vec.size() / 2; ++i) {
                    local_sum += vec[i] * vec[i];
                }
            }

#pragma omp section
            {
                for (int i = vec.size() / 2; i < 3 * vec.size() / 4; ++i) {
                    local_sum += vec[i] * vec[i];
                }
            }

#pragma omp section
            {
                for (int i = 3 * vec.size() / 4; i < vec.size(); ++i) {
                    local_sum += vec[i] * vec[i];
                }
            }
        }

#pragma omp atomic
        sum += local_sum;
    }

    return std::sqrt(sum);
}

int main() {
    std::vector<double> vec = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };

    double length = calculateVectorLength(vec);

    std::cout << "Vector length: " << length << std::endl;

    return 0;
}
