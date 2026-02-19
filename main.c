#include <stdio.h>

// Constants/Globals

// Prototypes
int inputHandler(int *variable);
void inputPrompt(int *variable, char *prompt);


int main(void)
{
    printf("Hello, World!\n");
    int userInput = 0;

    inputPrompt(&userInput, "Please enter a number\n==> ");

    printf("\n%d\n", userInput);

    return 0;
}



/***********/
/*   I/O   */
/***********/

int inputHandler(int *variable)
{
    int status = 0;
    int ch;
    status = scanf("%d", variable);
    if (status != 1)
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
            ; // Clear buffer
    }
    return status;
}

void inputPrompt(int *variable, char *prompt)
{
    do
    {
        printf("%s\n==> ", prompt);
    } while (inputHandler(variable) != 1);
    return;
}