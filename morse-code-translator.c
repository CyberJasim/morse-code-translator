#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

// Morse code lookup table for A-Z (indices 0-25) and 0-9 (indices 26-35)
char *morse[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", // S-Z
    "-----", ".----", "..---", "...--", "....-", ".....", // 0-5
    "-....", "--...", "---..", "----." // 6-9
};

// Convert character to index in the morse array
int charToIndex(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= '0' && c <= '9') return c - '0' + 26;
    return -1;
}

// Convert Text to Morse Code
void textToMorse(char *text) {
    printf("Morse: ");
    for (int i = 0; text[i] != '\0'; i++) {
        char c = toupper(text[i]);
        if (c == ' ') {
            printf("/ "); // Word separator
        } else {
            int idx = charToIndex(c);
            if (idx != -1) {
                printf("%s ", morse[idx]);
            }
        }
    }
    printf("\n");
}

// Convert Morse Code to Text
void morseToText(char *morseCode) {
    printf("Text: ");
    char *token = strtok(morseCode, " ");
    while (token != NULL) {
        if (strcmp(token, "/") == 0) {
            printf(" ");
        } else {
            int found = 0;
            for (int i = 0; i < 36; i++) {
                if (strcmp(token, morse[i]) == 0) {
                    if (i < 26) {
                        printf("%c", 'A' + i);
                    } else {
                        printf("%c", '0' + (i - 26));
                    }
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("? "); // Unknown token placeholder
            }
        }
        token = strtok(NULL, " ");
    }
    printf("\n");
}

int main() {
    int choice;
    char input[MAX];

    do {
        printf("\n=============================\n");
        printf("     MORSE CODE TRANSLATOR   \n");
        printf("=============================\n");
        printf("1. Text to Morse\n");
        printf("2. Morse to Text\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear buffer
            continue;
        }
        getchar(); // Clear newline from buffer

        if (choice == 3) {
            printf("Exiting program. Goodbye!\n");
            break;
        }

        if (choice == 1 || choice == 2) {
            printf("Enter the input string: ");
            fgets(input, MAX, stdin);
            input[strcspn(input, "\n")] = 0; // Remove trailing newline

            if (choice == 1) {
                textToMorse(input);
            } else {
                morseToText(input);
            }
        } else {
            printf("Invalid choice! Please choose 1, 2, or 3.\n");
        }

    } while (choice != 3);

    return 0;
}
