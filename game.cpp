#include "game.h"

Game::Game(Wt::WContainerWidget *boardContainer) {
    guessNum = 0;
    Wt::WTable *table = boardContainer->addWidget(std::make_unique<Wt::WTable>());
    table->setStyleClass("board");

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
            Wt::WText *text = table->elementAt(i, j)->addWidget(std::make_unique<Wt::WText>());
            board[i][j] = text;
        }
    }

    std::string word;
    std::ifstream guessesFile("guesses.txt");
    while(getline(guessesFile, word)) {
        validGuesses.insert(word);
    }

    answer = pickRandomAnswer();

}

GameState Game::checkGuess(std::string guess) {
    if (isValidWord(guess)) {
        setRow(guess);
        if (++guessNum == 6) {
            return LOSE;
        } else if (isAnswer(guess)) {
            return WIN;
        } else {
            return VALID;
        }
    }
    return INVALID;
}

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

int Game::getNumGuesses() {
    return guessNum;
}

std::string Game::getAnswer() {
    return answer;
}

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

bool Game::isAnswer(std::string guess) {
    return guess == answer;
}

bool Game::isValidWord(std::string guess) {
    return validGuesses.find(guess) != validGuesses.end();
}

void Game::setRow(std::string guess) {
    std::vector<std::string> colours(5, "");
    std::vector<bool> accountedFor(5, false);

    for (int i = 0; i < 5; i++) {
        if (guess[i] == answer[i]) {
            colours[i] = "correct";
            accountedFor[i] = true;
        }
    }

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

    for (int i = 0; i < 5; i++) {
        board[guessNum][i]->setStyleClass(colours[i]);
        std::string stringifiedChar(1, toupper(guess[i]));
        board[guessNum][i]->setText(stringifiedChar);
    }
}