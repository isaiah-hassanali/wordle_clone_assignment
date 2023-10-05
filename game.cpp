/**
 * Author: Isaiah Hassanali
 * Student Number: 251192094
 * Description: This file implements the Game class. The Game class controls the display and colouring of words on the gameboard. 
 *              It also determines the validity of guesses and the state of the game after each move (win, lose, continue).
 * Date: October 4, 2023
 */

#include "game.h"

/**
 * @brief Constructor for the Game class. This class handles game logic and word checking.
 * @param boardContainer The widget created by the Wordle class that will hold the gameboard
 */
Game::Game(Wt::WContainerWidget *boardContainer) {
    guessNum = 0; // this tracks how many successful guess have been made
    Wt::WTable *table = boardContainer->addWidget(std::make_unique<Wt::WTable>()); // this table is the gameboard
    table->setStyleClass("board");

    // populate the board with WText widgets, which will each hold one character
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
            Wt::WText *text = table->elementAt(i, j)->addWidget(std::make_unique<Wt::WText>());
            board[i][j] = text; // this matrix holds the text widgets in the gameboard
        }
    }

    // read all the valid guesses into the validGuesses set
    std::string word;
    std::ifstream guessesFile("guesses.txt");
    while(getline(guessesFile, word)) {
        validGuesses.insert(word);
    }

    answer = pickRandomAnswer(); // the answer for the first round of play
}

/**
 * @brief Empty destructor.
 */
Game::~Game() {}

/**
 * @brief Checks if a guess is a valid word, and if so, sets the board accordingly.
 * @param guess the guess to check
 * @return GameState representing if the guess was valid, invalid, or a winning or losing guess.
 */
GameState Game::checkGuess(std::string guess) {
    // if valid, set the row, then determine if the game was won, lost, or neither
    if (isValidWord(guess)) {
        setRow(guess);
        guessNum++;
        if (isAnswer(guess)) {
            return WIN;
        } else if (guessNum == 6) {
            return LOSE;
        } else {
            return VALID;
        }
    }
    return INVALID;
}

/**
 * @brief Resets the gameboard, guess number, and picks a new answer for the next round.
 * @return (void)
 */
void Game::resetGame() {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
            board[i][j]->setText("");
            board[i][j]->setStyleClass("");
        }
    }

    guessNum = 0;
    answer = pickRandomAnswer();
}

/**
 * @brief Returns the number of guesses that have been made.
 * @return the number of guesses that have been made
 */
int Game::getNumGuesses() {
    return guessNum;
}

/**
 * @brief Returns the answer for this round.
 * @return the answer for this round
 */
std::string Game::getAnswer() {
    return answer;
}

/**
 * @brief Reads the file containing valid answers (which contains only the most common words from the valid guesses) and randomly returns a word.
 * @return a string which is the new answer for the round
 */
std::string Game::pickRandomAnswer() {
    srand(std::time(NULL));
    int randomNumber = rand() % 3103;

    std::string word;
    std::ifstream answersFile("answers.txt");
    for (int i = 0; i <= randomNumber; i++) {
        std::getline(answersFile, word);
    }
    return word;
}

/**
 * @brief Determines if a guess is correct.
 * @param guess the guess to check
 * @return true if the guess is correct, false otherwise
 */
bool Game::isAnswer(std::string guess) {
    return guess == answer;
}

/**
 * @brief Determines if a guess is valid.
 * @param guess the guess to check
 * @return true if the guess is valid, false otherwise
 */
bool Game::isValidWord(std::string guess) {
    return validGuesses.find(guess) != validGuesses.end();
}

/**
 * @brief Writes a guess into a row of the gameboard and colours it accordingly.
 * @param guess the guess to write
 * @return (void)
 */
void Game::setRow(std::string guess) {
    std::vector<std::string> colours(5, ""); // the colour at each index corresponds to the letter at each index in the guess
    std::vector<bool> accountedFor(5, false); // the bool at each index represents if the letter at that index in the answer has been matched

    // initial pass marks positionally correct letters
    for (int i = 0; i < 5; i++) {
        if (guess[i] == answer[i]) {
            colours[i] = "correct";
            accountedFor[i] = true;
        }
    }

    // second pass for semi-correct and incorrect letters
    // for each letter in the guess that wasn't marked correct, iterate through the answer
    // and look for a match. if a match is found and unaccounted for, the letter in the guess is semi-correct.
    // if the inner loop finishes with no unnacounted for match, the letter is incorrect.
    for (int i = 0; i < 5; i++) {
        if (colours[i] == "") {
            for (int j = 0; j < 5; j++) {
                if (answer[j] == guess[i] && !accountedFor[j]) {
                    colours[i] = "semi-correct";
                    accountedFor[j] = true;
                    break;
                }
            }
            if (colours[i] == "") {
                colours[i] = "incorrect";
            }
        }
    }

    // set the colours for each character and write them into the row
    for (int i = 0; i < 5; i++) {
        board[guessNum][i]->setStyleClass(colours[i]);
        std::string stringifiedChar(1, toupper(guess[i]));
        board[guessNum][i]->setText(stringifiedChar);
    }
}
