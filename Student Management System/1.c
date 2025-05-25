#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    int age;
    float marks;
};

void addStudent(FILE *fp) {
    struct Student s;
    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    getchar();
    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';  // Remove newline
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fseek(fp, 0, SEEK_END);
    fwrite(&s, sizeof(struct Student), 1, fp);
    printf("Student added successfully!\n");
}

void viewStudents(FILE *fp) {
    struct Student s;
    rewind(fp);
    printf("\nAll Students:\n");
    printf("-------------------------------------------\n");
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("Roll: %d | Name: %s | Age: %d | Marks: %.2f\n", s.roll, s.name, s.age, s.marks);
    }
    printf("-------------------------------------------\n");
}

void searchStudent(FILE *fp, int roll) {
    struct Student s;
    rewind(fp);
    int found = 0;
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll == roll) {
            printf("\nStudent Found:\n");
            printf("Roll: %d | Name: %s | Age: %d | Marks: %.2f\n", s.roll, s.name, s.age, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with Roll Number %d not found.\n", roll);
    }
}

void updateStudent(FILE *fp, int roll) {
    struct Student s;
    rewind(fp);
    int found = 0;
    long pos;
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            pos = ftell(fp) - sizeof(struct Student);

            printf("Enter New Name: ");
            getchar();
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';
            printf("Enter New Age: ");
            scanf("%d", &s.age);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, pos, SEEK_SET);
            fwrite(&s, sizeof(struct Student), 1, fp);
            printf("Student information updated successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Student with Roll Number %d not found.\n", roll);
    }
}

void deleteStudent(FILE *fp, int roll) {
    struct Student s;
    FILE *temp = fopen("temp.dat", "wb");
    rewind(fp);
    int found = 0;

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll != roll) {
            fwrite(&s, sizeof(struct Student), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("Student deleted successfully!\n");
    } else {
        printf("Student with Roll Number %d not found.\n", roll);
    }
}

int main() {
    FILE *fp;
    int choice, roll;

    fp = fopen("students.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("students.dat", "wb+");
        if (fp == NULL) {
            printf("Unable to open file.\n");
            return 1;
        }
    }

    do {
        system("cls");  //clear the console screen
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        system("cls");  //clear the console screen
        switch (choice) {
            case 1:
                addStudent(fp);
                break;
            case 2:
                viewStudents(fp);
                break;
            case 3:
                printf("Enter Roll Number to Search: ");
                scanf("%d", &roll);
                searchStudent(fp, roll);
                break;
            case 4:
                printf("Enter Roll Number to Update: ");
                scanf("%d", &roll);
                updateStudent(fp, roll);
                break;
            case 5:
                printf("Enter Roll Number to Delete: ");
                scanf("%d", &roll);
                deleteStudent(fp, roll);
                fp = fopen("students.dat", "rb+");
                break;
            case 6:
                fclose(fp);
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
            
    
        }

        printf("\n");

        system("pause"); //Pause the window until user press any key

        system("cls");  //clear the console screen
    } while (choice != 6);

    return 0;
}
