#include <sys/time.h>
#include <pthread.h>
#include "../helpers.c"

#define DEBUG

#define SIZE 50
#define SIZE_PRINT_LIMIT 100

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

/* QUICKSORT METHODS */
void swap_numbers(int* one, int* two){
    int temp = *one;
    *one = *two;
    *two = temp;
}

int partition(int* array, int low, int high){
    int pivot = array[high];
    int i = low - 1;
    for(int j = low; j <= high - 1; j++){
        if(array[j] <= pivot){
            i++;
            swap_numbers(&array[i], &array[j]);
        }
    }
    swap_numbers(&array[i+1], &array[high]);
    return i + 1;
}

void pthread_quicksort(int* array){

}

// Wrapper function for quicksort that handles pthreading
void run_pthread_quicksort(int* array){

}

/* BENCHMARKING METHODS */
float get_pthread_benchmark(unsigned int* array){
    struct timeval begin;
    struct timeval end;

    gettimeofday(&begin, NULL);

    // Actual sorting

    // Finish benchmarking and process
    gettimeofday(&end, NULL);
    float time = (float)((end.tv_usec - begin.tv_usec)) / 1000;
    printf("Elapsed time for PTHREAD concurrent sorting (ms): %f\n", time);

    if(check_if_sorted(array, SIZE)){
        printf("Matrix was sorted ");
        printf(ANSI_GREEN "successfully." ANSI_RESET "\n");
        
        #ifdef DEBUG
        if(SIZE < SIZE_PRINT_LIMIT){
            printf("Good sort: ");
            print_matrix(array, SIZE);
        }
        #endif
    }else{
        printf("ERROR: Matrix sorting ");
        printf(ANSI_RED "failed." ANSI_RESET "\n");

        #ifdef DEBUG
        if(SIZE < SIZE_PRINT_LIMIT){
            printf("Bad sort: ");
            print_matrix(array, SIZE);
        }
        #endif
    }
    printf("\n");
    return time;
}


/* MAIN METHOD */
int main(){
    printf("Sorting array with %d elements using PTHREADS...\n", SIZE);
    unsigned int* array = (int*) malloc(sizeof(int) * SIZE);
    init_matrix(array, SIZE);

    
    return 0;
}