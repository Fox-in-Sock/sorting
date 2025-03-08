#include <stdio.h>
#include <stdlib.h>

//swapping is donee in these algorithms
void swap(int *a, int *b, int arr[], int n)
{
    int temp = *a;
    *a = *b;
    *b = temp;//pointrs for original array

    // Print array state after each swap
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    fflush(stdout); // Ensure output is immediately printed
}

// pivot for dividing array to 2 parets
int partition(int arr[], int low, int high, int n)
{
    int pivot = arr[high];//chooses last
    int i = low - 1;//small nos goes to left of pivot no and larger to right
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)//for arr j is small move to left by swap
        {
            i++;
            swap(&arr[i], &arr[j], arr, n);
        }
    }
    swap(&arr[i + 1], &arr[high], arr, n);//pivot places in position
    return i + 1;//return indx
}

void quickSort(int arr[], int low, int high, int n)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, n);
        quickSort(arr, low, pi - 1, n);//sprt left
        quickSort(arr, pi + 1, high, n);//sort right
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
    int arr[] = {10, 3, 8, 15, 6, 12, 2, 18, 7, 34, 45, 65, 76, 86, 23, 13, 33, 11, 1, 2, 4, 81};
    int n = sizeof(arr) / sizeof(arr[0]);
    int arr_qs[n], arr_ms[n], arr_hs[n];
    for (int i = 0; i < n; i++)
    {
        arr_qs[i] = arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        arr_ms[i] = arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        arr_hs[i] = arr[i];
    }

    quickSort(arr_qs, 0, n - 1, n);
    mergeSort(arr_ms, 0, n - 1, n);
    heapSortWrapper(arr_hs, 0, n - 1, n);

    write_array_to_file("quic.txt", arr_qs, n);
    write_array_to_file("merg.txt", arr_ms, n);
    write_array_to_file("hea.txt", arr_hs, n);

    return 0;
}
