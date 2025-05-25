#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int bookID;
    char title[50];
    char author[50];
    int quantity;
};

void addBook(FILE *fp) {
    struct Book b;
    printf("Enter Book ID: ");
    scanf("%d", &b.bookID);
    getchar();  // To consume newline character left by scanf
    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0';  // Remove newline
    printf("Enter Author: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = '\0';  // Remove newline
    printf("Enter Quantity: ");
    scanf("%d", &b.quantity);

    fseek(fp, 0, SEEK_END);
    fwrite(&b, sizeof(struct Book), 1, fp);
    printf("Book added successfully!\n");
}

void viewBooks(FILE *fp) {
    struct Book b;
    rewind(fp);
    printf("\nList of Books:\n");
    printf("-------------------------------------------\n");
    while (fread(&b, sizeof(struct Book), 1, fp)) {
        printf("Book ID: %d | Title: %s | Author: %s | Quantity: %d\n", b.bookID, b.title, b.author, b.quantity);
    }
    printf("-------------------------------------------\n");
}

void searchBook(FILE *fp, int bookID) {
    struct Book b;
    rewind(fp);
    int found = 0;
    while (fread(&b, sizeof(struct Book), 1, fp)) {
        if (b.bookID == bookID) {
            printf("\nBook Found:\n");
            printf("Book ID: %d | Title: %s | Author: %s | Quantity: %d\n", b.bookID, b.title, b.author, b.quantity);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Book with ID %d not found.\n", bookID);
    }
}

void deleteBook(FILE *fp, int bookID) {
    struct Book b;
    FILE *temp = fopen("temp.dat", "wb");
    rewind(fp);
    int found = 0;

    while (fread(&b, sizeof(struct Book), 1, fp)) {
        if (b.bookID != bookID) {
            fwrite(&b, sizeof(struct Book), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove("library.dat");
    rename("temp.dat", "library.dat");

    if (found) {
        printf("Book deleted successfully!\n");
    } else {
        printf("Book with ID %d not found.\n", bookID);
    }
}

void updateBook(FILE *fp, int bookID) {
    struct Book b;
    rewind(fp);
    int found = 0;
    long pos;
    while (fread(&b, sizeof(struct Book), 1, fp)) {
        if (b.bookID == bookID) {
            found = 1;
            pos = ftell(fp) - sizeof(struct Book);

            printf("Enter New Title: ");
            getchar();  // To consume newline character left by scanf
            fgets(b.title, sizeof(b.title), stdin);
            b.title[strcspn(b.title, "\n")] = '\0';
            printf("Enter New Author: ");
            fgets(b.author, sizeof(b.author), stdin);
            b.author[strcspn(b.author, "\n")] = '\0';
            printf("Enter New Quantity: ");
            scanf("%d", &b.quantity);

            fseek(fp, pos, SEEK_SET);
            fwrite(&b, sizeof(struct Book), 1, fp);
            printf("Book information updated successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Book with ID %d not found.\n", bookID);
    }
}

int main() {
    FILE *fp;
    int choice, bookID;

    fp = fopen("library.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("library.dat", "wb+");
        if (fp == NULL) {
            printf("Unable to open file.\n");
            return 1;
        }
    }

    do {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n");
        printf("2. View All Books\n");
        printf("3. Search Book\n");
        printf("4. Update Book\n");
        printf("5. Delete Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(fp);
                break;
            case 2:
                viewBooks(fp);
                break;
            case 3:
                printf("Enter Book ID to Search: ");
                scanf("%d", &bookID);
                searchBook(fp, bookID);
                break;
            case 4:
                printf("Enter Book ID to Update: ");
                scanf("%d", &bookID);
                updateBook(fp, bookID);
                break;
            case 5:
                printf("Enter Book ID to Delete: ");
                scanf("%d", &bookID);
                deleteBook(fp, bookID);
                fp = fopen("library.dat", "rb+");
                break;
            case 6:
                fclose(fp);
                printf("Exiting the program. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
