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


enum GameState {
    INVALID = 0,
    WIN = 1,
    VALID = 2,
    LOSE = 3
};

/*
 * This class represents the gameboard and handles its display and word colouring.
 */
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