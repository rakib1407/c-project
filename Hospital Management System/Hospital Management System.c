#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100  // Maximum number of patients

// Patient structure
struct Patient {
    int id;
    char name[100];
    int age;
    char gender[10];
    char disease[100];
    float bill;
};

// Global array to store patients
struct Patient patients[MAX_PATIENTS];
int patientCount = 0;

// Function to add a new patient
void addPatient() {
    if (patientCount < MAX_PATIENTS) {
        struct Patient p;
        p.id = patientCount + 1;  // Automatically assign a unique ID

        printf("Enter Patient Name: ");
        getchar();  // To consume newline character left by previous input
        fgets(p.name, sizeof(p.name), stdin);
        p.name[strcspn(p.name, "\n")] = '\0';  // Remove newline character

        printf("Enter Age: ");
        scanf("%d", &p.age);

        printf("Enter Gender: ");
        getchar();  // To consume newline character left by previous input
        fgets(p.gender, sizeof(p.gender), stdin);
        p.gender[strcspn(p.gender, "\n")] = '\0';  // Remove newline character

        printf("Enter Disease: ");
        fgets(p.disease, sizeof(p.disease), stdin);
        p.disease[strcspn(p.disease, "\n")] = '\0';  // Remove newline character

        printf("Enter Bill Amount: ");
        scanf("%f", &p.bill);

        patients[patientCount++] = p;  // Store the patient in the array
        printf("Patient added successfully!\n");
    } else {
        printf("Sorry, the hospital is at full capacity.\n");
    }
}

// Function to view all patients
void viewPatients() {
    if (patientCount == 0) {
        printf("No patients found.\n");
    } else {
        printf("\nPatient List:\n");
        printf("ID | Name | Age | Gender | Disease | Bill\n");
        printf("----------------------------------------------\n");
        for (int i = 0; i < patientCount; i++) {
            printf("%d | %s | %d | %s | %s | %.2f\n", patients[i].id, patients[i].name, patients[i].age, patients[i].gender, patients[i].disease, patients[i].bill);
        }
    }
}

// Function to search for a patient by ID
void searchPatientByID(int id) {
    int found = 0;
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            printf("\nPatient Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nBill: %.2f\n", patients[i].id, patients[i].name, patients[i].age, patients[i].gender, patients[i].disease, patients[i].bill);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Patient with ID %d not found.\n", id);
    }
}

// Function to update patient information
void updatePatient(int id) {
    int found = 0;
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            printf("Updating information for patient: %s\n", patients[i].name);

            printf("Enter new Name: ");
            getchar();  // To consume newline character left by previous input
            fgets(patients[i].name, sizeof(patients[i].name), stdin);
            patients[i].name[strcspn(patients[i].name, "\n")] = '\0';  // Remove newline character

            printf("Enter new Age: ");
            scanf("%d", &patients[i].age);

            printf("Enter new Gender: ");
            getchar();  // To consume newline character left by previous input
            fgets(patients[i].gender, sizeof(patients[i].gender), stdin);
            patients[i].gender[strcspn(patients[i].gender, "\n")] = '\0';  // Remove newline character

            printf("Enter new Disease: ");
            fgets(patients[i].disease, sizeof(patients[i].disease), stdin);
            patients[i].disease[strcspn(patients[i].disease, "\n")] = '\0';  // Remove newline character

            printf("Enter new Bill Amount: ");
            scanf("%f", &patients[i].bill);

            printf("Patient information updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Patient with ID %d not found.\n", id);
    }
}

// Function to delete a patient by ID
void deletePatient(int id) {
    int found = 0;
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];  // Shift patients down
            }
            patientCount--;  // Decrease the count
            printf("Patient with ID %d deleted successfully!\n", id);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Patient with ID %d not found.\n", id);
    }
}

int main() {
    int choice, id;

    do {
        printf("\n--- Hospital Management System ---\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient by ID\n");
        printf("4. Update Patient Information\n");
        printf("5. Delete Patient\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                printf("Enter Patient ID to Search: ");
                scanf("%d", &id);
                searchPatientByID(id);
                break;
            case 4:
                printf("Enter Patient ID to Update: ");
                scanf("%d", &id);
                updatePatient(id);
                break;
            case 5:
                printf("Enter Patient ID to Delete: ");
                scanf("%d", &id);
                deletePatient(id);
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
