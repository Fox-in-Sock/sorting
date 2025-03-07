#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Function to write sorted arrays to files
void write_array_to_file(const char *filename, int arr[], int n) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < n; i++)
        fprintf(file, "%d ", arr[i]);
    fprintf(file, "\n");
    fclose(file);
}

int main() {
    int arr[] = {10, 3, 8, 15, 6, 12, 2, 18, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int arr_qs[n], arr_ms[n], arr_hs[n];

    memcpy(arr_qs, arr, sizeof(arr));
    memcpy(arr_ms, arr, sizeof(arr));
    memcpy(arr_hs, arr, sizeof(arr));

    quickSort(arr_qs, 0, n - 1);
    mergeSort(arr_ms, 0, n - 1);
    heapSort(arr_hs, n);

    write_array_to_file("quic.txt", arr_qs, n);
    write_array_to_file("merg.txt", arr_ms, n);
    write_array_to_file("hea.txt", arr_hs, n);

    return 0;
}
