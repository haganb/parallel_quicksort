#include "openMP_quicksort.h"
#include "sequential_quicksort.h"
#include "pthread_quicksort.h"

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

int main(){
    int SIZE = 5000;
    printf("Number of elements in unsorted arrays: %d\n", SIZE);
    unsigned int* array = (int*) malloc(sizeof(int) * SIZE);
    init_matrix(array, SIZE);

    float sequential_benchmark = get_cpu_benchmark(array, SIZE);
    float pthread_benchmark = get_pthread_benchmark(array, SIZE);
    float omp_benchmark = get_omp_benchmark(array, SIZE);
    return 0;
}