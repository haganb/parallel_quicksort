#include "openMP_quicksort.h"
#include "sequential_quicksort.h"
#include "pthread_quicksort.h"

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

// Global Variables
int SIZE = 10000;
int PRINT_SIZE_LIMIT = 100; // the maximum number of elements an array can have while still being allowed to print

void compare_results(float sequential, float pthread, float omp){

}

int main(){

    printf("Number of elements in unsorted arrays: %d\n", SIZE);
    unsigned int* array = (int*) malloc(sizeof(int) * SIZE);
    init_array(array, SIZE);

    float sequential_benchmark = get_cpu_benchmark(array, SIZE);
    float pthread_benchmark = get_pthread_benchmark(array, SIZE);
    float omp_benchmark = get_omp_benchmark(array, SIZE);
    compare_results(sequential_benchmark, pthread_benchmark, omp_benchmark);

    free(array);
    return 0;
}