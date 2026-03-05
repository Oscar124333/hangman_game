# alternative python version
import random

# Constants
ongoing = 0
win = 1
lose = 2

secretList = ["wasd", "oscar", "computer", "hippopatomus", "westminster"]
rng = random.randint(0, len(secretList) - 1)

secretChosen = list(secretList[rng])
secretChosen_len = len(secretChosen)
secretHint = " _" * secretChosen_len

# Main loop
userState = ongoing
userLives = 6
userCorrectCount = 0
userGuessList = []


while (True):
    print("**********")
    print("guessed letters: " + ", ".join(userGuessList))
    print("secret word hint: " + secretHint)

    userInput = input("guess: ")

    if userInput in list(userGuessList):
        print("you already guessed this!\n")
        continue
    elif (not(userInput in secretChosen)):
        userGuessList.append(userInput)
    #endif

    userGuessState = False
    for letterIndex in range(0, secretChosen_len):
        if (userInput == secretChosen[letterIndex]):
            userCorrectCount += 1
            userGuessState = True

            secretHint_temp = list(secretHint)
            secretHint_temp[(letterIndex * 2) + 1] = userInput
            secretHint = "".join(secretHint_temp)
        #endif
    #endfor

    if (userGuessState == True):
        print("correct guess!\n")
    else:
        print("wrong guess!\n")
        userLives -= 1
    #endif

    if (userCorrectCount >= secretChosen_len):
        print("you win!")
        print(">>>> " + "".join(secretChosen) + " <<<<")
        break
    elif (userLives <= 0):
        print("you lose!\n:( womp womp :(")
        break
    #endif
#endwhile