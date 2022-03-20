
#include "../helpers.c"
#include "../openMP/openMP_quicksort.c"
#include "../sequential/sequential_quicksort.c"
#include "../pthread/pthread_quicksort.c"

#ifdef SIZE
#define SIZE 5000000
#endif
#define SIZE_PRINT_LIMIT 100

// For pretty printing
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"





int main(){
    printf("Hello!\n");

    return 0;
}