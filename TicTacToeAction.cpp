#include "TicTacToeAction.h"

// TicTacToe action is the number associated with the player who took the action
TicTacToeAction ::TicTacToeAction(int actionNum, Player player) : Action()
{
    this->actionNum = actionNum;
    this->player = player;
}

// destructor
TicTacToeAction :: ~TicTacToeAction()
{

}

// print
void TicTacToeAction :: print(ostream &out) const
{
    out << actionNum;
}

// get action number
int TicTacToeAction :: get_action_num()
{
    return actionNum;
}

// get the player associated with the action
Player TicTacToeAction ::get_player()
{
    return player;
}