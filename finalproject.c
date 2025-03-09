#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[50];
    int estimated_time;
    char problem[100];
} Patient;

// Function to swap two elements
void swap(Patient *a, Patient *b)
{
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function
int partition(Patient arr[], int low, int high)
{
    int pivot = arr[high].estimated_time;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j].estimated_time < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quicksort function
void quicksort(Patient arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Print the patient list
void printPatients(Patient arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s: %d minutes, Problem: %s\n", arr[i].name, arr[i].estimated_time, arr[i].problem);
    }
}

// Read patients from a file
int readPatientsFromFile(const char *filename, Patient patients[], int max_size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%[^,],%d,%[^\n]\n", patients[count].name, &patients[count].estimated_time, patients[count].problem) != EOF)
    {
        count++;
        if (count >= max_size)
        {
            break;
        }
    }

    fclose(file);
    return count;
}

// Write sorted patients to a file
void writePatientsToFile(const char *filename, Patient patients[], int size)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%s,%d,%s\n", patients[i].name, patients[i].estimated_time, patients[i].problem);
    }

    fclose(file);
}

// Add new patient to the list
void addPatient(Patient patients[], int *size)
{
    printf("Enter patient name: ");
    scanf("%s", patients[*size].name);
    printf("Enter estimated time (in minutes): ");
    scanf("%d", &patients[*size].estimated_time);

    printf("Enter the type of problem: ");
    scanf(" %[^\n]", patients[*size].problem);

    (*size)++;
}

// Delete patient from the list
void deletePatient(Patient patients[], int *size)
{
    if (*size == 0)
    {
        printf("No patients to delete.\n");
        return;
    }

    char name[50];
    printf("Enter the name of the patient to delete: ");
    scanf("%s", name);

    int found = 0;
    for (int i = 0; i < *size; i++)
    {
        if (strcmp(patients[i].name, name) == 0)
        {
            for (int j = i; j < *size - 1; j++)
            {
                patients[j] = patients[j + 1];
            }
            (*size)--;
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Patient not found.\n");
    }
    else
    {
        printf("Patient %s deleted.\n", name);
    }
}

int main()
{
    const char *input_filename = "patients.txt";
    const char *output_filename = "sorted_patients.txt";
    Patient patients[100];

    int n = readPatientsFromFile(input_filename, patients, 100);

    int choice;
    do
    {
        printf("Menu:\n");
        printf("1. Add patient\n");
        printf("2. Delete patient\n");
        printf("3. Display sorted patient list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addPatient(patients, &n);
            break;
        case 2:
            deletePatient(patients, &n);
            break;
        case 3:
            quicksort(patients, 0, n - 1);
            printf("Sorted patients based on estimated time:\n");
            printPatients(patients, n);
            writePatientsToFile(output_filename, patients, n);
            break;
        case 4:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
