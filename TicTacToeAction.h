#ifndef ADVERSERIALSEARCHTICTACTOE_TICTACTOEACTION_H
#define ADVERSERIALSEARCHTICTACTOE_TICTACTOEACTION_H
#include "Action.h"
#include "State.h"

// Action for a TicTacToe Game inherits from abstract base class Action
class TicTacToeAction : public Action{
public:
    TicTacToeAction(int, Player);
    ~TicTacToeAction();
    void print(ostream& out) const;
    int get_action_num();
    Player get_player();
private:
    Player player;
    int actionNum;
};
#endif //ADVERSERIALSEARCHTICTACTOE_TICTACTOEACTION_H
