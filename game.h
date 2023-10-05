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
        int guessNum;
        Wt::WText *board[6][5];
        std::set<std::string> validGuesses;
        std::string answer;

        std::string pickRandomAnswer();
        bool isAnswer(std::string guess);
        bool isValidWord(std::string guess);
        void setRow(std::string guess);
};

#endif