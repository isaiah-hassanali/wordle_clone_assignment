#include <memory>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WText.h>
#include "game.h"

/*
 * Main class of the application. Handles user input and drives the game.
 */
class Wordle: public Wt::WApplication {
    public:
        Wordle(const Wt::WEnvironment& env);

    private:
        Wt::WContainerWidget *gameContainer;
        Game *game;
        Wt::WLineEdit *guessEntry;
        Wt::WPushButton *inputButton;
        Wt::WText *alertText;

        bool isValidGuess(std::string guess);
        int attemptGuess(std::string guessText);
        bool isAlpha(std::string guess);
        std::string lowercaseGuessString();
};