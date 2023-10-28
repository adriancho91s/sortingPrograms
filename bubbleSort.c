#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int age;
    int sal;
} Registro;

/**
 * Compares two Registro structs by name in ascending order.
 * 
 * @param a Pointer to the first Registro struct to be compared.
 * @param b Pointer to the second Registro struct to be compared.
 * @return An integer less than, equal to, or greater than zero if the name of the first Registro struct is found, respectively, to be less than, to match, or be greater than the name of the second Registro struct.
 */
int compareByNameAscending(const void *a, const void *b) {
    return strcmp(((Registro*)a)->name, ((Registro*)b)->name);
}

/**
 * Compares two Registro structs by name in descending order.
 * 
 * @param a Pointer to the first Registro struct to be compared.
 * @param b Pointer to the second Registro struct to be compared.
 * @return An integer less than, equal to, or greater than zero if the name of the first Registro struct is found, respectively, to be greater than, to match, or be less than the name of the second Registro struct.
 */
int compareByNameDescending(const void *a, const void *b) {
    return -strcmp(((Registro*)a)->name, ((Registro*)b)->name);
}

/**
 * Compares two Registro structs by age in ascending order.
 * 
 * @param a Pointer to the first Registro struct to be compared.
 * @param b Pointer to the second Registro struct to be compared.
 * @return An integer less than, equal to, or greater than zero if the age of the first Registro struct is found, respectively, to be less than, to match, or be greater than the age of the second Registro struct.
 */
int compareByAgeAscending(const void *a, const void *b) {
    return ((Registro*)a)->age - ((Registro*)b)->age;
}

/**
 * Compares two Registro structs by age in descending order.
 * 
 * @param a Pointer to the first Registro struct to be compared.
 * @param b Pointer to the second Registro struct to be compared.
 * @return An integer less than, equal to, or greater than zero if the age of the first Registro struct is found, respectively, to be greater than, to match, or be less than the age of the second Registro struct.
 */
int compareByAgeDescending(const void *a, const void *b) {
    return ((Registro*)b)->age - ((Registro*)a)->age;
}

/**
 * Compares two Registro structs by salary in ascending order.
 * 
 * @param a Pointer to the first Registro struct to be compared.
 * @param b Pointer to the second Registro struct to be compared.
 * @return An integer less than, equal to, or greater than zero if the salary of the first Registro struct is found, respectively, to be less than, to match, or be greater than the salary of the second Registro struct.
 */
int compareBySalaryAscending(const void *a, const void *b) {
    return ((Registro*)a)->sal - ((Registro*)b)->sal;
}

/**
 * Compares two Registro structs by salary in descending order.
 * 
 * @param a Pointer to the first Registro struct to be compared.
 * @param b Pointer to the second Registro struct to be compared.
 * @return An integer less than, equal to, or greater than zero if the salary of the first Registro struct is found, respectively, to be greater than, to match, or be less than the salary of the second Registro struct.
 */
int compareBySalaryDescending(const void *a, const void *b) {
    return ((Registro*)b)->sal - ((Registro*)a)->sal;
}

int main() {
    FILE *fp;
    int size = 4;//size of the records
    Registro emp[2];
    int sorted = 0;

    fp = fopen("employeeRecords.dat", "r+b");

    if (fp == NULL) {
        printf("\nCannot open the file\n");
        exit(1);
    }

    int choice;
    int ascending;
    printf("Select field to order:\n");
    printf("1. Name\n");
    printf("2. Age\n");
    printf("3. Salary\n");
    scanf("%d", &choice);
    printf("Select order:\n");
    printf("1. Ascending\n");
    printf("2. Descending\n");
    scanf("%d", &ascending);

    int (*compareFunction)(const void *, const void *);

    switch (choice) {
        case 1:
            if (ascending == 2) {
                compareFunction = compareByNameAscending;
            } else {
                compareFunction = compareByNameDescending;
            }
            break;
        case 2:
            if (ascending == 2) {
                compareFunction = compareByAgeAscending;
            } else {
                compareFunction = compareByAgeDescending;
            }
            break;
        case 3:
            if (ascending == 2) {
                compareFunction = compareBySalaryAscending;
            } else {
                compareFunction = compareBySalaryDescending;
            }
            break;
        default:
            printf("Invalid choice\n");
            fclose(fp);
            exit(1);
    }

    while (!sorted) {
        sorted = 1; // Suponemos que el archivo está ordenado

        for (int i = 0; i < size - 1; i++) {
            fseek(fp, i * sizeof(Registro), SEEK_SET);
            fread(&emp[0], sizeof(Registro), 1, fp);

            fseek(fp, (i + 1) * sizeof(Registro), SEEK_SET);
            fread(&emp[1], sizeof(Registro), 1, fp);

            if (compareFunction(&emp[0], &emp[1]) > 0) {
                fseek(fp, i * sizeof(Registro), SEEK_SET);
                fwrite(&emp[1], sizeof(Registro), 1, fp);

                fseek(fp, (i + 1) * sizeof(Registro), SEEK_SET);
                fwrite(&emp[0], sizeof(Registro), 1, fp);
                sorted = 0;
            }
        }
    }

    fclose(fp);

    printf("\nEl archivo se ha ordenado con éxito en el archivo original (employeeRecords.dat).\n\n");

    return 0;
}
