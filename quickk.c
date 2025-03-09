#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function: Places pivot at correct position
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choosing last element as pivot
    int i = low - 1; // Index for smaller elements

    for (int j = low; j < high; j++) { // Traverse array from low to high-1
        if (arr[j] < pivot) { // If current element is smaller than pivot
            i++; // Move index forward
            swap(&arr[i], &arr[j]); // Swap smaller element with current element
        }
    }
    swap(&arr[i + 1], &arr[high]); // Swap pivot with element at correct position
    return i + 1; // Return the partition index
}

// QuickSort function: Recursively sorts partitions
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Get partition index

        quickSort(arr, low, pi - 1); // Sort left half
        quickSort(arr, pi + 1, high); // Sort right half
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function
int main() {
    int arr[] = {10, 3, 8, 15, 6, 12, 2, 18, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}