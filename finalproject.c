#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_NAME_LENGTH 50
#define MAX_PROBLEM_LENGTH 100

typedef struct
{
    char name[MAX_NAME_LENGTH];
    int estimated_time;
    char problem[MAX_PROBLEM_LENGTH];
} Patient;

// Function to swap two elements
void swap(Patient *a, Patient *b)
{
    Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for quicksort to sort by estimated time
int partition(Patient arr[], int low, int high)
{
    Patient pivot = arr[high];
    int i = low - 1;

    // Compare estimated_time instead of name
    for (int j = low; j < high; j++)
    {
        if (arr[j].estimated_time < pivot.estimated_time) // Compare times instead of names
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Quicksort function to sort patients by estimated time
void quicksort(Patient arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Binary search function to find a patient by name
int binarySearch(Patient arr[], int size, const char *name)
{
    int low = 0;
    int high = size - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        int cmp = strcmp(arr[mid].name, name);
        if (cmp == 0)
        {
            return mid; // Found the patient
        }
        else if (cmp < 0)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1; // Patient not found
}

// Write patients to file
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
    if (*size >= MAX_PATIENTS)
    {
        printf("Maximum number of patients reached.\n");
        return;
    }

    // Clear the input buffer
    while (getchar() != '\n')
        ;

    // Read patient name using fgets for spaces
    printf("Enter patient name: ");
    fgets(patients[*size].name, MAX_NAME_LENGTH, stdin);
    // Remove the newline character if present
    patients[*size].name[strcspn(patients[*size].name, "\n")] = 0;

    // Read estimated time
    printf("Enter estimated time (in minutes): ");
    while (scanf("%d", &patients[*size].estimated_time) != 1)
    {
        printf("Invalid input. Please enter a numerical value for estimated time: ");
        while (getchar() != '\n')
            ; // Clear input buffer
    }
    while (getchar() != '\n')
        ; // Clear input buffer

    // Read the problem description using fgets
    printf("Enter the type of problem: ");
    fgets(patients[*size].problem, MAX_PROBLEM_LENGTH, stdin);
    patients[*size].problem[strcspn(patients[*size].problem, "\n")] = 0; // Remove newline

    (*size)++;
    quicksort(patients, 0, *size - 1);                    // Sort after adding each patient
    writePatientsToFile("patients.txt", patients, *size); // Update patients.txt
}

// Delete patient from the list
void deletePatient(Patient patients[], int *size)
{
    if (*size == 0)
    {
        printf("No patients to delete.\n");
        return;
    }

    char name[MAX_NAME_LENGTH];
    printf("Enter the name of the patient to delete: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline

    int found = binarySearch(patients, *size, name);
    if (found != -1)
    {
        for (int i = found; i < *size - 1; i++)
        {
            patients[i] = patients[i + 1];
        }
        (*size)--;
        writePatientsToFile("patients.txt", patients, *size); // Update patients.txt
        printf("Patient %s deleted.\n", name);
    }
    else
    {
        printf("Patient not found.\n");
    }
}

int main()
{
    Patient patients[MAX_PATIENTS];
    int size = 0;

    // Read initial patients from file
    FILE *file = fopen("patients.txt", "r");
    if (file != NULL)
    {
        while (size < MAX_PATIENTS && fscanf(file, " %49[^,],%d, %99[^\n]", patients[size].name, &patients[size].estimated_time, patients[size].problem) == 3)
        {
            printf("Read patient: %s, %d minutes, Problem: %s\n", patients[size].name, patients[size].estimated_time, patients[size].problem);
            size++;
        }
        fclose(file);
        quicksort(patients, 0, size - 1); // Sort initial patients by estimated time
    }

    int choice;
    do
    {
        printf("Menu:\n");
        printf("1. Add patient\n");
        printf("2. Delete patient\n");
        printf("3. Display patient list\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n')
            ; // Clear input buffer

        switch (choice)
        {
        case 1:
            addPatient(patients, &size);
            break;
        case 2:
            deletePatient(patients, &size);
            break;
        case 3:
            printf("Patient list:\n");
            for (int i = 0; i < size; i++)
            {
                printf("%s: %d minutes, Problem: %s\n", patients[i].name, patients[i].estimated_time, patients[i].problem);
            }
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
