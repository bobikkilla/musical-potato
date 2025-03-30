#include "algo_lab.h"

void gnome_sort(int* first_element, int* last_element);
void patience_sort(int *first_element, int *last_element);
void smooth_sort(int* first_element, int* last_element);

// working correctly
void gnome_sort(int* first_element, int* last_element) {
	int *array = first_element;
	while (array <= last_element) {
		if (array == first_element || *(array - 1) <= *array) {
            array++;
        }
		else {
            int temp = *array;
            *array = *(array-1);
            *(array-1) = temp;
            array--;
        }
	}
}

////////////////////////////////////////////////////////////////////////////

// Min-heap implementation for tracking the top cards of piles
typedef struct {
    int value;  // Current top card of the pile
    int pile;   // Index of the pile
} HeapNode;

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(HeapNode* heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].value < heap[smallest].value)
        smallest = left;
    if (right < size && heap[right].value < heap[smallest].value)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        min_heapify(heap, size, smallest);
    }
}

void build_min_heap(HeapNode* heap, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        min_heapify(heap, size, i);
}

void patience_sort(int* first_element, int* last_element) 
{
    if (first_element >= last_element) return;

    int size = last_element - first_element;
    if (size <= 1) return;

    // Phase 1: Pile Formation (O(n log n))
    int** piles = (int**)malloc(size * sizeof(int*));
    int* pile_sizes = (int*)calloc(size, sizeof(int));
    int num_piles = 0;

    for (int i = 0; i < size; i++) {
        int x = first_element[i];
        int left = 0, right = num_piles;

        // Binary search to find the correct pile (O(log n) per element)
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (piles[mid][pile_sizes[mid] - 1] < x)
                left = mid + 1;
            else
                right = mid;
        }

        if (left == num_piles) {
            // Create a new pile
            piles[num_piles] = (int*)malloc(size * sizeof(int));
            num_piles++;
        }

        piles[left][pile_sizes[left]++] = x;
    }

    // Phase 2: Merge Piles using a Min-Heap (O(n log n))
    HeapNode* heap = (HeapNode*)malloc(num_piles * sizeof(HeapNode));
    for (int i = 0; i < num_piles; i++) {
        heap[i].value = piles[i][pile_sizes[i] - 1];
        heap[i].pile = i;
    }

    build_min_heap(heap, num_piles);  // O(n) heap construction

    for (int i = 0; i < size; i++) {
        // Extract the smallest element (O(log n))
        first_element[i] = heap[0].value;
        int pile = heap[0].pile;

        pile_sizes[pile]--;
        if (pile_sizes[pile] > 0) {
            // Replace with the new top of the pile
            heap[0].value = piles[pile][pile_sizes[pile] - 1];
        } else {
            // Remove the empty pile from the heap
            heap[0] = heap[num_piles - 1];
            num_piles--;
        }

        min_heapify(heap, num_piles, 0);  // Restore heap property
    }

    // Free memory
    for (int i = 0; i < num_piles; i++)
        free(piles[i]);
    free(piles);
    free(pile_sizes);
    free(heap);
}

////////////////////////////////////////////////////////////////////////////

// Leonardo numbers cache (we'll compute up to needed values)
static int leonardo_numbers[46]; // Enough for arrays up to 2^64 elements

// Compute Leonardo numbers up to needed size
void compute_leonardo_numbers() {
    leonardo_numbers[0] = 1;
    leonardo_numbers[1] = 1;
    for (int i = 2; i < 46; i++) {
        leonardo_numbers[i] = leonardo_numbers[i-1] + leonardo_numbers[i-2] + 1;
    }
}

// Heap operations for smooth sort
void heapify(int* arr, int root, int size) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;

    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != root) {
        int temp = arr[root];
        arr[root] = arr[largest];
        arr[largest] = temp;
        heapify(arr, largest, size);
    }
}

// Build the heap structure
void build_heap(int* arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, i, size);
}

// Smooth sort implementation
void smooth_sort(int* first_element, int* last_element) {
    if (first_element >= last_element) return;
    
    int size = last_element - first_element + 1;
    compute_leonardo_numbers();
    
    // Build the heap
    build_heap(first_element, size);
    
    // Extract elements from heap
    for (int i = size - 1; i > 0; i--) {
        // Move current root to end
        int temp = first_element[0];
        first_element[0] = first_element[i];
        first_element[i] = temp;
        
        // Heapify the reduced heap
        heapify(first_element, 0, i);
    }
}