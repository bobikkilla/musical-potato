#include "algo_lab.h"
// 1 = patience sort, 2 = smooth sort, 3 = gnome sort

int comp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int comp_backward(const void *a, const void *b) {
  return (*(int *)b - *(int *)a);
}

int power_of_10(int stepen) {
  int to_return = 10;
  if (stepen == 0) {
    return 1;
  } else {
    for (int i = 0; i < stepen - 1; i++) {
      to_return *= 10;
    }
  }
  return to_return;
}

// 1 = patience sort, 2 = smooth sort, 3 = gnome sort
void test_full_random(int number_of_sorting_algorithm, int elements_module,
                      int num_of_elements) {
  double summary_time;
  int number_of_elements = num_of_elements;
  for (int test_count = 0; test_count < 10; test_count++) {
    srand(time(NULL));
    int *array;
    array = malloc(sizeof(int) * number_of_elements);
    for (int i = 0; i < number_of_elements; i++) {
      array[i] = rand() % (elements_module + 1);
    }
    time_t start, end;
    start = clock();
    if (number_of_sorting_algorithm == 1) {
      patience_sort(array, array + (int)(number_of_elements - 1));
    } else if (number_of_sorting_algorithm == 2) {
      smooth_sort(array, array + (int)(number_of_elements - 1));
    } else if (number_of_sorting_algorithm == 3) {
      gnome_sort(array, array + (int)(number_of_elements - 1));
    }
    end = clock();
    summary_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    free(array);
  }
  if (number_of_sorting_algorithm == 1) {
    printf("\n\nСреднее время сортировки массива %d случайных чисел по модулю "
           "%d\n",
           number_of_elements, elements_module);
    printf("Для терпеливой сортировки составило %f секунд\n\n",
           summary_time / 10);
  } else if (number_of_sorting_algorithm == 2) {
    printf("\n\nСреднее время сортировки массива %d случайных чисел по модулю "
           "%d\n",
           number_of_elements, elements_module);
    printf("Для плавной сортировки составило %f секунд\n\n", summary_time / 10);
  } else if (number_of_sorting_algorithm == 3) {
    printf("\n\nСреднее время сортировки массива %d случайных чисел по модулю "
           "%d\n",
           number_of_elements, elements_module);
    printf("Для гномьей сортировки составило %f секунд\n\n", summary_time / 10);
  }
}

// 1 = patience sort, 2 = smooth sort, 3 = gnome sort
void test_sorted_subarrays(int number_of_sorting_algorithm, int subarray_module,
                           int num_of_elements) {
  double summary_time;
  int number_of_elements = num_of_elements;
  int elements_module = power_of_10(9);
  for (int test_count = 0; test_count < 10; test_count++) {
    srand(time(NULL));
    int *array;
    array = malloc(sizeof(int) * number_of_elements);
    for (int i = 0; i < number_of_elements; i++) {
      array[i] = rand() % (elements_module + 1);
    }

    for (int i = 0; i < num_of_elements / subarray_module; i++) {
      int to_last = ((i * subarray_module) + subarray_module),
          to_first = (i * subarray_module);
      smooth_sort(array + to_first, array + to_last);
    }

    time_t start, end;
    start = clock();
    if (number_of_sorting_algorithm == 1) {
      patience_sort(array, array + (int)(number_of_elements - 1));
    } else if (number_of_sorting_algorithm == 2) {
      smooth_sort(array, array + (int)(number_of_elements - 1));
    } else if (number_of_sorting_algorithm == 3) {
      gnome_sort(array, array + (int)(number_of_elements - 1));
    }
    end = clock();
    summary_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    free(array);
  }
  if (number_of_sorting_algorithm == 1) {
    printf("\n\nСреднее время сортировки отсортированных подмассивов по модулю "
           "%d\n",
           subarray_module);
    printf("Для терпеливой сортировки составило %f секунд\n\n",
           summary_time / 10);
  } else if (number_of_sorting_algorithm == 2) {
    printf("\n\nСреднее время сортировки отсортированных подмассивов по модулю "
           "%d\n",
           subarray_module);
    printf("Для плавной сортировки составило %f секунд\n\n", summary_time / 10);
  } else if (number_of_sorting_algorithm == 3) {
    printf("\n\nСреднее время сортировки отсортированных подмассивов по модулю "
           "%d\n",
           subarray_module);
    printf("Для гномьей сортировки составило %f секунд\n\n", summary_time / 10);
  }
}

// 1 = patience sort, 2 = smooth sort, 3 = gnome sort
void test_presorted_swaps(int number_of_sorting_algorithm, int number_of_swaps,
                          int num_of_elements) {
  double summary_time;
  int elements_module = power_of_10(9);
  int *array;
  array = malloc(num_of_elements * sizeof(int));

  for (int test_count = 0; test_count < 10; test_count++) {
    srand(time(NULL));
    for (int i = 0; i < num_of_elements; i++) {
      array[i] = rand() % (elements_module + 1);
    }
    qsort(array, num_of_elements, sizeof(int), comp); // presort
    for (int swap_count = 0; swap_count < number_of_swaps; swap_count++) {
      // Generate two different random indices
      int index1 = rand() % num_of_elements;
      int index2 = rand() % num_of_elements;

      // Ensure we're swapping different elements
      while (index1 == index2) {
        index2 = rand() % num_of_elements;
      }

      // Perform the swap
      int temp = array[index1];
      array[index1] = array[index2];
      array[index2] = temp;
    }
    time_t start, end;
    start = clock();
    if (number_of_sorting_algorithm == 1) {
      patience_sort(array, array + (int)(num_of_elements - 1));
    } else if (number_of_sorting_algorithm == 2) {
      smooth_sort(array, array + (int)(num_of_elements - 1));
    } else if (number_of_sorting_algorithm == 3) {
      gnome_sort(array, array + (int)(num_of_elements - 1));
    }
    end = clock();
    summary_time += ((double)(end - start)) / CLOCKS_PER_SEC;
  }
  free(array);

  if (number_of_sorting_algorithm == 1) {
    printf("\n\nСреднее время сортировки массива с %d свопов\n",
           number_of_swaps);
    printf("Для терпеливой сортировки составило %f секунд\n\n",
           summary_time / 10);
  } else if (number_of_sorting_algorithm == 2) {
    printf("\n\nСреднее время сортировки массива с %d свопов\n",
           number_of_swaps);
    printf("Для плавной сортировки составило %f секунд\n\n", summary_time / 10);
  } else if (number_of_sorting_algorithm == 3) {
    printf("\n\nСреднее время сортировки массива с %d свопов\n",
           number_of_swaps);
    printf("Для гномьей сортировки составило %f секунд\n\n", summary_time / 10);
  }
}

// 1 = patience sort, 2 = smooth sort, 3 = gnome sort
void test_same_elements(int number_of_sorting_algorithm,
                        int percent_of_same_elements, int num_of_elements) {
  double summary_time;
  int number_of_elements = num_of_elements;
  int elements_module = power_of_10(9);
  for (int test_count = 0; test_count < 10; test_count++) {
    srand(time(NULL));
    int *array;
    array = malloc(sizeof(int) * number_of_elements);
    for (int i = 0; i < number_of_elements; i++) {
      array[i] = i;
    }

    // Выбираем случайный элемент для замены
    const int element = rand() % elements_module;

    // Вычисляем количество замен (минимум 1, если percent > 0)
    int num_replacements =
        (num_of_elements * percent_of_same_elements + 99) / 100;
    if (num_replacements > num_of_elements) {
      num_replacements = num_of_elements;
    }

    // Заменяем случайные элементы на `element`
    for (int i = 0; i < num_replacements; i++) {
      int index;
      do {
        index = rand() % num_of_elements;
      } while (array[index] == element); // Избегаем лишних замен
      array[index] = element;
    }

    time_t start, end;
    start = clock();
    if (number_of_sorting_algorithm == 1) {
      patience_sort(array, array + (int)(number_of_elements - 1));
    } else if (number_of_sorting_algorithm == 2) {
      smooth_sort(array, array + (int)(number_of_elements - 1));
    } else if (number_of_sorting_algorithm == 3) {
      gnome_sort(array, array + (int)(number_of_elements - 1));
    }
    end = clock();
    summary_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    free(array);
  }
  if (number_of_sorting_algorithm == 1) {
    printf("\n\nСреднее время сортировки массива с %d%% одинаковых элеметов\n",
           percent_of_same_elements);
    printf("Для терпеливой сортировки составило %f секунд\n\n",
           summary_time / 10);
  } else if (number_of_sorting_algorithm == 2) {
    printf("\n\nСреднее время сортировки массива с %d%% одинаковых элеметов\n",
           percent_of_same_elements);
    printf("Для плавной сортировки составило %f секунд\n\n", summary_time / 10);
  } else if (number_of_sorting_algorithm == 3) {
    printf("\n\nСреднее время сортировки массива с %d%% одинаковых элеметов\n",
           percent_of_same_elements);
    printf("Для гномьей сортировки составило %f секунд\n\n", summary_time / 10);
  }
}

// 1 = patience sort, 2 = smooth sort, 3 = gnome sort
void test_backward_sorted(int number_of_sorting_algorithm,
                          int num_of_elements) {
  double summary_time;
  int number_of_elements = num_of_elements;
  int elements_module = power_of_10(9);
  for (int test_count = 0; test_count < 10; test_count++) {
    srand(time(NULL));
    int *array;
    array = malloc(sizeof(int) * number_of_elements);
    for (int i = 0; i < number_of_elements; i++) {
      array[i] = rand() % (elements_module + 1);
    }
    qsort(array, num_of_elements, sizeof(int), comp_backward); // presort

    time_t start, end;
    start = clock();
    if (number_of_sorting_algorithm == 1) {
      patience_sort(array, array + (int)(number_of_elements - 1));
    } else if (number_of_sorting_algorithm == 2) {
      smooth_sort(array, array + (int)(number_of_elements - 1));
    } else if (number_of_sorting_algorithm == 3) {
      gnome_sort(array, array + (int)(number_of_elements - 1));
    }
    end = clock();
    summary_time += ((double)(end - start)) / CLOCKS_PER_SEC;
    free(array);
  }
  if (number_of_sorting_algorithm == 1) {
    printf("\n\nСреднее время сортировки отсортированного в обратном порядке "
           "массива\n");
    printf("Для терпеливой сортировки составило %f секунд\n\n",
           summary_time / 10);
  } else if (number_of_sorting_algorithm == 2) {
    printf("\n\nСреднее время сортировки отсортированного в обратном порядке "
           "массива\n");
    printf("Для плавной сортировки составило %f секунд\n\n", summary_time / 10);
  } else if (number_of_sorting_algorithm == 3) {
    printf("\n\nСреднее время сортировки отсортированного в обратном порядке "
           "массива\n");
    printf("Для гномьей сортировки составило %f секунд\n\n", summary_time / 10);
  }
}
