#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 1024

bool is_vowel(char c) {
    // Check if the character is an uppercase or lowercase vowel
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' ||
            c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    int count = 0;
    for (int i = 0; i < num_chars; i++) {
        if (!is_vowel(in_buf[i])) {
            out_buf[count++] = in_buf[i];
        }
    }
    return count; // Number of non-vowels copied
}



void disemvowel(FILE* inputFile, FILE* outputFile) {
    char in_buf[BUF_SIZE];
    char out_buf[BUF_SIZE];

    int num_chars;
    while ((num_chars = fread(in_buf, sizeof(char), BUF_SIZE, inputFile)) > 0) {
        int num_non_vowels = copy_non_vowels(num_chars, in_buf, out_buf);
        fwrite(out_buf, sizeof(char), num_non_vowels, outputFile);
    }
}

int main(int argc, char *argv[]) {
    FILE *inputFile = stdin;  // Default to stdin
    FILE *outputFile = stdout; // Default to stdout

    // Handle command-line arguments
    if (argc > 1) {
        inputFile = fopen(argv[1], "r");
        if (inputFile == NULL) {
            perror("Error opening input file");
            return 1;
        }
    }

    if (argc > 2) {
        outputFile = fopen(argv[2], "w");
        if (outputFile == NULL) {
            perror("Error opening output file");
            fclose(inputFile);  // Close the input file before exiting
            return 1;
        }
    }

    // Call disemvowel function
    disemvowel(inputFile, outputFile);

    // Clean up
    if (inputFile != stdin) fclose(inputFile);
    if (outputFile != stdout) fclose(outputFile);

    return 0;
}
