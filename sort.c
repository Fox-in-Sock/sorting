#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // For gettimeofday()

// Function to swap two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Quick Sort
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Heap Sort
void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Function to measure time using gettimeofday()
double measure_time(void (*sortFunc)(int[], int, int), int arr[], int size)
{
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL); // Start time
    sortFunc(arr, 0, size - 1);      // Call the sorting function
    gettimeofday(&end_time, NULL);   // End time

    // Calculate the time difference in seconds
    double time_taken = (end_time.tv_sec - start_time.tv_sec) * 1.0;
    time_taken += (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    return time_taken; // Return time in seconds
}

int main()
{
    int arr[] = {10, 3, 8, 15, 6, 12, 2, 18, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Measure and display time for Quick Sort
    int arr_qs[] = {10, 3, 8, 15, 6, 12, 2, 18, 7};
    double time_qs = measure_time(quickSort, arr_qs, n);
    FILE *timing_file = fopen("timing_output.txt", "w");
    fprintf(timing_file, "Quick Sort: %.5f seconds\n", time_qs);

    // Measure and display time for Merge Sort
    int arr_ms[] = {10, 3, 8, 15, 6, 12, 2, 18, 7};
    double time_ms = measure_time(mergeSort, arr_ms, n);
    fprintf(timing_file, "Merge Sort: %.5f seconds\n", time_ms);

    // Measure and display time for Heap Sort
    int arr_hs[] = {10, 3, 8, 15, 6, 12, 2, 18, 7};
    double time_hs = measure_time(heapSort, arr_hs, n);
    fprintf(timing_file, "Heap Sort: %.5f seconds\n", time_hs);

    fclose(timing_file);

    return 0;
}
