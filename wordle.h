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
        Wt::WContainerWidget *gameContainer; // reference to the container of all the main widgets making up the game
        Game *game; // reference to the controls the game logic and word processing
        Wt::WContainerWidget *inputContainer; // reference to the container of the text entry and submit button
        Wt::WLineEdit *guessEntry; // reference to the text entry for guesses
        Wt::WPushButton *inputButton; // reference to the input button
        Wt::WText *alertText; // reference to the textbox that displays alerts

        void sendGuess();
        void changeState(GameState state, std::string guessText);
        void gameOver(bool gameOver);
        bool isValidGuess(std::string guess);
        bool isAlpha(std::string guess);
        std::string lowercaseGuessString();
};

#endif
