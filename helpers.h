#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void init_array(unsigned int* array, int SIZE);
void swap_numbers(int* one, int* two);
bool check_if_sorted(unsigned int* array, int SIZE);
void print_array(unsigned int* array, int SIZE);

#endif