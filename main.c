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
int inputHandler(char *variable);
void inputPrompt(char *variable, char *prompt);

int main(void)
{
    int playerOutcome = ONGOING; // ongoing by default at startup
    int lives = 6;

    char key[] = "secret";
    int keyLength = strlen(key);

    char hint[keyLength];
    memset(hint, 95, keyLength * sizeof(char));
    
    char *guessLetterLibrary = calloc(1 + NULL_TERM_SIZE, sizeof(char));
    if (guessLetterLibrary == NULL)
    {
        perror("char *guesslib malloc");
        free(guessLetterLibrary);
        return 1;
    }
    
    char userInput;    
    int previous_correctCounter = 0;
    int correctCounter = 0;
    while (playerOutcome == ONGOING)
    {
        inputPrompt(&userInput, "Please enter a single character guess");
        printf("\n");
        
        for (int i = 0; i < keyLength; i++)
        {
            if (userInput == key[i])
            {
                hint[i] = key[i];
                correctCounter++;
            }
        }
        
        if (correctCounter == keyLength)
        {
            printf("You got the word!\n");
            break;
        }
        else if (correctCounter > previous_correctCounter)
        {
            printf("You guessed correctly!\n");
        }
        else 
        {
            lives--;
            int length_guessLetterLibrary = strlen(guessLetterLibrary); 
            guessLetterLibrary[length_guessLetterLibrary] = userInput;
            
            // refactor later
            char *temp = realloc(guessLetterLibrary, length_guessLetterLibrary + 1 + NULL_TERM_SIZE);
            if (temp == NULL)
            {
                perror("char temp realloc");
                free(temp);
                return 1;
            }
            guessLetterLibrary = temp;
            // ^

            printf("%i lives remaining!\n", lives);
            if (lives <= 0)
            {
                printf("You ran out of lives! :(\n");
                break;
            }
        }
        printf("Incorrect Guesses: %s\nHint: %s\n\n", guessLetterLibrary, hint);
        
        previous_correctCounter = correctCounter;
    }
    
    
    free(guessLetterLibrary);
    return 0;
}



/***********/
/*   I/O   */
/***********/

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