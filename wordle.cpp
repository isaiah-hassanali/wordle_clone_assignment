#include "wordle.h"

Wordle::Wordle(const Wt::WEnvironment &env): WApplication(env) {
    setTitle("Wordle!");
    instance()->useStyleSheet("styles.css");
    Wt::WText *title = root()->addWidget(std::make_unique<Wt::WText>("Not Wordle"));
    title->setStyleClass("title");
    gameContainer = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    gameContainer->setStyleClass("game-container");
    
    game = new Game(gameContainer->addWidget(std::make_unique<Wt::WContainerWidget>()));

    inputContainer = gameContainer->addWidget(std::make_unique<Wt::WContainerWidget>());
    inputContainer->setStyleClass("input-container");

    guessEntry = inputContainer->addWidget(std::make_unique<Wt::WLineEdit>());
    guessEntry->setMaxLength(5);
    guessEntry->setPlaceholderText("Enter a guess...");
    guessEntry->enterPressed().connect([=]() {
        std::string guessText = lowercaseGuessString();
        if (isValidGuess(guessText)) {
            GameState state = game->checkGuess(guessText);
            changeState(state, guessText);
        }
    });

    inputButton = inputContainer->addWidget(std::make_unique<Wt::WPushButton>("Submit"));
    inputButton->clicked().connect([=]() {
        std::string guessText = lowercaseGuessString();
        if (isValidGuess(guessText)) {
            GameState state = game->checkGuess(guessText);
            changeState(state, guessText);
        }
    });

    alertText = gameContainer->addWidget(std::make_unique<Wt::WText>());
    alertText->setStyleClass("alert");
}

Wordle::~Wordle() {}

void Wordle::changeState(GameState state, std::string guessText) {
    guessEntry->setText("");
    if (state == INVALID) {
        alertText->setText(guessText + " is not a valid word.");
    } else if (state == LOSE) {
        gameOver(true);
    } else if (state == WIN) {
        gameOver(false);
    }
}

void Wordle::gameOver(bool gameOver) {
    inputContainer->setDisabled(true);
    if (gameOver) {
        alertText->setText("You lost. The answer was <span style=\"color: rgb(74, 130, 73);\">" + game->getAnswer() + ".</span>");
    } else {
        alertText->setText("<span style=\"color: rgb(74, 130, 73);\">Congratulations! You won in " + std::to_string(game->getNumGuesses()) + " guesses.</span>");
    }
    Wt::WPushButton *playAgainButton = gameContainer->addWidget(std::make_unique<Wt::WPushButton>("Play again!"));
    playAgainButton->clicked().connect([=]() {
        game->resetGame();
        inputContainer->setDisabled(false);
        alertText->setText("");
        gameContainer->removeWidget(playAgainButton);
    });
    playAgainButton->setStyleClass("play-again-button");
}

bool Wordle::isValidGuess(std::string guess) {
    if (guess.length() != 5) {
        guessEntry->setText("");
        alertText->setText("You must enter a five-letter word.");
        return false;
    } else if (!isAlpha(guess)) {
        guessEntry->setText("");
        alertText->setText("You may only use alphabetic characters.");
        return false;
    } else {
        alertText->setText("");
        return true;
    }
}

bool Wordle::isAlpha(std::string text) {
    for (int i = 0; i < 5; i++) {
        if (!isalpha(text[i])) {
            return false;
        }
    }
    return true;
}

std::string Wordle::lowercaseGuessString() {
    std::string guessText = guessEntry->text().toUTF8();
    for (char &c : guessText) {
        c = tolower(c);
    }
    return guessText;
}