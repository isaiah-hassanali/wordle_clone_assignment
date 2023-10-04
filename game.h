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
        GameState checkGuess(std::string guess);
        int getNumGuesses();
        std::string getAnswer();
        void resetGame();

    private:
        Wt::WText *board[6][5];
        std::set<std::string> validGuesses;
        int guessNum;
        std::string answer;

        std::string pickRandomAnswer();
        bool isAnswer(std::string guess);
        bool isValidWord(std::string guess);
        void setRow(std::string guess);
};

#endif