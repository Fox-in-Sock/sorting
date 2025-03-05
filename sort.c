#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void swap(int *a, int *b, int arr[], int n)
{
    int temp = *a;
    *a = *b;
    *b = temp;

    // Print array state after each swap
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    fflush(stdout); // Ensure output is immediately printed
}

// Modified Quick Sort
int partition(int arr[], int low, int high, int n)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j], arr, n);
        }
    }
    swap(&arr[i + 1], &arr[high], arr, n);
    return i + 1;
}

void quickSort(int arr[], int low, int high, int n)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, n);
        quickSort(arr, low, pi - 1, n);
        quickSort(arr, pi + 1, high, n);
    }
}

// Modified Merge Sort
void merge(int arr[], int left, int mid, int right, int n)
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
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
        }
        // Print array state after each merge step
        for (int l = 0; l < n; l++)
        {
            printf("%d ", arr[l]);
        }
        printf("\n");
        fflush(stdout); // Ensure output is immediately printed
    }
    while (i < n1)
    {
        arr[k++] = L[i++];
        for (int l = 0; l < n; l++)
        {
            printf("%d ", arr[l]);
        }
        printf("\n");
        fflush(stdout);
    }
    while (j < n2)
    {
        arr[k++] = R[j++];
        for (int l = 0; l < n; l++)
        {
            printf("%d ", arr[l]);
        }
        printf("\n");
        fflush(stdout);
    }
}

void mergeSort(int arr[], int left, int right, int n)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, n);
        mergeSort(arr, mid + 1, right, n);
        merge(arr, left, mid, right, n);
    }
}

// Modified Heap Sort
void heapify(int arr[], int n, int i)
{
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i)
    {
        swap(&arr[i], &arr[largest], arr, n);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i], arr, n);
        heapify(arr, i, 0);
    }
}

void heapSortWrapper(int arr[], int left, int right, int n)
{
    heapSort(arr, n);
}

double measure_time(void (*sortFunc)(int[], int, int, int), int arr[], int size)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    sortFunc(arr, 0, size - 1, size);
    gettimeofday(&end, NULL);
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}

void write_array_to_file(const char *filename, int arr[], int n)
{
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < n; i++)
        fprintf(file, "%d ", arr[i]);
    fprintf(file, "\n");
    fclose(file);
}

int main()
{
    int arr[] = {10, 3, 8, 15, 6, 12, 2, 18, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    int arr_qs[n], arr_ms[n], arr_hs[n];
    memcpy(arr_qs, arr, sizeof(arr));
    memcpy(arr_ms, arr, sizeof(arr));
    memcpy(arr_hs, arr, sizeof(arr));

    double time_qs = measure_time(quickSort, arr_qs, n);
    double time_ms = measure_time(mergeSort, arr_ms, n);

    double time_hs = measure_time(heapSortWrapper, arr_hs, n);

    write_array_to_file("sorted_qs.txt", arr_qs, n);
    write_array_to_file("sorted_ms.txt", arr_ms, n);
    write_array_to_file("sorted_hs.txt", arr_hs, n);

    FILE *timing_file = fopen("timing_output.txt", "w");
    if (timing_file == NULL)
    {
        fprintf(stderr, "Error opening timing_output.txt for writing.\n");
        return EXIT_FAILURE; // Exit with an error code
    }

    fprintf(timing_file, "Quick Sort: %.5f seconds\n", time_qs);
    fprintf(timing_file, "Merge Sort: %.5f seconds\n", time_ms);
    fprintf(timing_file, "Heap Sort: %.5f seconds\n", time_hs);

    if (fclose(timing_file) != 0)
    {
        fprintf(stderr, "Error closing timing_output.txt.\n");
        return EXIT_FAILURE; // Exit with an error code
    }

    return 0;
}
