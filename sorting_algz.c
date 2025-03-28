#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// Leonardo numbers cache (we'll compute up to needed values)
static int leonardo_numbers[46]; // Enough for arrays up to 2^64 elements

void gnome_sort(int* first_element, int* last_element);
void patience_sort(int *first_element, int *last_element);
void smooth_sort(int* first_element, int* last_element);

int main() {
    int arr[] = {2,5,1,0,7,6,3,9,8,4};

    smooth_sort(arr,(arr+(sizeof(arr)/sizeof(int))-1));

    for(int i=0; i<(sizeof(arr)/sizeof(int)); i++){
        printf("%d ", arr[i]);
    }
}

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

// Structure for a pile (stack)
typedef struct {
    int *cards;     // Array to store elements
    int top;        // Index of top element
    int capacity;   // Maximum capacity of the pile
} Pile;

// Function to create a new pile
Pile* createPile(int capacity) {
    Pile *pile = (Pile*)malloc(sizeof(Pile));
    pile->cards = (int*)malloc(capacity * sizeof(int));
    pile->top = -1;
    pile->capacity = capacity;
    return pile;
}

// Function to push an element onto a pile
void push(Pile *pile, int value) {
    if (pile->top == pile->capacity - 1) {
        // Resize if needed (though theoretically shouldn't happen in patience sort)
        pile->capacity *= 2;
        pile->cards = (int*)realloc(pile->cards, pile->capacity * sizeof(int));
    }
    pile->cards[++pile->top] = value;
}

// Function to peek at the top element of a pile
int peek(Pile *pile) {
    return pile->cards[pile->top];
}

// Function to pop the top element from a pile
int pop(Pile *pile) {
    return pile->cards[pile->top--];
}

// Binary search to find the leftmost pile whose top is >= value
int findPile(Pile **piles, int numPiles, int value) {
    int left = 0, right = numPiles - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (peek(piles[mid]) >= value) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// Function to merge piles using k-way merge (simplified for implementation)
void mergePiles(int *arr, Pile **piles, int numPiles, int size) {
    // Create a min-heap for efficient merging (simplified here for clarity)
    // In a more optimized version, we'd use a proper priority queue
    
    int index = 0;
    while (index < size) {
        // Find the pile with the smallest top element
        int minIndex = -1;
        int minValue = INT_MAX;
        
        for (int i = 0; i < numPiles; i++) {
            if (piles[i]->top != -1 && peek(piles[i]) < minValue) {
                minValue = peek(piles[i]);
                minIndex = i;
            }
        }
        
        if (minIndex == -1) break; // All piles are empty
        
        arr[index++] = pop(piles[minIndex]);
    }
}

// Patience sort implementation
void patience_sort(int *first_element, int *last_element) {
    if (first_element >= last_element) return; // Empty or single-element range
    
    int size = last_element - first_element + 1;
    Pile **piles = (Pile**)malloc(size * sizeof(Pile*)); // Worst case: each element in its own pile
    int numPiles = 0;
    
    // Phase 1: Create piles
    for (int i = 0; i < size; i++) {
        int value = first_element[i];
        int pileIndex = findPile(piles, numPiles, value);
        
        if (pileIndex == numPiles) {
            // Need a new pile
            piles[numPiles] = createPile(size);
            push(piles[numPiles++], value);
        } else {
            // Place on existing pile
            push(piles[pileIndex], value);
        }
    }
    
    // Phase 2: Merge piles
    mergePiles(first_element, piles, numPiles, size);
    
    // Clean up
    for (int i = 0; i < numPiles; i++) {
        free(piles[i]->cards);
        free(piles[i]);
    }
    free(piles);
}


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