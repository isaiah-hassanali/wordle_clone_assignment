#include <stdlib.h>
#include <iterator>
#include <memory>
#include <string>
#include <set>
#include <fstream>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>
#include <Wt/WTable.h>
#include <Wt/WString.h>

/*
 * This class represents the gameboard and handles its display and word colouring.
 */

class Game {
    public:
        Game(Wt::WContainerWidget *boardContainer);
        int checkGuess(std::string guess);

    private:
        Wt::WText *board[6][5];
        std::set<std::string> validWords;
        int currentRow;
        std::string answer;

        std::string pickRandomWord();
        bool isAnswer(std::string guess);
        bool isValidWord(std::string guess);
        void setRow(std::string guess);
};

enum GameState {
    INVALID = 0,
    ANSWER = 1,
    VALID = 2,
    GAMEOVER = 3
};