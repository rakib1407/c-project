#include <stdio.h>
#include <stdlib.h>

#define MAX_PIN_TRIES 3

// Structure for ATM Account
struct ATMAccount {
    int accountNumber;
    char pin[5]; // PIN as a string
    float balance;
};

// Function to validate PIN
int validatePin(char *pin) {
    // Hardcoded PIN for the example. In a real application, you would fetch this from a database.
    return strcmp(pin, "1234") == 0;
}

// Function to check balance
void checkBalance(struct ATMAccount *account) {
    printf("Your current balance is: %.2f\n", account->balance);
}

// Function to deposit money
void depositMoney(struct ATMAccount *account) {
    float depositAmount;
    printf("Enter amount to deposit: ");
    scanf("%f", &depositAmount);
    
    if (depositAmount > 0) {
        account->balance += depositAmount;
        printf("Deposited: %.2f\n", depositAmount);
        printf("New balance: %.2f\n", account->balance);
    } else {
        printf("Invalid deposit amount.\n");
    }
}

// Function to withdraw money
void withdrawMoney(struct ATMAccount *account) {
    float withdrawAmount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &withdrawAmount);
    
    if (withdrawAmount > 0 && withdrawAmount <= account->balance) {
        account->balance -= withdrawAmount;
        printf("Withdrawn: %.2f\n", withdrawAmount);
        printf("Remaining balance: %.2f\n", account->balance);
    } else {
        printf("Insufficient balance or invalid amount.\n");
    }
}

// Function to transfer money
void transferMoney(struct ATMAccount *account) {
    float transferAmount;
    int targetAccountNumber;

    printf("Enter target account number: ");
    scanf("%d", &targetAccountNumber);
    printf("Enter amount to transfer: ");
    scanf("%f", &transferAmount);

    if (transferAmount > 0 && transferAmount <= account->balance) {
        account->balance -= transferAmount;
        printf("Transferred %.2f to account number %d.\n", transferAmount, targetAccountNumber);
        printf("Remaining balance: %.2f\n", account->balance);
    } else {
        printf("Insufficient balance or invalid transfer amount.\n");
    }
}

// Main function - ATM interface
int main() {
    struct ATMAccount account = {123456, "1234", 10000.0}; // Example account with balance 1000
    int choice, attempts = 0;
    char pin[5];

    printf("Welcome to ATM\n");

    // PIN validation loop
    while (attempts < MAX_PIN_TRIES) {
        printf("Enter your PIN: ");
        scanf("%s", pin);

        if (validatePin(pin)) {
            printf("PIN validated successfully.\n");
            break;
        } else {
            attempts++;
            printf("Incorrect PIN. You have %d attempts left.\n", MAX_PIN_TRIES - attempts);
        }
    }

    if (attempts == MAX_PIN_TRIES) {
        printf("Too many incorrect PIN attempts. Exiting...\n");
        return 0;
    }

    do {
        // Display ATM menu
        printf("\nATM Menu:\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transfer Money\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(&account);
                break;
            case 2:
                depositMoney(&account);
                break;
            case 3:
                withdrawMoney(&account);
                break;
            case 4:
                transferMoney(&account);
                break;
            case 5:
                printf("Exiting the system...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
