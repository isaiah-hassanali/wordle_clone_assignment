#include "game.h"

Game::Game(Wt::WContainerWidget *boardContainer) {
    currentRow = 0;
    Wt::WTable *table = boardContainer->addWidget(std::make_unique<Wt::WTable>());
    table->setStyleClass("board");

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
            Wt::WText *text = table->elementAt(i, j)->addWidget(std::make_unique<Wt::WText>());
            board[i][j] = text;
        }
    }

    std::string word;
    std::ifstream wordFile("words.txt");
    while(getline(wordFile, word)) {
        validWords.insert(word);
    }

    answer = "tears";//pickRandomWord();

}

int Game::checkGuess(std::string guess) {
    if (isValidWord(guess)) {
        if (isAnswer(guess)) {
            setRow(guess);
            return ANSWER;
        }
        for (int i = 0; i < 5; i++) {
            setRow(guess);
        }
        if (++currentRow > 6) {
            return GAMEOVER;
        } else {
            return VALID;
        }
    }
    return INVALID;
}

std::string Game::pickRandomWord() {
    int randomNumber = rand() % 14855;
    auto iterator = std::begin(validWords);
    std::advance(iterator, randomNumber);
    return *iterator;
}

bool Game::isAnswer(std::string guess) {
    return guess == answer;
}

bool Game::isValidWord(std::string guess) {
    return validWords.find(guess) != validWords.end();
}

void Game::setRow(std::string guess) {
    std::vector<std::string> colours(5, "");


    for (int i = 0; i < 5; i++) {
        if (guess[i] == answer[i]) {
            colours[i] = "correct";
        } else {
            auto iterator = find(answer.begin(), answer.end(), guess[i]);
            int index = std::distance(answer.begin(), iterator);
            if (iterator != answer.end() && guess[index] != answer[index]) {
                colours[i] = "semi-correct";
            } else {
                colours[i] = "incorrect";
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        board[currentRow][i]->setStyleClass(colours[i]);
        std::string stringifiedChar(1, toupper(guess[i]));
        board[currentRow][i]->setText(stringifiedChar);
    }
}