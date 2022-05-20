#ifndef ADVERSERIALSEARCHTICTACTOE_TICTACTOESTATE_H
#define ADVERSERIALSEARCHTICTACTOE_TICTACTOESTATE_H
#include "State.h"
#include <utility>
#include <vector>

// State for a TicTacToe Game inherits from abstract base class State
class TicTacToeState : public State{
public:
    TicTacToeState(Player);
    ~TicTacToeState();
    TicTacToeState(TicTacToeState*, int fill_in);
    void print(ostream& out) const;
    vector<int> get_available_tiles();
    pair<bool, Player> is_win();
    bool is_full();
    int unblocked(int,Player);
private:
    int tiles[9];
    pair<bool, Player> is_horizontal_win();
    pair<bool, Player> is_vertical_win();
    pair<bool, Player> is_diagonal_win();
    int unblocked_horizontal(int,int);
    int unblocked_vertical(int,int);
    int unblocked_diagonal(int,int);
};

#endif //ADVERSERIALSEARCHTICTACTOE_TICTACTOESTATE_H
