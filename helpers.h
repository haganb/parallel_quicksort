#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void init_matrix(unsigned int* matrix, int N);
bool check_if_sorted(unsigned int* matrix, int N);
bool compare_matrix(unsigned int* device_matrix, unsigned int* host_matrix, int N);
void print_matrix(unsigned int* matrix, int N);