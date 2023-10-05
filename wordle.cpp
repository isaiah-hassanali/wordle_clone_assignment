/**
 * Author: Isaiah Hassanali
 * Student Number: 251192094
 * Description: This is the implementation file for the Wordle class. This is the main driver of the game, controlling
 *              the interaction with the user and sending clean and valid input to the Game class for play.
 * Date: October 4, 2023
 */

#include "wordle.h"

/**
 * @name Wordle
 * @brief Constructor for the Wordle class. This class controls the flow of the game and I/O with the user, 
 *        sending clean input to the Game class, and taking the appropriate action based on the response.
 * @param env
 */
Wordle::Wordle(const Wt::WEnvironment &env): WApplication(env) {
    // set up main style sheet and title
    setTitle("Wordle!");
    instance()->useStyleSheet("styles.css");
    Wt::WText *title = root()->addWidget(std::make_unique<Wt::WText>("Not Wordle"));
    title->setStyleClass("title");

    // this is the main container that will hold the gameboard and input mechanisms
    gameContainer = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    gameContainer->setStyleClass("game-container");
    
    // create the Game instance that will handle the Wordle logic and gameboard appearance
    game = new Game(gameContainer->addWidget(std::make_unique<Wt::WContainerWidget>()));

    // this container will hold the text entry and submit buttons
    inputContainer = gameContainer->addWidget(std::make_unique<Wt::WContainerWidget>());
    inputContainer->setStyleClass("input-container");

    // set up text entry for guesses
    guessEntry = inputContainer->addWidget(std::make_unique<Wt::WLineEdit>());
    guessEntry->setMaxLength(5);
    guessEntry->setPlaceholderText("Enter a guess...");
    guessEntry->enterPressed().connect(this, &Wordle::sendGuess);

    // set up "submit guess" button
    inputButton = inputContainer->addWidget(std::make_unique<Wt::WPushButton>("Submit"));
    inputButton->clicked().connect(this, &Wordle::sendGuess);

    // this text area is for alerts regarding game status
    alertText = gameContainer->addWidget(std::make_unique<Wt::WText>());
    alertText->setStyleClass("alert");
}

/**
 * @brief Empty destructor.
 */
Wordle::~Wordle() {}

/**
 * @brief Cleans and validates guess and submits it to Game to see if it plays. Handles the state change accordingly.
 * @return (void)
 */
void Wordle::sendGuess() {
    std::string guessText = lowercaseGuessString();
    if (isValidGuess(guessText)) {
        GameState state = game->checkGuess(guessText);
        changeState(state, guessText);
    }
}

/**
 * @brief Handles the state after a guess occurs. If invalid, alerts the user and continues play, and if the game is over, calls gameOver().
 * @param state The state returned from checkGuess()
 * @param guessText The user's guess, used to display invalid word message
 * @return (void)
 */
void Wordle::changeState(GameState state, std::string guessText) {
    guessEntry->setText("");
    if (state == INVALID) {
        alertText->setText(guessText + " is not a valid word.");
    } else if (state == LOSE) {
        gameOver(0);
    } else if (state == WIN) {
        gameOver(1);
    }
}

/**
 * @brief Handles a game over situation, telling the user if they won or lost and allowing them to play again.
 * @param gameOver 0 if the user lost, 1 if they won
 * @return (void)
 */
void Wordle::gameOver(bool gameOver) {
    // disable input and display relevant alert
    inputContainer->setDisabled(true);
    if (gameOver == 0) {
        alertText->setText("You lost. The answer was <span style=\"color: rgb(74, 130, 73);\">" + game->getAnswer() + ".</span>");
    } else {
        alertText->setText("<span style=\"color: rgb(74, 130, 73);\">Congratulations! You won in " + std::to_string(game->getNumGuesses()) + " guesses.</span>");
    }

    // create button and attach lambda function to play again, button is self-deleting
    Wt::WPushButton *playAgainButton = gameContainer->addWidget(std::make_unique<Wt::WPushButton>("Play again!"));
    playAgainButton->clicked().connect([=]() {
        game->resetGame();
        inputContainer->setDisabled(false);
        alertText->setText("");
        gameContainer->removeWidget(playAgainButton);
    });
    playAgainButton->setStyleClass("play-again-button");
}

/**
 * @brief Determines if a guess contains 5 letters and is alphabetic. Displays a relevant alert.
 * @param guess the user's guess
 * @return true if valid, false if invalid
 */
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

/**
 * @brief Helper function determining if the string it's passed is alphabetic only.
 * @param text the string to check
 * @return true if alphabetic, false otherwise
 */
bool Wordle::isAlpha(std::string text) {
    for (int i = 0; i < 5; i++) {
        if (!isalpha(text[i])) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Converts the string inside the guess entry box to lowercase.
 * @return lowercased guess string
 */
std::string Wordle::lowercaseGuessString() {
    std::string guessText = guessEntry->text().toUTF8();
    for (char &c : guessText) {
        c = tolower(c);
    }
    return guessText;
}
