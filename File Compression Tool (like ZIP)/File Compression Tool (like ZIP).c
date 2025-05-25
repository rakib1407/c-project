#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform Run-Length Encoding (RLE) compression
void compressRLE(char *input, FILE *outputFile) {
    int length = strlen(input);
    
    for (int i = 0; i < length; i++) {
        // Count the number of repetitions of the current character
        int count = 1;
        while (i < length - 1 && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        
        // Write the character and its count to the output file
        fprintf(outputFile, "%c%d", input[i], count);
    }
}

// Function to decompress the RLE compressed data
void decompressRLE(FILE *inputFile, FILE *outputFile) {
    char ch;
    while (fscanf(inputFile, "%c", &ch) != EOF) {
        int count;
        fscanf(inputFile, "%d", &count);
        
        // Write the character 'count' times to the output file
        for (int i = 0; i < count; i++) {
            fputc(ch, outputFile);
        }
    }
}

int main() {
    int choice;
    char input[1000];
    FILE *inputFile, *outputFile;

    do {
        printf("\n--- File Compression Tool (RLE) ---\n");
        printf("1. Compress File\n");
        printf("2. Decompress File\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // to consume the newline character

        switch (choice) {
            case 1:
                printf("Enter the string to compress: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';  // Remove newline character

                // Open the file for writing the compressed data
                outputFile = fopen("compressed.txt", "w");
                if (outputFile == NULL) {
                    printf("Error opening file for compression.\n");
                    break;
                }

                compressRLE(input, outputFile);
                printf("File compressed and saved as 'compressed.txt'.\n");

                fclose(outputFile);
                break;

            case 2:
                // Open the compressed file for reading
                inputFile = fopen("compressed.txt", "r");
                if (inputFile == NULL) {
                    printf("No compressed file found!\n");
                    break;
                }

                // Open the file for writing the decompressed data
                outputFile = fopen("decompressed.txt", "w");
                if (outputFile == NULL) {
                    printf("Error opening file for decompression.\n");
                    fclose(inputFile);
                    break;
                }

                decompressRLE(inputFile, outputFile);
                printf("File decompressed and saved as 'decompressed.txt'.\n");

                fclose(inputFile);
                fclose(outputFile);
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
