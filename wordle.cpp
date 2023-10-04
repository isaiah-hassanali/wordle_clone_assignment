#include "wordle.h"

Wordle::Wordle(const Wt::WEnvironment &env): WApplication(env) {
    setTitle("Wordle!");
    instance()->useStyleSheet("styles.css");
    Wt::WText *title = root()->addWidget(std::make_unique<Wt::WText>("Not Wordle"));
    title->setStyleClass("title");
    gameContainer = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    gameContainer->setStyleClass("game-container");
    
    game = new Game(gameContainer->addWidget(std::make_unique<Wt::WContainerWidget>()));

    Wt::WContainerWidget *inputContainer = gameContainer->addWidget(std::make_unique<Wt::WContainerWidget>());
    inputContainer->setStyleClass("input-container");

    guessEntry = inputContainer->addWidget(std::make_unique<Wt::WLineEdit>());
    guessEntry->setMaxLength(5);
    guessEntry->enterPressed().connect([=]() {
        std::string guessText = lowercaseGuessString();
        if (isValidGuess(guessText)) {
            attemptGuess(guessText);
        }
    });

    inputButton = inputContainer->addWidget(std::make_unique<Wt::WPushButton>("Enter guess!"));
    inputButton->clicked().connect([=]() {
        std::string guessText = lowercaseGuessString();
        if (isValidGuess(guessText)) {
            attemptGuess(guessText);
        }
    });

    alertText = gameContainer->addWidget(std::make_unique<Wt::WText>());
    alertText->setStyleClass("alert");
}

int Wordle::attemptGuess(std::string guessText) {
    int status;
    status = game->checkGuess(guessText);
    guessEntry->setText("");
    if (status == 0) {
        alertText->setText(guessText + " is not a valid word.");
    }
    return status;
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