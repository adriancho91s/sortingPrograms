#include <stdio.h>
#include <stdlib.h>

// Define the employee struct
struct employee
{
    char name[20];
    int age;
    int sal;
};

int main()
{
    FILE *file;
    struct employee emp;
    char filename[] = "employeeRecords.dat";

    // Open the file for writing
    file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    int numEmployees;

    // Prompt the user for the number of employees
    printf("Enter the number of employees: ");
    scanf("%d", &numEmployees);

    for (int i = 0; i < numEmployees; i++)
    {
        // Input employee details
        printf("Employee %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", emp.name);
        printf("Age: ");
        scanf("%d", &emp.age);
        printf("Salary: ");
        scanf("%d", &emp.sal);

        // Write the employee struct to the file
        fwrite(&emp, sizeof(struct employee), 1, file);
    }

    // Close the file
    fclose(file);

    printf("Employee records written to %s\n", filename);

    return 0;
}
