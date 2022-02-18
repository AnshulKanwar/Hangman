#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(NULL));

    // Choosing a word
    const std::array wordList{
        "awake", "stand", "solve", "cheek", "pit", "proof", "queen", "pitch", "spit",
        "idea", "swipe", "soak", "pawn", "floor", "mood", "metal", "blow", "drum"
    };
    const std::string randomWord = wordList[rand() % wordList.size()];

    // guessing
    int wordLength = randomWord.length();
    std::vector<char> word(wordLength, '_');
    std::vector<char> usedWords;

    // we are using string for a guess insted of char because
    // if player enters multiple chars at same time then the will
    // stay in input stream and used for upcoming iterations.
    std::string guessString;
    int triesLeft = 10;

    bool isCompleted = false;
    bool isWordUsed = false;
    bool multipleCharactersEntered = false;

    while (!isCompleted && triesLeft > 0)
    {
        // printing
        std::cout << "\x1B[2J\x1B[H" << std::endl;
        if (isWordUsed)
        {
            std::cout << "You have already used that letter" << std::endl
                      << std::endl;
            isWordUsed = false;
        }
        else if (multipleCharactersEntered)
        {
            std::cout << "Please enter one letter at a time" << std::endl
                      << std::endl;
            multipleCharactersEntered = false;
        }

        for (char ch : word)
        {
            std::cout << ch << " ";
        }
        std::cout << std::endl
                  << "Tries Left: " << triesLeft << std::endl;

        std::cout << "Make a guess: ";
        std::cin >> guessString;

        // validation
        // 1. Only one character should be entered at a time
        // 2. The word should not be already used
        if (guessString.length() > 1)
        {
            multipleCharactersEntered = true;
            continue;
        }
        char guess = guessString[0];

        for (char ch : usedWords)
        {
            if (ch == guess)
            {
                isWordUsed = true;
                break;
            }
        }
        if (!isWordUsed)
        {
            isCompleted = true;
            bool isCorrect = false;

            for (int i = 0; i < word.size(); i++)
            {
                // if entered char matches anywhere
                // replace _ with the char
                if (randomWord[i] == guess)
                {
                    word[i] = guess;
                    isCorrect = true;
                }
                // also check if the game is completed
                // (by checking for any left _)
                if (word[i] == '_')
                {
                    isCompleted = false;
                }
            }

            if (!isCorrect) {
                triesLeft--;
            }

            usedWords.push_back(guess);
        }
    }

    std::cout << "\n\n";
    if (isCompleted)
    {
        std::cout << "You Won! The word was \"" << randomWord << "\"" << std::endl;
    }
    else if (triesLeft == 0)
    {
        std::cout << "You Lost! The word was \"" << randomWord << "\"" << std::endl;
    }

    return 0;
}