#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    // Utility Prototypes
int inputHandler(char *variable);
void inputPrompt(char *variable, char *prompt);
bool didReallocFail(char *temp);
// ^

int main(void)
{
    int playerOutcome = ONGOING;
    int lives = 6;

    char key[] = "secret";
    int keyLength = strlen(key);

    char hint[keyLength];
    memset(hint, 95, keyLength * sizeof(char));
    
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
    
    char userInput;    
    int correctCounter = 0;
    int correctCounterPrevious = 0;
    while (playerOutcome == ONGOING)
    {
        int wrongGuessLibraryLength = strlen(guessLibrary[WRONGLETTERS]); 
        int correctGuessLibraryLength = strlen(guessLibrary[CORRECTLETTERS]);
        bool guessRepeated = false;

        inputPrompt(&userInput, "Please enter a single character guess");
        printf("\n");
        
        for (int i = 0; i < keyLength; i++)
        {
            char hintPrevious[keyLength];
            strcpy(hintPrevious, hint);

            if (doesListHaveChar(guessLibrary[WRONGLETTERS], userInput) || doesListHaveChar(guessLibrary[CORRECTLETTERS], userInput))
            {    
                printf("You already guessed this letter!\n");
                guessRepeated = true;
                break;
            }
            if (userInput == key[i])
            {
                {
                    hint[i] = key[i];
                    correctCounter++;
                }
            }
        }
        
        for (int i = 0; i < guessLibrarySIZE; i++)
        {
            char *temp = realloc(guessLibrary[i], strlen(guessLibrary[i]) + 1 + NULL_TERM_SIZE);
            if (temp == NULL)
            {
                perror("char temp realloc");
                free(temp);
                return 1;
            }
            guessLibrary[i] = temp;
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
            guessLibrary[CORRECTLETTERS][correctGuessLibraryLength] = userInput;
        }
        else
        {
            lives--;
            printf("%i lives remaining!\n", lives);
            guessLibrary[WRONGLETTERS][wrongGuessLibraryLength] = userInput;
        }
        
        if (lives <= 0)
        {
            printf("You ran out of lives! :(\n");
            break;
        }
        
        skip: printf("Incorrect Guesses: %s\nHint: %s\n\n", guessLibrary[WRONGLETTERS], hint);
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