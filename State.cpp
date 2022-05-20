#include "State.h"

// Constructor for the state with the player for that state passed in
State ::State(Player player)
{
    this->player = player;
}

// get player for this state
Player State ::get_player()
{
    return player;
}

// get the adversary of the player in this state
Player State ::get_adversary()
{
    if(player == MIN)
    {
        return MAX;
    }

    return MIN;
}

// set the player for this state
void State ::set_player(Player player)
{
    this->player = player;
}
