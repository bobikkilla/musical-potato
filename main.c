#include "algo_lab.h"

int main(int argc, char** argv) {
    if(strcmp(argv[1],"smooth") == 0) {
        test_full_random(2, power_of_10(3),power_of_10(7));
        test_full_random(2, power_of_10(6),power_of_10(7));
        test_full_random(2, power_of_10(9),power_of_10(7));

        test_full_random(2, power_of_10(3),power_of_10(8));
        test_full_random(2, power_of_10(6),power_of_10(8));
        test_full_random(2, power_of_10(9),power_of_10(8));

        test_sorted_subarrays(2,power_of_10(1),power_of_10(7));
        test_sorted_subarrays(2,power_of_10(3),power_of_10(7));
        test_sorted_subarrays(2,power_of_10(5),power_of_10(7));
        test_sorted_subarrays(2,power_of_10(7),power_of_10(7));

        test_presorted_swaps(2,power_of_10(3),power_of_10(7));
        test_presorted_swaps(2,power_of_10(4),power_of_10(7));
        test_presorted_swaps(2,power_of_10(5),power_of_10(7));

        test_same_elements(2,10,power_of_10(7));
        test_same_elements(2,25,power_of_10(7));
        test_same_elements(2,50,power_of_10(7));
        test_same_elements(2,70,power_of_10(7));
        test_same_elements(2,90,power_of_10(7));

        test_backward_sorted(2,power_of_10(7));

        test_sorted_subarrays(2,power_of_10(1),power_of_10(8));
        test_sorted_subarrays(2,power_of_10(3),power_of_10(8));
        test_sorted_subarrays(2,power_of_10(5),power_of_10(8));
        test_sorted_subarrays(2,power_of_10(7),power_of_10(8));

        test_presorted_swaps(2,power_of_10(3),power_of_10(8));
        test_presorted_swaps(2,power_of_10(4),power_of_10(8));
        test_presorted_swaps(2,power_of_10(5),power_of_10(8));

        test_same_elements(2,10,power_of_10(8));
        test_same_elements(2,25,power_of_10(8));
        test_same_elements(2,50,power_of_10(8));
        test_same_elements(2,70,power_of_10(8));
        test_same_elements(2,90,power_of_10(8));

        test_backward_sorted(2,power_of_10(8));
    }
    else if(strcmp(argv[1],"patience") == 0) {
        test_full_random(1, power_of_10(3),power_of_10(7));
        test_full_random(1, power_of_10(6),power_of_10(7));
        test_full_random(1, power_of_10(9),power_of_10(7));

        test_full_random(1, power_of_10(3),power_of_10(8));
        test_full_random(1, power_of_10(6),power_of_10(8));
        test_full_random(1, power_of_10(9),power_of_10(8));
        
        test_sorted_subarrays(1,power_of_10(1),power_of_10(7));
        test_sorted_subarrays(1,power_of_10(3),power_of_10(7));
        test_sorted_subarrays(1,power_of_10(5),power_of_10(7));
        test_sorted_subarrays(1,power_of_10(7),power_of_10(7));

        test_presorted_swaps(1,power_of_10(3),power_of_10(7));
        test_presorted_swaps(1,power_of_10(4),power_of_10(7));
        test_presorted_swaps(1,power_of_10(5),power_of_10(7));

        test_same_elements(1,10,power_of_10(7));
        test_same_elements(1,25,power_of_10(7));
        test_same_elements(1,50,power_of_10(7));
        test_same_elements(1,70,power_of_10(7));
        test_same_elements(1,90,power_of_10(7));

        test_backward_sorted(1,power_of_10(7));

        test_sorted_subarrays(1,power_of_10(1),power_of_10(8));
        test_sorted_subarrays(1,power_of_10(3),power_of_10(8));
        test_sorted_subarrays(1,power_of_10(5),power_of_10(8));
        test_sorted_subarrays(1,power_of_10(7),power_of_10(8));

        test_presorted_swaps(1,power_of_10(3),power_of_10(8));
        test_presorted_swaps(1,power_of_10(4),power_of_10(8));
        test_presorted_swaps(1,power_of_10(5),power_of_10(8));

        test_same_elements(1,10,power_of_10(8));
        test_same_elements(1,25,power_of_10(8));
        test_same_elements(1,50,power_of_10(8));
        test_same_elements(1,70,power_of_10(8));
        test_same_elements(1,90,power_of_10(8));

        test_backward_sorted(1,power_of_10(8));
    }
    else if(strcmp(argv[1],"gnome") == 0) {
        test_full_random(3, power_of_10(3),power_of_10(5));
        test_full_random(3, power_of_10(6),power_of_10(5));
        test_full_random(3, power_of_10(9),power_of_10(5));

        test_sorted_subarrays(3,power_of_10(1),power_of_10(5));
        test_sorted_subarrays(3,power_of_10(2),power_of_10(5));
        test_sorted_subarrays(3,power_of_10(3),power_of_10(5));
        test_sorted_subarrays(3,power_of_10(4),power_of_10(5));
        test_sorted_subarrays(3,power_of_10(5),power_of_10(5));

        test_presorted_swaps(3,power_of_10(2),power_of_10(5));
        test_presorted_swaps(3,power_of_10(3),power_of_10(5));
        test_presorted_swaps(3,power_of_10(4),power_of_10(5));

        test_same_elements(3,10,power_of_10(5));
        test_same_elements(3,25,power_of_10(5));
        test_same_elements(3,50,power_of_10(5));
        test_same_elements(3,70,power_of_10(5));
        test_same_elements(3,90,power_of_10(5));

        test_backward_sorted(3,power_of_10(5));
    }
    else if(strcmp(argv[1],"test") == 0){ 
        test_same_elements(2, 50,power_of_10(6));
        test_backward_sorted(2,power_of_10(6));
        test_presorted_swaps(2,power_of_10(3),power_of_10(6));
        test_sorted_subarrays(2,power_of_10(3),power_of_10(6));
        test_full_random(2, power_of_10(3),power_of_10(6));
    }
}