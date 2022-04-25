#include "helpers.h"
// init_array: Method used to populate array with randomized values
void init_array(unsigned int* array, int SIZE){
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++){
        array[i] = rand () % SIZE;
    }
}

// swap_numbers: Used to swap to numbers in an array
void swap_numbers(int* one, int* two){
    int temp = *one;
    *one = *two;
    *two = temp;
}

// check_if_sorted: iterate through values in array, ensure that it is in proper order
bool check_if_sorted(unsigned int* array, int SIZE){
    for(int i = 0; i < SIZE-1; i++){
        if(array[i] > array[i+1]){
            return false;
        }
    }
    return true;
}

// print_matrix: helper method to print all values in array
void print_array(unsigned int* array, int SIZE){
    printf("[");
    for(int i = 0; i < SIZE; i++){
        if(i != (SIZE-1)){
            printf("%d, ", array[i]);
        }else{
            printf("%d]\n", array[i]);
        }
    }
}

