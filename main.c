#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Constants
const int NULL_TERM_SIZE = 1;
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
// ^

int main(void)
{
    int playerOutcome = ONGOING; // ongoing by default at startup
    int lives = 99;

    char key[] = "secret";
    int keyLength = strlen(key);

    char hint[keyLength];
    memset(hint, 95, keyLength * sizeof(char));
    
    char *guessLibrary = calloc(1 + NULL_TERM_SIZE, sizeof(char));
    if (guessLibrary == NULL)
    {
        perror("char *guesslib malloc");
        free(guessLibrary);
        return 1;
    }
    
    
    char userInput;    
    int correctCounter = 0;
    int correctCounterPrevious = 0;
    while (playerOutcome == ONGOING)
    {
        int guessLibraryLength = strlen(guessLibrary); 
        bool guessRepeated = false;

        inputPrompt(&userInput, "Please enter a single character guess");
        printf("\n");
        
        for (int i = 0; i < keyLength; i++)
        {
            char hintPrevious[keyLength];
            strcpy(hintPrevious, hint);
            if (doesListHaveChar(guessLibrary, userInput) || doesListHaveChar(hintPrevious, userInput))
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
        
        if (guessRepeated)
        {
            goto skip;
        }
        else if (correctCounter >= keyLength)
        {
            printf("You got the word!\n");
            break;
        }
        else if (correctCounter > correctCounterPrevious)
        {
            printf("You guessed correctly!\n");
        }
        else 
        {
            lives--;
            guessLibrary[guessLibraryLength] = userInput;
            
            // refactor later
            char *temp = realloc(guessLibrary, guessLibraryLength + 1 + NULL_TERM_SIZE);
            if (temp == NULL)
            {
                perror("char temp realloc");
                free(temp);
                return 1;
            }
            guessLibrary = temp;
            // ^
            
            printf("%i lives remaining!\n", lives);
            if (lives <= 0)
            {
                printf("You ran out of lives! :(\n");
                break;
            }
        }
        skip: printf("Incorrect Guesses: %s\nHint: %s\n\n", guessLibrary, hint);
        correctCounterPrevious = correctCounter;
    }
    
    
    free(guessLibrary);
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