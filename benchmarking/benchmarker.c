#include <time.h>
#include <stdlib.h>

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

// get_cpu_benchmark: method to use radix sort on CPU and benchmark
float get_cpu_benchmark(unsigned int *unsorted_matrix, int SIZE, int SIZE_PRINT_LIMIT){
    // Set up benchmarking tools
    struct timeval begin;
    struct timeval end;
    gettimeofday(&begin, NULL);

    // Actual sorting
    //TODO: ADD SORTING

    // Finish benchmarking
    gettimeofday(&end, NULL);
    float host_time = (float)((end.tv_usec - begin.tv_usec)) / 1000;
    printf("Elapsed time for CPU-bound sorting (ms): %f\n", host_time);

    // Ensure that device is properly sorted
    if(check_if_sorted(unsorted_matrix, SIZE)){
        printf("Host matrix was sorted ");
        printf(ANSI_GREEN "successfully." ANSI_RESET "\n");

        if(SIZE < SIZE_PRINT_LIMIT){
            printf("Good sort: ");
            print_matrix(unsorted_matrix, SIZE);
        }
    }else{
        printf("ERROR: Host matrix sorting ");
        printf(ANSI_RED "failed." ANSI_RESET "\n");
        if(SIZE < SIZE_PRINT_LIMIT){
            printf("Bad sort: ");
            print_matrix(unsorted_matrix, SIZE);
        }
    }
    printf("\n");
    return host_time;
}