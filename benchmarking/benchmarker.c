#include "../openMP/openMP_quicksort.h"
#include "../sequential/sequential_quicksort.h"
#include "../pthread/pthread_quicksort.h"

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