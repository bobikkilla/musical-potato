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
    int* elements;
    int size;
    int capacity;
} Pile;

typedef struct {
    int value;
    int pile;
} HeapNode;

#define INITIAL_CAPACITY 4

static void min_heapify(HeapNode* heap, int heap_size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap_size && heap[left].value < heap[smallest].value)
        smallest = left;
    if (right < heap_size && heap[right].value < heap[smallest].value)
        smallest = right;

    if (smallest != i) {
        HeapNode temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        min_heapify(heap, heap_size, smallest);
    }
}

static void build_min_heap(HeapNode* heap, int heap_size) {
    for (int i = (heap_size / 2) - 1; i >= 0; i--)
        min_heapify(heap, heap_size, i);
}

void patience_sort(int* first_element, int* last_element) {
    if (first_element >= last_element) return;
    int size = last_element - first_element;
    if (size <= 1) return;

    // Phase 1: Dynamic pile formation
    Pile* piles = (Pile*)malloc(size * sizeof(Pile));
    int num_piles = 0;

    for (int i = 0; i < size; i++) {
        int x = first_element[i];
        int left = 0, right = num_piles;

        // Binary search for insertion point
        while (left < right) {
            int mid = left + (right - left) / 2;
            int top = piles[mid].elements[piles[mid].size - 1];
            if (top < x) left = mid + 1;
            else right = mid;
        }

        if (left == num_piles) { // New pile needed
            piles[num_piles].elements = (int*)malloc(INITIAL_CAPACITY * sizeof(int));
            piles[num_piles].size = 0;
            piles[num_piles].capacity = INITIAL_CAPACITY;
            num_piles++;
        }

        Pile* p = &piles[left];
        if (p->size >= p->capacity) { // Resize if full
            p->capacity *= 2;
            p->elements = realloc(p->elements, p->capacity * sizeof(int));
        }
        p->elements[p->size++] = x;
    }

    // Phase 2: Merge using min-heap
    HeapNode* heap = (HeapNode*)malloc(num_piles * sizeof(HeapNode));
    for (int i = 0; i < num_piles; i++) {
        heap[i].value = piles[i].elements[piles[i].size - 1];
        heap[i].pile = i;
    }
    build_min_heap(heap, num_piles);

    int heap_size = num_piles;
    for (int i = 0; i < size; i++) {
        first_element[i] = heap[0].value;
        int pile_idx = heap[0].pile;
        Pile* p = &piles[pile_idx];

        if (--p->size > 0) { // Update heap with next element
            heap[0].value = p->elements[p->size - 1];
        } else { // Remove empty pile from heap
            heap[0] = heap[--heap_size];
        }
        min_heapify(heap, heap_size, 0);
    }

    // Cleanup
    free(heap);
    for (int i = 0; i < num_piles; i++)
        free(piles[i].elements);
    free(piles);
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