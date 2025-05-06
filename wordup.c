//Ryan Byorum
//Project 10: Wordup!


#include <stdio.h>
#include <stdbool.h>

#define MAX_GUESSES 6
#define WORD_LEN 5

void loadWord(char word[]);
void toLowerCase(char str[]);
bool isAlpha(char c);
bool isValidGuess(const char guess[]);
void checkGuess(const char guess[], const char word[], char formatted[], char hint[]);
void printGuesses(char guesses[][WORD_LEN + 1], char hints[][WORD_LEN + 1], int numGuesses);
bool isWordGuessed(const char guess[], const char word[]);
void clearString(char str[], int size);

int main() {
    char word[WORD_LEN + 1];
    loadWord(word);

    char guesses[MAX_GUESSES][WORD_LEN + 1];
    char hints[MAX_GUESSES][WORD_LEN + 1];

    int numGuesses = 0;
    bool won = false;

    while (numGuesses < MAX_GUESSES && !won) {
        char guess[WORD_LEN + 2];
        printf("Enter your guess: ");
        fgets(guess, sizeof(guess), stdin);

        if (guess[WORD_LEN] == '\n') {
            guess[WORD_LEN] = '\0';
        }

        toLowerCase(guess);

        if (!isValidGuess(guess)) {
            printf("Invalid guess! Make sure it's 5 letters, all alphabets.\n");
        }
        else{
            clearString(guesses[numGuesses], WORD_LEN + 1);
            clearString(hints[numGuesses], WORD_LEN + 1);

            checkGuess(guess, word, guesses[numGuesses], hints[numGuesses]);

            won = isWordGuessed(guess, word);
            numGuesses++;

            printGuesses(guesses, hints, numGuesses);
        }
    }

    if (won) {
        printf("Congratulations! You guessed the word!\n");
    }
    else {
        printf("Out of guesses! The word was '%s'.\n", word);
    }

    return 0;
}


void loadWord(char word[]) {
    FILE *file = fopen("word.txt", "r");
    if (file == NULL) {
        printf("Error: could not open word.txt\n");
        word[0] = '\0';
        return;
    }
    fscanf(file, "%5s", word);
    fclose(file);
}


void toLowerCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 'a' - 'A';
        }
    }
}



bool isValidGuess(char guess[]) {
    for (int i = 0; i < WORD_LEN; i++) {
        if (!((guess[i] >= 'A' && guess[i] <= 'Z') || (guess[i] >= 'a' && guess[i] <= 'z'))) {
            return false;
        }
    }
}


void checkGuess(char guess[], char word[], char formatted[], char hint[]) {

    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] == word[i]) {
            formatted[i] = guess[i] - ('a' - 'A');
        } else {
            formatted[i] = guess[i];
        }
        hint[i] = ' ';
    }

    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] != word[i]) {
            for (int j = 0; j < WORD_LEN; j++) {
                if (guess[i] == word[j] && guess[j] != word[j]) {
                    hint[i] = '^';
                }
            }
        }
    }
}


void printGuesses(char guesses[][WORD_LEN + 1], char hints[][WORD_LEN + 1], int numGuesses) {
    for (int i = 0; i < numGuesses; i++) {
        printf("%s\n", guesses[i]);
        printf("%s\n", hints[i]);
    }
}


bool isWordGuessed(const char guess[], const char word[]) {
    for (int i = 0; i < WORD_LEN; i++) {
        if (guess[i] != word[i]) {
            return false;
        }
    }
    return true;
}


void clearString(char str[], int size) {
    for (int i = 0; i < size; i++) {
        str[i] = '\0';
    }
}

