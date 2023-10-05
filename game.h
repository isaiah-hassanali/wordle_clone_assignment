/**
 * Author: Isaiah Hassanali
 * Student Number: 251192094
 * Description: This is the header file for game.cpp, containing the declaration for the Game class.
 * Date: October 4, 2023
 */

#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <memory>
#include <string>
#include <set>
#include <fstream>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WTable.h>
#include "gamestate.h"

class Game {
    public:
        Game(Wt::WContainerWidget *boardContainer);
        ~Game();
        GameState checkGuess(std::string guess);
        void resetGame();
        int getNumGuesses();
        std::string getAnswer();

    private:
        int guessNum; // the current guess the user is on
        Wt::WText *board[6][5]; // holds the text widgets that make up the game board
        std::set<std::string> validGuesses; // contains all the words that are considered valid guesses
        std::string answer; // contains the answer for a given round of the game

        std::string pickRandomAnswer();
        bool isAnswer(std::string guess);
        bool isValidWord(std::string guess);
        void setRow(std::string guess);
};

#endif
