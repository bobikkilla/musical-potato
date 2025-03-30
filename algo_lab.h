#ifndef LABORATORY
#define LABORATORY

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int power_of_10(int stepen);

/************************sorting algorithms****************************/

void gnome_sort(int* first_element, int* last_element);

void patience_sort(int *first_element, int *last_element);

void smooth_sort(int* first_element, int* last_element);

// ********************** tests **************************

void test_full_random(int number_of_sorting_algorithm, int elements_module, int num_of_elements);

void test_sorted_subarrays(int number_of_sorting_algorithm, int subarray_module, int num_of_elements);

void test_presorted_swaps(int number_of_sorting_algorithm, int number_of_swaps, int num_of_elements);

void test_same_elements(int number_of_sorting_algorithm, int percent_of_same_elements, int num_of_elements);

void test_backward_sorted(int number_of_sorting_algorithm, int num_of_elements);

#endif