#include "../helpers.c"
#include <sys/time.h>

#define SIZE 50
#define SIZE_PRINT_LIMIT 100

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"



int main(){
    printf("Sorting array with %d elements\n", SIZE);

    unsigned int* array = (int*) malloc(sizeof(int) * SIZE);
    init_matrix(array, SIZE);
    
    return 0;
}