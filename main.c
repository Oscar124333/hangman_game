#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Constants
const int NULL_TERM_SIZE = 1;
const int WRONGLETTERS = 0;
const int CORRECTLETTERS = 1;
const int guessLibrarySIZE = 2;
enum
{
    ONGOING,
    WIN,
    LOSS
};

// Prototypes
bool doesListHaveChar(char *list, char character);
int RNG(int rangeStart, int rangeEnd);
    // Utility Prototypes
int inputHandler(char *variable);
void inputPrompt(char *variable, char *prompt);
// ^

int main(void)
{
    int playerOutcome = ONGOING;
    int lives = 6;

    // Key/Secrets
    char *key[] = {"secret", "hippopotamus", "apple", "computer", "oscar", "principles"};
    int keySize = sizeof(key) / sizeof(char *);
    srand(time(NULL));
    int keyRNGIndex = RNG(0, keySize - 1);
    int keyLength = strlen(key[keyRNGIndex]);
    char keyCurrent[keyLength + NULL_TERM_SIZE];
    strcpy(keyCurrent, key[keyRNGIndex]);

    // Hint
    char hint[keyLength + NULL_TERM_SIZE];
    memset(hint, 95, keyLength * sizeof(char));
    hint[keyLength] = '\0';
    
    // Guess tracker
    char *guessLibrary[2];
    for (int i = 0; i < 2; i++)
    {
        guessLibrary[i] = calloc(1 + NULL_TERM_SIZE, sizeof(char));
        if (guessLibrary[i] == NULL)
        {
            perror("char *guesslib malloc");
            free(guessLibrary[i]);
            return 1;
        }
    }    
    
    // Main Loop
    char userInput;    
    int correctCounter = 0;
    int correctCounterPrevious = 0;
    while (playerOutcome == ONGOING)
    {
        int wrongGuessLibraryLength = strlen(guessLibrary[WRONGLETTERS]); 
        int correctGuessLibraryLength = strlen(guessLibrary[CORRECTLETTERS]);
        bool guessRepeated = false;

        printf("\nHint: %s\n", hint);
        inputPrompt(&userInput, "Please enter a single character guess");
        printf("\n");
        
        for (int i = 0; i < keyLength; i++)
        {
            if (doesListHaveChar(guessLibrary[WRONGLETTERS], userInput) || doesListHaveChar(guessLibrary[CORRECTLETTERS], userInput))
            {    
                printf("You already guessed this letter!\n");
                guessRepeated = true;
                break;
            }
            if (userInput == keyCurrent[i])
            {
                {
                    hint[i] = keyCurrent[i];
                    correctCounter++;
                }
            }
        }

        if (guessRepeated)
        {
            goto skip;
        }
        else if (correctCounter >= keyLength)
        {
            printf("You got the word!\n");
            printf("--> %s <--\n", hint);
            break;
        }
        else if (correctCounter > correctCounterPrevious)
        {
            printf("You guessed correctly!\n");

            char *temp = realloc(guessLibrary[CORRECTLETTERS], correctGuessLibraryLength + 1 + NULL_TERM_SIZE);
            if (temp == NULL)
            {
                perror("char temp realloc");
                free(temp);
                return 1;
            }
            guessLibrary[CORRECTLETTERS] = temp;
            guessLibrary[CORRECTLETTERS][correctGuessLibraryLength] = userInput;
        }
        else
        {
            lives--;
            printf("%i lives remaining!\n", lives);

            char *temp = realloc(guessLibrary[WRONGLETTERS], wrongGuessLibraryLength + 1 + NULL_TERM_SIZE);
            if (temp == NULL)
            {
                perror("char temp realloc");
                free(temp);
                return 1;
            }
            guessLibrary[WRONGLETTERS] = temp;
            guessLibrary[WRONGLETTERS][wrongGuessLibraryLength] = userInput;
        }
        
        if (lives <= 0)
        {
            printf("You ran out of lives! :(\n");
            break;
        }
        
        skip: printf("Incorrect Guesses: %s\n", guessLibrary[WRONGLETTERS]);
        correctCounterPrevious = correctCounter;
    }
    
    
    free(guessLibrary[WRONGLETTERS]);
    free(guessLibrary[CORRECTLETTERS]);
    return 0;
}

/*************/
/* Functions */
/*************/

bool doesListHaveChar(char *list, char character)
{
    int listLength = strlen(list);
    for (int i = 0; i < listLength; i++)
    {
        if (character == list[i])
        {
            return true;
        }
    }
    return false;
}

int RNG(int rangeStart, int rangeEnd)
{
    int output = 0;
    output = (rand() % (rangeEnd - rangeStart)) + rangeStart;
    return output;
}

/*************/
/*  Utility  */
/*************/

int inputHandler(char *variable)
{
    int status = 0;
    int ch;
    status = scanf("%c", variable);
    while ((ch = getchar()) != '\n' && ch != EOF); // Clear buffer
    return status;
}

void inputPrompt(char *variable, char *prompt)
{
    do
    {
        printf("%s\n==> ", prompt);
    } while (inputHandler(variable) != 1);
    return;
}