#include "Game.h"

// constructor for a game with parameter max depth
Game :: Game(int max_depth)
{
    this->max_depth = max_depth;
}

// return the player whose turn it is to move in the game
Player Game :: to_move(State *s)
{
    return s->get_player();
}

// method for setting the current state
void Game :: set_current_state(State *s)
{
    // delete the last state before setting the currentState to the new state
    delete currentState;
    currentState = s;
}
