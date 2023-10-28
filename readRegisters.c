#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int age;
    int sal;
} Registro;

int main() {
    FILE *fp;
    int size = 4;
    Registro emp;
    char filename[] = "employeeRecords.dat";

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("\nCannot open the file\n");
        exit(1);
    }

    printf("Name\tAge\tSalary\n");
    printf("----\t---\t------\n");

    while (fread(&emp, sizeof(Registro), 1, fp) == 1) {
        printf("%s\t%d\t%d\n", emp.name, emp.age, emp.sal);
    }

    fclose(fp);

    return 0;
}
