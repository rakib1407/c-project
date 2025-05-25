#include <stdio.h>
#include <string.h>

// Function to encrypt the text
void encrypt(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        // Encrypt uppercase letters
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - 'A' + shift) % 26 + 'A';
        }
        // Encrypt lowercase letters
        else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' + shift) % 26 + 'a';
        }
    }
}

// Function to decrypt the text
void decrypt(char text[], int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        // Decrypt uppercase letters
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - 'A' - shift + 26) % 26 + 'A';
        }
        // Decrypt lowercase letters
        else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' - shift + 26) % 26 + 'a';
        }
    }
}

int main() {
    char text[100];
    int shift, choice;

    printf("----- Encryption and Decryption Tool -----\n");
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin); // Take input text from user
    text[strcspn(text, "\n")] = '\0';  // Remove the newline character at the end

    printf("Enter shift value (1-25): ");
    scanf("%d", &shift);

    // Menu to choose between encryption and decryption
    do {
        printf("\nChoose an option:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                encrypt(text, shift);
                printf("Encrypted Text: %s\n", text);
                break;
            case 2:
                decrypt(text, shift);
                printf("Decrypted Text: %s\n", text);
                break;
            case 3:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
