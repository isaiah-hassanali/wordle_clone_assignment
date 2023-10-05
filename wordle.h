/**
 * Author: Isaiah Hassanali
 * Student Number: 251192094
 * Description: This is the header file for wordle.cpp, containing the declaration for the Wordle class.
 * Date: October 4, 2023
 */

#ifndef WORDLE_H
#define WORDLE_H

#include <memory>
#include <string>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "game.h"
#include "gamestate.h"

class Wordle: public Wt::WApplication {
    public:
        Wordle(const Wt::WEnvironment& env);
        ~Wordle();

    private:
        Wt::WContainerWidget *gameContainer;
        Game *game;
        Wt::WContainerWidget *inputContainer;
        Wt::WLineEdit *guessEntry;
        Wt::WPushButton *inputButton;
        Wt::WText *alertText;

        void sendGuess();
        void changeState(GameState state, std::string guessText);
        void gameOver(bool gameOver);
        bool isValidGuess(std::string guess);
        bool isAlpha(std::string guess);
        std::string lowercaseGuessString();
};

#endif
