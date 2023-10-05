/**
 * Author: Isaiah Hassanali
 * Student Number: 251192094
 * Description: The enumeration defined in this header file is used to increase readability regarding changes in game state in wordle.cpp and game.cpp.
 * Date: October 4, 2023
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

enum GameState {
    INVALID = 0,
    WIN = 1,
    VALID = 2,
    LOSE = 3
};

#endif
