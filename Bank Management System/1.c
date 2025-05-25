#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accountNumber;
    char accountHolderName[50];
    float balance;
};

void createAccount(FILE *fp) {
    struct Account acc;
    printf("Enter Account Number: ");
    scanf("%d", &acc.accountNumber);
    getchar();
    printf("Enter Account Holder Name: ");
    fgets(acc.accountHolderName, sizeof(acc.accountHolderName), stdin);
    acc.accountHolderName[strcspn(acc.accountHolderName, "\n")] = '\0';  // Remove newline
    acc.balance = 0.0;  // Initial balance is 0

    fseek(fp, 0, SEEK_END);
    fwrite(&acc, sizeof(struct Account), 1, fp);
    printf("Account created successfully!\n");
}

void viewAccount(FILE *fp, int accountNumber) {
    struct Account acc;
    rewind(fp);
    int found = 0;

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accountNumber == accountNumber) {
            printf("\nAccount Details:\n");
            printf("Account Number: %d\n", acc.accountNumber);
            printf("Account Holder Name: %s\n", acc.accountHolderName);
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account with Account Number %d not found.\n", accountNumber);
    }
}

void depositAmount(FILE *fp, int accountNumber) {
    struct Account acc;
    rewind(fp);
    int found = 0;

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accountNumber == accountNumber) {
            found = 1;
            float amount;
            printf("Enter deposit amount: ");
            scanf("%f", &amount);
            acc.balance += amount;
            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);
            printf("Amount deposited successfully. New Balance: %.2f\n", acc.balance);
            break;
        }
    }

    if (!found) {
        printf("Account with Account Number %d not found.\n", accountNumber);
    }
}

void withdrawAmount(FILE *fp, int accountNumber) {
    struct Account acc;
    rewind(fp);
    int found = 0;

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accountNumber == accountNumber) {
            found = 1;
            float amount;
            printf("Enter withdraw amount: ");
            scanf("%f", &amount);
            if (amount > acc.balance) {
                printf("Insufficient balance.\n");
            } else {
                acc.balance -= amount;
                fseek(fp, -sizeof(struct Account), SEEK_CUR);
                fwrite(&acc, sizeof(struct Account), 1, fp);
                printf("Amount withdrawn successfully. New Balance: %.2f\n", acc.balance);
            }
            break;
        }
    }

    if (!found) {
        printf("Account with Account Number %d not found.\n", accountNumber);
    }
}

int main() {
    FILE *fp;
    int choice, accountNumber;

    fp = fopen("bank_accounts.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("bank_accounts.dat", "wb+");
        if (fp == NULL) {
            printf("Unable to open file.\n");
            return 1;
        }
    }

    do {
        printf("\n--- Bank Management System ---\n");
        printf("1. Create Account\n");
        printf("2. View Account\n");
        printf("3. Deposit Amount\n");
        printf("4. Withdraw Amount\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(fp);
                break;
            case 2:
                printf("Enter Account Number to View: ");
                scanf("%d", &accountNumber);
                viewAccount(fp, accountNumber);
                break;
            case 3:
                printf("Enter Account Number to Deposit: ");
                scanf("%d", &accountNumber);
                depositAmount(fp, accountNumber);
                break;
            case 4:
                printf("Enter Account Number to Withdraw: ");
                scanf("%d", &accountNumber);
                withdrawAmount(fp, accountNumber);
                break;
            case 5:
                fclose(fp);
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
